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

#ifndef LVSETTINGS_H
#define LVSETTINGS_H

#include <QObject>
#include <QMap>
#include <QUrl>
#include <projectslistmodel.h>


#include "appupdater.h"
#include "socketio.h"
#include "userslistmodel.h"

class  Settings : public QObject , public JsonSerializable {

    Q_OBJECT
    Q_INTERFACES(JsonSerializable)

    Q_PROPERTY(QString source READ source NOTIFY sourceChanged)
    Q_PROPERTY(bool useRemoteSettings READ useRemoteSettings WRITE setUseRemoteSettings NOTIFY useRemoteSettingsChanged)
    Q_PROPERTY(QString remoteSettingsBaseLocation READ remoteSettingsBaseLocation WRITE setRemoteSettingsBaseLocation NOTIFY remoteSettingsBaseLocationChanged)

    Q_PROPERTY(bool loaded READ loaded WRITE setLoaded NOTIFY loadedChanged)
    Q_PROPERTY(bool basefileLoaded READ basefileLoaded  NOTIFY basefileLoadedChanged)
    Q_PROPERTY(bool basefileError READ basefileError NOTIFY basefileErrorChanged)


    Q_PROPERTY(QString sysInfo READ sysInfo)
    Q_PROPERTY(QString cpuType READ cpuType)



    Q_PROPERTY(UsersListModel* users READ users WRITE setUsers NOTIFY usersChanged USER("serialize"))
    Q_PROPERTY(User* currentUser READ currentUser WRITE setCurrentUser NOTIFY currentUserChanged)

    Q_PROPERTY(QString selectedLanguage READ selectedLanguage WRITE setSelectedanguage NOTIFY selectedLanguageChanged USER("serialize"))
    Q_PROPERTY(bool useKeyboard READ useKeyboard WRITE setUseKeyboard NOTIFY useKeyboardChanged USER("serialize"))



    Q_PROPERTY(bool useVirtualKeyboard READ useVirtualKeyboard WRITE setUseVirtualKeyboard NOTIFY useVirtualKeyboardChanged)


    Q_PROPERTY(SocketIO* socketIO READ socketIO WRITE setSocketIO NOTIFY socketIOChanged)
    Q_PROPERTY(bool appRegistred READ appRegistred NOTIFY appRegistredChanged)

    Q_PROPERTY(AppUpdater*  appUpdater READ appUpdater WRITE setAppUpdater NOTIFY appUpdaterChanged USER("serialize"))

    Q_PROPERTY(QString appID READ appID NOTIFY appIDChanged)



    Q_PROPERTY(Project* selectedProject READ selectedProject WRITE setSelectedProject NOTIFY selectedProjectChanged)

    Q_PROPERTY(ProjectsListModel* projects READ projects WRITE setProjects NOTIFY projectsChanged USER("serialize"))


//    Q_PROPERTY(ProjectsListModel* projects READ projects WRITE setProjects NOTIFY projectsChanged)




public:
    Settings(QObject* parent = nullptr, QString appdir="");
    ~Settings();


    Q_INVOKABLE bool load();
    Q_INVOKABLE bool save();
    Q_INVOKABLE void updateBaseSettings();
    Q_INVOKABLE void loadBaseSettings();
    Q_INVOKABLE void initSocketIO();
    Q_INVOKABLE void backupConfigs();


    QString source() const
    {
        return m_source;
    }

    bool loaded() const
    {
        return m_loaded;
    }



    QString sysInfo() const
    {
        return m_sysInfo;
    }

    QString cpuType() const
    {
        return m_cpuType;
    }

    UsersListModel* users() const
    {
        return m_users;
    }

    User* currentUser() const
    {
        return m_currentUser;
    }

    QString selectedLanguage() const
    {
        return m_selectedLanguage;
    }

    bool useVirtualKeyboard() const
    {
        return m_useVirtualKeyboard;
    }

    bool basefileLoaded() const
    {
        return m_basefileLoaded;
    }

    void setBasefileLoaded(bool basefileLoaded);



    SocketIO* socketIO() const
    {
        return m_socketIO;
    }


    bool appRegistred() const
    {
        return m_appRegistred;
    }

    Q_INVOKABLE void registerApp();
    AppUpdater* appUpdater() const
    {
        return m_appUpdater;
    }

    QString appID() const
    {
        return m_appID;
    }

    QString projectsFile() const
    {
        return m_projectsFile;
    }

public slots:


    void setSource(QString source)
    {
        if (m_source == source)
            return;

        m_source = source;
        emit sourceChanged(m_source);
    }

    void setLoaded(bool loaded)
    {
        if (m_loaded == loaded)
            return;

        m_loaded = loaded;
        emit loadedChanged(m_loaded);
    }

    void setCurrentUser(User* currentUser)
    {
        if (m_currentUser == currentUser)
            return;

        m_currentUser = currentUser;
        emit currentUserChanged(m_currentUser);
    }

    void setSelectedanguage(QString selectedLanguage)
    {
        if (m_selectedLanguage == selectedLanguage)
            return;

        m_selectedLanguage = selectedLanguage;
        emit selectedLanguageChanged(m_selectedLanguage);
    }

    void setUseVirtualKeyboard(bool useVirtualKeyboard)
    {
        if (m_useVirtualKeyboard == useVirtualKeyboard)
            return;

        m_useVirtualKeyboard = useVirtualKeyboard;
        emit useVirtualKeyboardChanged(m_useVirtualKeyboard);
    }


