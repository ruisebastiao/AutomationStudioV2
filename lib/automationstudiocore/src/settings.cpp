/****************************************************************************
**
** Copyright (C) 2014-2018 Dinu SV.
** (contact: mail@dinusv.com)
** This file is part of Live CV Application.
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
****************************************************************************/

#include "settings.h"
#include <QVariant>
#include <QDir>
#include <QQmlEngine>
#include <QJsonDocument>
#include <QJsonArray>
#include <QSysInfo>
#include <qdebug.h>
#include <QNetworkInterface>
#include <qhostinfo.h>

#include "Logger.h"


namespace as{


Settings::Settings(QObject *parent, QString appdir)
    : QObject(parent)
{
    m_appdir=appdir;



    foreach (QNetworkInterface interface, QNetworkInterface::allInterfaces()) {

        switch (interface.type()) {
        case QNetworkInterface::Ethernet:
            m_ethMAC=interface.hardwareAddress();
            LOG_INFO("hardwareAddress:"+m_ethMAC+"("+interface.name()+")");
            break;
        default:
            break;
        }

    }

    m_sysInfo=QSysInfo::kernelType();
    m_cpuType=QSysInfo::currentCpuArchitecture();

    // LOG_INFO("Running on "+m_sysInfo+"/"+m_cpuType);


    //    QList<QString> teste=Utilities::QtEnumsToStrings<User::UserRole>(false);

    m_projects= new ProjectsListModel();
    m_users= new UsersListModel();

    m_socketIO= new SocketIO(this);

    m_appUpdater= new AppUpdater(this);



    connect(m_appUpdater,&AppUpdater::updateDone,this,[&](){
        QJsonObject data;

        data["mac"]=m_ethMAC;


        QJsonDocument doc(data);
        m_socketIO->send("fromapp:updatedone",doc.toJson(QJsonDocument::Compact));
        emit this->updateDone();
    });


    connect(m_socketIO,&SocketIO::doUpdate,this,[&](QString releasename){
        LOG_INFO()<<"Updating ::"<<releasename;
        emit this->doUpdate(releasename);



        m_appUpdater->doUpdate(releasename);
    });


    connect(m_socketIO,&SocketIO::socketIOConnected,this,[&](){

        QJsonObject data;

        data["mac"]=m_ethMAC;
        data["installedversion"]=APPVERSION;
        data["buildinfo"]=BUILD_ID;


        QJsonDocument doc(data);


        m_socketIO->send("fromapp:setinstalledversion",doc.toJson(QJsonDocument::Compact),[&](message::list const& msg) {


            if(msg.size()>0){

                message::ptr data=msg.at(0);
                if(data->get_flag() == message::flag_string){
                    QString result=QString::fromStdString(data->get_string());

                    QList<QString> results=result.split('|');

                    if(results.length()>0 && results[0]=="NOK"){
                        if(results.length()>1 && results[1]=="NOT REGISTRED"){
                            this->setAppRegistred(false);
                            emit this->appRegistredChanged(false);
                        }
                    }
                    else{
                        this->setAppRegistred(true);
                        emit this->appRegistredChanged(true);
                    }
                }
            }

            return;
        });


    });


}


void Settings::registerApp(){
    QJsonObject data;

    data["mac"]=m_ethMAC;
    data["installedversion"]=APPVERSION;
    data["buildinfo"]=BUILD_ID;
    data["hostname"]=QHostInfo::localHostName();

    QJsonDocument doc(data);


    m_socketIO->send("fromapp:registerapp",doc.toJson(QJsonDocument::Compact),[&](message::list const& msg) {


        if(msg.size()>0){

            message::ptr data=msg.at(0);
            if(data->get_flag() == message::flag_string){
                QString result=QString::fromStdString(data->get_string());

                QList<QString> results=result.split('|');

                if(results.length()>0 && results[0]=="NOK"){
                    if(results.length()>1 && results[1]=="NOT REGISTRED"){
                        this->setAppRegistred(false);
                        emit this->appRegistredChanged(false);
                    }
                }
                else{
                    this->setAppRegistred(true);
                    emit this->appRegistredChanged(true);
                }
            }
        }

        return;
    });



}

Settings::~Settings(){

}

bool Settings::load()
{

    LOG_INFO()<<"Loading setting from:"<<m_source;

    if(m_source.isEmpty()) {
        LOG_WARNING() << "Empty document: " << m_source;
        setLoaded(false);
        return false;
    }


    QFile settingsFile(m_source);


    if(!settingsFile.exists()) {
        LOG_WARNING() << "Does not exits: " << m_source;
        setLoaded(false);
        return false;
    }

    if (!settingsFile.open(QIODevice::ReadWrite)) {
        LOG_WARNING("Couldn't open save file.");
        settingsFile.close();
        return false;
    }

    QByteArray settingsData = settingsFile.readAll();

    settingsFile.close();

    QJsonDocument settings(QJsonDocument::fromJson(settingsData ));

    m_settingsobject=settings.object();

    read(m_settingsobject);

    setLoaded(true);

    return true;
}

bool Settings::save()
{
    LOG_INFO()<<"saving settings to:"<<m_source;
    QFile saveFile(m_source);

    if (!saveFile.open(QIODevice::ReadWrite)) {
        qWarning("Couldn't open save file.");
        saveFile.close();
        return false;
    }

    write(m_settingsobject);

    QJsonDocument saveDoc(m_settingsobject);


    QByteArray jsondoc = saveDoc.toJson();


    saveFile.write(jsondoc);

    saveFile.close();
    //    emit settingsSaved();
    return true;

}

void Settings::updateBaseSettings()
{

}

void Settings::loadBaseSettings()
{
    QFile basesettingsFile(m_appdir+"/appsettings.json");

    if(!basesettingsFile.exists()) {
        qWarning() << "Base file does not exits: " <<m_appdir;

        basesettingsFile.open(QIODevice::WriteOnly);
        QByteArray basesettingsData = basesettingsFile.readAll();

        QJsonDocument settings(QJsonDocument::fromJson(basesettingsData ));

        QJsonObject settingsobject=settings.object();

        settingsobject["location"]="";
        QJsonDocument saveDoc(settingsobject);
        QByteArray json = saveDoc.toJson();
        basesettingsFile.write(json);
        basesettingsFile.close();

    }

    if (!basesettingsFile.open(QIODevice::ReadWrite)) {
        qWarning("Couldn't open file.");
        basesettingsFile.close();
        return;
    }


    QByteArray basesettingsData = basesettingsFile.readAll();

    QJsonDocument settings(QJsonDocument::fromJson(basesettingsData ));

    QJsonObject settingsobject=settings.object();


    setSource(m_appdir+'/'+settingsobject["location"].toString());


    setBasefileLoaded(true);

    return;
}

void Settings::initSocketIO()
{
    m_socketIO->init();
}

void Settings::setBasefileLoaded(bool basefileLoaded)
{
    if (m_basefileLoaded == basefileLoaded)
        return;

    m_basefileLoaded = basefileLoaded;
    emit basefileLoadedChanged(m_basefileLoaded);

}

void Settings::read(QJsonObject &json)
{
    setSelectedanguage(json["language"].toString());



    m_appUpdater->DeSerialize(json);
    m_socketIO->DeSerialize(json);

    m_projects->clear();


    QJsonArray projectArray = json["projects"].toArray();
    for (int projectIndex = 0; projectIndex < projectArray.size(); ++projectIndex) {
        QJsonObject projectObject = projectArray[projectIndex].toObject();

        Project *project= new Project();
        project->DeSerialize(projectObject);

        m_projects->AddProject(project);

    }

    m_users->clear();

    QJsonArray usersArray = json["users"].toArray();
    for (int userIndex = 0; userIndex < usersArray.size(); ++userIndex) {
        QJsonObject userObject = usersArray[userIndex].toObject();

        User *user= new User();
        user->read(userObject);
        if(user->isDefault()){
            setCurrentUser(user);
        }
        m_users->AddUser(user);

    }



}

void Settings::write(QJsonObject &json) const
{
    // TODO SERIALIZE

    m_appUpdater->Serialize(json);
    m_socketIO->Serialize(json);



}



}// namespace
