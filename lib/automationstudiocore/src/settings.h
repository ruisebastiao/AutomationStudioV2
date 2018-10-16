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
#include "automationstudiocoreglobal.h"

#include "projectslistmodel.h"
#include "socketio.h"
#include "userslistmodel.h"

namespace as{

class AUTOMATIONSTUDIO_CORE_EXPORT Settings : public QObject{

    Q_OBJECT

    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(bool loaded READ loaded WRITE setLoaded NOTIFY loadedChanged)
    Q_PROPERTY(bool basefileLoaded READ basefileLoaded  NOTIFY basefileLoadedChanged)





    Q_PROPERTY(ProjectsListModel* projects READ projects NOTIFY projectsChanged)
    Q_PROPERTY(QString sysInfo READ sysInfo)
    Q_PROPERTY(QString cpuType READ cpuType)
    Q_PROPERTY(QString ethMAC READ ethMAC)


    Q_PROPERTY(UsersListModel* users READ users NOTIFY usersChanged)
    Q_PROPERTY(User* currentUser READ currentUser WRITE setCurrentUser NOTIFY currentUserChanged)

    Q_PROPERTY(Project* selectedProject READ selectedProject WRITE setSelectedProject NOTIFY selectedProjectChanged)

    Q_PROPERTY(QString selectedLanguage READ selectedLanguage WRITE setSelectedanguage NOTIFY selectedLanguageChanged)


    Q_PROPERTY(bool useVirtualKeyboard READ useVirtualKeyboard WRITE setUseVirtualKeyboard NOTIFY useVirtualKeyboardChanged)


    Q_PROPERTY(SocketIO* socketIO READ socketIO WRITE setSocketIO NOTIFY socketIOChanged)
    Q_PROPERTY(bool appRegistred READ appRegistred NOTIFY appRegistredChanged)






public:
    Settings(QObject* parent = nullptr, QString baseconfigpath="");
    ~Settings();


    Q_INVOKABLE bool load(QString basePath="");
    Q_INVOKABLE bool save();
    Q_INVOKABLE void updateBaseSettings();
    Q_INVOKABLE void loadBaseSettings();
    Q_INVOKABLE void initSocketIO();

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

    ProjectsListModel* projects() const
    {
        return m_projects;
    }

    Project* selectedProject() const
    {
        return m_selectedProject;
    }



    SocketIO* socketIO() const
    {
        return m_socketIO;
    }

    QString ethMAC() const
    {
        return m_ethMAC;
    }

    bool appRegistred() const
    {
        return m_appRegistred;
    }

    Q_INVOKABLE void registerApp();
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

    void setSelectedProject(Project* selectedProject)
    {
        if (m_selectedProject == selectedProject)
            return;

        m_selectedProject = selectedProject;
        emit selectedProjectChanged(m_selectedProject);
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

signals:
    void sourceChanged(QString source);

    void loadedChanged(bool loaded);



    void usersChanged(UsersListModel* users);

    void currentUserChanged(User* currentUser);

    void selectedLanguageChanged(QString selectedLanguage);

    void useVirtualKeyboardChanged(bool useVirtualKeyboard);

    void basefileLoadedChanged(bool basefileLoaded);


    void projectsChanged(ProjectsListModel* projects);

    void selectedProjectChanged(Project* selectedProject);

    void socketIOServerChanged(QString socketIOServer);

    void socketIOChanged(SocketIO* socketIO);

    void appRegistredChanged(bool appRegistred);

private:

private:
    void read(QJsonObject &json);
    void write(QJsonObject &json) const;

    QString m_source;
    bool m_loaded=false;

    QString m_sysInfo="";
    QString m_baseconfigpath="";
    QString m_cpuType="";
    UsersListModel* m_users=nullptr;
    User* m_currentUser=nullptr;
    QString m_selectedLanguage="";
    bool m_useVirtualKeyboard=false;
    bool m_basefileLoaded=false;
    QJsonObject m_settingsobject;
    ProjectsListModel* m_projects=nullptr;
    Project* m_selectedProject=nullptr;

    SocketIO* m_socketIO=nullptr;
    QString m_ethMAC="";
    bool m_appRegistred=false;
};


}// namespace

#endif // LVSETTINGS_H