    void setSocketIO(SocketIO* socketIO)
    {
        if (m_socketIO == socketIO)
            return;

        m_socketIO = socketIO;
        emit socketIOChanged(m_socketIO);
    }

    void setAppRegistred(bool appRegistred)
    {
        if (m_appRegistred == appRegistred)
            return;

        m_appRegistred = appRegistred;
        emit appRegistredChanged(m_appRegistred);
    }

    void setAppID(QString appID)
    {
        if (m_appID == appID)
            return;

        m_appID = appID;
        emit appIDChanged(m_appID);
    }

    void setProjectsFile(QString projectsFile)
    {
        if (m_projectsFile == projectsFile)
            return;

        m_projectsFile = projectsFile;
        emit projectsFileChanged(m_projectsFile);
    }

    void setProjects(ProjectsListModel* projects)
    {
        if (m_projects == projects)
            return;

        m_projects = projects;
        emit projectsChanged(m_projects);
    }

    void setUsers(UsersListModel* users)
    {


        m_users = users;
        emit usersChanged(m_users);
    }

    void setAppUpdater(AppUpdater* appUpdater)
    {
        if (m_appUpdater == appUpdater)
            return;

        m_appUpdater = appUpdater;
        emit appUpdaterChanged(m_appUpdater);
    }

    void setSelectedProject(Project* selectedProject)
    {
        if (m_selectedProject == selectedProject)
            return;

        if(m_selectedProject){
            m_selectedProject->unload();
        }

//        emit selectedProjectChanged(m_selectedProject);

        m_selectedProject = selectedProject;


        if(m_selectedProject){
            m_selectedProject->load();
        }

        emit selectedProjectChanged(m_selectedProject);

    }

    void setUseKeyboard(bool useKeyboard)
    {
        if (m_useKeyboard == useKeyboard)
            return;

        m_useKeyboard = useKeyboard;
        emit useKeyboardChanged(m_useKeyboard);
    }

    void setUseRemoteSettings(bool useRemoteSettings)
    {
        if (m_useRemoteSettings == useRemoteSettings)
            return;

        m_useRemoteSettings = useRemoteSettings;
        emit useRemoteSettingsChanged(m_useRemoteSettings);
    }



    void setRemoteSettingsBaseLocation(QString remoteSettingsBaseLocation)
    {
        if (m_remoteSettingsBaseLocation == remoteSettingsBaseLocation)
            return;

        m_remoteSettingsBaseLocation = remoteSettingsBaseLocation;
        emit remoteSettingsBaseLocationChanged(m_remoteSettingsBaseLocation);
    }

signals:
    void sourceChanged(QString source);

    void loadedChanged(bool loaded);



    void usersChanged(UsersListModel* users);

    void currentUserChanged(User* currentUser);

    void selectedLanguageChanged(QString selectedLanguage);

    void useVirtualKeyboardChanged(bool useVirtualKeyboard);

    void basefileLoadedChanged(bool basefileLoaded);


    void socketIOServerChanged(QString socketIOServer);

    void socketIOChanged(SocketIO* socketIO);

    void appRegistredChanged(bool appRegistred);


    void doUpdate(QString releasename);

    void updateDone();

    void appIDChanged(QString appID);

    void appUpdaterChanged(AppUpdater* appUpdater);

    void projectsFileChanged(QString projectsFile);

    void projectsChanged(ProjectsListModel* projects);

    void basefileErrorChanged(bool basefileError);

    void selectedProjectChanged(Project* selectedProject);

    void useKeyboardChanged(bool useKeyboard);

    void useRemoteSettingsChanged(bool useRemoteSettings);


    void remoteSettingsBaseLocationChanged(QString remoteSettingsBaseLocation);

private:

private:


    QString m_source;
    bool m_loaded=false;

    QString m_sysInfo="";
    QString m_appdir="";
    QString m_cpuType="";
    UsersListModel* m_users=nullptr;
    User* m_currentUser=nullptr;
    QString m_selectedLanguage="";
    bool m_useVirtualKeyboard=false;
    bool m_basefileLoaded=false;
    //    QJsonObject m_settingsobject;

    SocketIO* m_socketIO=nullptr;



    bool m_appRegistred=false;
    AppUpdater* m_appUpdater=nullptr;
    QString m_appID="";
    QString m_projectsFile;

    // JsonSerializable interface
    ProjectsListModel* m_projects=new ProjectsListModel(this);

    bool m_basefileError=false;

    Project* m_selectedProject=nullptr;

    bool m_useKeyboard=false;

    bool m_useRemoteSettings=false;



    QString m_remoteSettingsBaseLocation="/mnt/automationstudio/";

public:
    virtual void Serialize(QJsonObject &json) override;
    virtual void DeSerialize(QJsonObject &json) override;
    ProjectsListModel* projects() const
    {
        return m_projects;
    }
    bool basefileError() const
    {
        return m_basefileError;
    }
    Project* selectedProject() const
    {
        return m_selectedProject;
    }
    bool useKeyboard() const
    {
        return m_useKeyboard;
    }
    bool useRemoteSettings() const
    {
        return m_useRemoteSettings;
    }

    QString remoteSettingsBaseLocation() const
    {
        return m_remoteSettingsBaseLocation;
    }
};


#endif // LVSETTINGS_H
