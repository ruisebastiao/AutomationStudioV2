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
#include "version.h"

#include "Logger.h"
#include <QtConcurrent>
//#include <QtConcurrent>


Settings::Settings(QObject *parent, QString appdir)
    : QObject(parent)
{
    m_appdir=appdir;

    QString ethMAC;

    //    QString m_currentDir=QCoreApplication::applicationDirPath()+"/dumps";
    //    Breakpad::CrashHandler::instance()->Init(m_currentDir);

    foreach (QNetworkInterface interface, QNetworkInterface::allInterfaces()) {

        switch (interface.type()) {
        case QNetworkInterface::Ethernet:
            ethMAC=interface.hardwareAddress();
            LOG_INFO("hardwareAddress:"+ethMAC+"("+interface.name()+")");
            break;
        default:
            break;
        }

    }

    QString appid=QString(APP_ID);

    appid+=":"+QString(ethMAC);

    setAppID(appid);



    m_sysInfo=QSysInfo::kernelType();
    m_cpuType=QSysInfo::currentCpuArchitecture();

    // LOG_INFO("Running on "+m_sysInfo+"/"+m_cpuType);


    //    QList<QString> teste=Utilities::QtEnumsToStrings<User::UserRole>(false);


    m_users= new UsersListModel();

    m_socketIO= new SocketIO(this,appid);

    m_appUpdater= new AppUpdater(this);



    connect(m_appUpdater,&AppUpdater::updateDone,this,[&](){
        QJsonObject data;

        data["appid"]=this->appID();


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

        data["appid"]=appID();
        data["installedversion"]=RELEASEVERS;

        data["buildinfo"]=BUILD_ID;


        QJsonDocument doc(data);


        m_socketIO->send("fromapp:connected",doc.toJson(QJsonDocument::Compact),[&](message::list const& msg) {

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

    data["appid"]=appID();
    data["installedversion"]=RELEASEVERS;
    data["buildinfo"]=BUILD_ID;
    data["hostname"]=QHostInfo::localHostName();

    QJsonDocument doc(data);



    m_socketIO->send("fromapp:registerapp",doc.toJson(QJsonDocument::Compact),[&](message::list const& msg) {


        if(msg.size()>0){

            message::ptr data=msg.at(0);
            if(data->get_flag() == message::flag_string){
                QString result=QString::fromStdString(data->get_string());

                LOG_INFO()<<"registerstatus:"<<result;

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
    qDebug()<<"~Settings()";
    if(m_selectedProject){
        delete m_selectedProject;
    }
}

bool Settings::load()
{


    QString load_filepath;
    if(m_useRemoteSettings){

        load_filepath=remoteSettingsBaseLocation()+"/"+appID().replace(':','_')+"/"+m_source;

        QFileInfo target(load_filepath);
        QDir dir(target.dir());
        if (!dir.exists())
            dir.mkpath(".");


    }
    else {
        load_filepath=m_source;
    }



    LOG_INFO()<<"Loading setting from:"<<load_filepath;

    if(m_source.isEmpty()) {
        LOG_WARNING() << "Empty document: " << load_filepath;
        setLoaded(false);
        return false;
    }


    QFile settingsFile(load_filepath);


    if(!settingsFile.exists()) {
        LOG_ERROR() << "Does not exits: " << load_filepath;
        setLoaded(false);
        return false;
    }

    if (!settingsFile.open(QIODevice::ReadOnly)) {
        LOG_ERROR("Couldn't open save file.");
        settingsFile.close();
        return false;
    }

    QByteArray settingsData = settingsFile.readAll();



    QJsonDocument settings(QJsonDocument::fromJson(settingsData ));


    if(settings.isNull()){
        LOG_ERROR("Failed to create JSON doc");
        return false;
    }

    if (!settings.isObject()) {
        LOG_ERROR() << "JSON is not an object.";
        return false;
    }


    QJsonObject settingsobject=settings.object();

    settingsFile.close();


    if (settingsobject.isEmpty()) {
        LOG_ERROR()<< "JSON object is empty.";

        return false;
    }

    DeSerialize(settingsobject);



    setLoaded(true);

    return true;
}

bool Settings::save()
{



    QFile basesettingsFile(QDir(QCoreApplication::applicationDirPath()).filePath("basesettings.json"));


    if(basesettingsFile.exists()) {


        basesettingsFile.open(QIODevice::WriteOnly);
        QByteArray basesettingsData = basesettingsFile.readAll();

        QJsonDocument settings(QJsonDocument::fromJson(basesettingsData ));

        QJsonObject settingsobject=settings.object();

        settingsobject["location"]=source();
        settingsobject["useRemoteSettings"]=useRemoteSettings();
        settingsobject["remoteSettingsBaseLocation"]=remoteSettingsBaseLocation();
        QJsonDocument saveDoc(settingsobject);
        QByteArray json = saveDoc.toJson();
        basesettingsFile.write(json);
        basesettingsFile.close();

    }

    QString save_filepath;
    if(m_useRemoteSettings){
        save_filepath=remoteSettingsBaseLocation()+"/"+appID().replace(':','_')+"/"+m_source;

    }
    else {
        save_filepath=m_source;
    }


    LOG_INFO()<<"saving settings to:"<<save_filepath;

    QJsonObject json;

    Serialize(json);

    QJsonDocument saveDoc(json);



    QByteArray jsondoc = saveDoc.toJson();



    QFile saveFile(save_filepath);

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning()<<"Couldn't open save file."<<save_filepath;
        saveFile.close();
        return false;
    }


    saveFile.write(jsondoc);




    return true;

}

void Settings::updateBaseSettings()
{

}

void Settings::loadBaseSettings()
{


    QFile basesettingsFile(QDir(QCoreApplication::applicationDirPath()).filePath("basesettings.json"));


    if(!basesettingsFile.exists()) {
        qWarning() << "Base file does not exits: " <<m_appdir;

        basesettingsFile.open(QIODevice::WriteOnly);
        QByteArray basesettingsData = basesettingsFile.readAll();

        QJsonDocument settings(QJsonDocument::fromJson(basesettingsData ));

        QJsonObject settingsobject=settings.object();

        settingsobject["location"]="";
        settingsobject["remoteSettingsBaseLocation"]="";
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



    QDir appdir=QDir(QCoreApplication::applicationDirPath());

    appdir.makeAbsolute();

    QDir::setCurrent(QCoreApplication::applicationDirPath());






    setUseRemoteSettings(settingsobject["useRemoteSettings"].toBool());

    setRemoteSettingsBaseLocation(settingsobject["remoteSettingsBaseLocation"].toString());


    setSource(appdir.cleanPath(settingsobject["location"].toString()));




    setBasefileLoaded(true);



    if (m_useRemoteSettings){


#ifdef RPI

        connect(&watcher, &QFutureWatcher<void>::finished, this, [this](){
            load();
        });

        QFuture<void> future = QtConcurrent::run([this](){
            bool ismounted=false;
            Utilities utils;
            do{
                utils.executeCommand("cat /proc/mounts",true,"",true,false,[&](QString line){
                    if(line.contains(QDir::cleanPath(remoteSettingsBaseLocation()))){
                        ismounted=true;
                    }
                    else{
                        LOG_INFO()<<line;
                        utils.executeCommand("mount -t cifs -o username=automationstudio,password=auto123 //keyeu-linux-svr/automationstudio /mnt/automationstudio",true,"",true,false,[&](QString line_2){
                            LOG_INFO()<<line_2;
                        });

                    }
                });

                QThread::msleep(1000);
            }
            while(ismounted==false);
        });

        watcher.setFuture(future);



#else
        load();
#endif




    }
    else {
        load();
    }






    return;
}

void Settings::initSocketIO()
{
    m_socketIO->init();
}

void Settings::backupConfigs()
{

    m_appUpdater->backupConfigs(appID());
}

void Settings::setBasefileLoaded(bool basefileLoaded)
{
    if (m_basefileLoaded == basefileLoaded)
        return;

    m_basefileLoaded = basefileLoaded;
    emit basefileLoadedChanged(m_basefileLoaded);

}

void Settings::Serialize(QJsonObject &json)
{
    JsonSerializable::Serialize(json,this);
}

void Settings::DeSerialize(QJsonObject &json)
{
    JsonSerializable::DeSerialize(json,this);

    m_socketIO->setServerUrl(appUpdater()->serverUrl());

    for (int var = 0; var < m_users->length(); ++var) {
        User* user=m_users->at(var);
        if(user->isDefault()){
            setCurrentUser(m_users->at(var));
            break;
        }
    }


    for (int var = 0; var < m_projects->length(); ++var) {
        if(m_projects->at(var)->isDefault()){
            setSelectedProject(m_projects->at(var));
            break;
        }
    }


}

