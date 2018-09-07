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
#include "automationstudiocore/automationstudiocoreglobal.h"

#include "userslistmodel.h"

namespace as{

class AUTOMATIONSTUDIO_CORE_EXPORT Settings : public QObject{

    Q_OBJECT

    Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(bool loaded READ loaded WRITE setLoaded NOTIFY loadedChanged)
    Q_PROPERTY(bool basefileLoaded READ basefileLoaded  NOTIFY basefileLoadedChanged)





   // Q_PROPERTY(ProjectsListModel* projects READ projects NOTIFY projectsChanged)
    Q_PROPERTY(QString sysInfo READ sysInfo)
    Q_PROPERTY(QString cpuType READ cpuType)

    Q_PROPERTY(UsersListModel* users READ users NOTIFY usersChanged)
    Q_PROPERTY(User* currentUser READ currentUser WRITE setCurrentUser NOTIFY currentUserChanged)

   // Q_PROPERTY(Project* selectedProject READ selectedProject WRITE setSelectedProject NOTIFY selectedProjectChanged)

    Q_PROPERTY(QString selectedLanguage READ selectedLanguage WRITE setSelectedanguage NOTIFY selectedLanguageChanged)


    Q_PROPERTY(bool useVirtualKeyboard READ useVirtualKeyboard WRITE setUseVirtualKeyboard NOTIFY useVirtualKeyboardChanged)



public:
    Settings(QObject* parent = nullptr, QString baseconfigpath="");
    ~Settings();


    Q_INVOKABLE bool load();
    Q_INVOKABLE bool save();
    Q_INVOKABLE void updateBaseSettings();
    Q_INVOKABLE void loadBaseSettings();

    QUrl source() const
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

public slots:


    void setSource(QUrl source)
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

signals:
    void sourceChanged(QUrl source);

    void loadedChanged(bool loaded);



    void usersChanged(UsersListModel* users);

    void currentUserChanged(User* currentUser);

    void selectedLanguageChanged(QString selectedLanguage);

    void useVirtualKeyboardChanged(bool useVirtualKeyboard);

    void basefileLoadedChanged(bool basefileLoaded);


private:


private:
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

    QUrl m_source;
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
};


}// namespace

#endif // LVSETTINGS_H
