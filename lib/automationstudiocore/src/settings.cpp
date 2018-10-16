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


Settings::Settings(QObject *parent, QString baseconfigpath)
    : QObject(parent)
{
    m_baseconfigpath=baseconfigpath;



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


    connect(m_socketIO,&SocketIO::socketIOConnected,this,[&](){

        QJsonObject data;

        data["mac"]=m_ethMAC;
        data["installedversion"]=APPVERSION;


        QJsonDocument doc(data);


        m_socketIO->send("fromunit:setinstalledversion",doc.toJson(QJsonDocument::Compact),[&](message::list const& msg) {


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
    data["hostname"]=QHostInfo::localHostName();

    QJsonDocument doc(data);


    m_socketIO->send("fromunit:registerapp",doc.toJson(QJsonDocument::Compact),[&](message::list const& msg) {


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

bool Settings::load(QString basePath)
{

    if(m_source.isEmpty()) {
        qWarning() << "Empty document: " << m_source;
        setLoaded(false);
        return false;
    }


    QFile settingsFile(basePath+'/'+m_source);
    if(!settingsFile.exists()) {
        qWarning() << "Does not exits: " << m_source;
        setLoaded(false);
        return false;
    }

    if (!settingsFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QByteArray settingsData = settingsFile.readAll();

    QJsonDocument settings(QJsonDocument::fromJson(settingsData ));

    m_settingsobject=settings.object();

    read(m_settingsobject);

    setLoaded(true);

    return true;
}

bool Settings::save()
{
    QFile saveFile(m_source);

    if (!saveFile.open(QIODevice::ReadWrite)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    write(m_settingsobject);

    QJsonDocument saveDoc(m_settingsobject);


    QByteArray jsondoc = saveDoc.toJson();


    saveFile.write(jsondoc);

    //    emit settingsSaved();
    return true;

}

void Settings::updateBaseSettings()
{

}

void Settings::loadBaseSettings()
{
    QFile basesettingsFile(m_baseconfigpath);

    if(!basesettingsFile.exists()) {
        qWarning() << "Base file does not exits: " <<m_baseconfigpath;

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

    if (!basesettingsFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open file.");
        return;
    }


    QByteArray basesettingsData = basesettingsFile.readAll();

    QJsonDocument settings(QJsonDocument::fromJson(basesettingsData ));

    QJsonObject settingsobject=settings.object();


    m_source=settingsobject["location"].toString();


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


}



}// namespace
