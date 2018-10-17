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

#ifndef AUTOMATIONSTUDIO_H
#define AUTOMATIONSTUDIO_H

#include <QString>
#include <QLibrary>
#include <qpluginloader.h>

#include <automationstudiocore/systemsettings.h>
#include <automationstudiocore/socketio.h>

#include <automationstudiocore/utilities.h>
#include <QCoreApplication>


// Forward declarations
// --------------------

class QGuiApplication;
class QQmlApplicationEngine;
class QUrl;

namespace as{

class Engine;
class Settings;


// class AutomationStudio
// ------------

class AutomationStudio : public QObject{

    Q_OBJECT

    Q_PROPERTY(QCoreApplication* coreApplication READ coreApplication WRITE setCoreApplication NOTIFY coreApplicationChanged)

    Q_PROPERTY(as::Settings*       settings READ settings CONSTANT)

    Q_PROPERTY(as::Utilities*       utilities READ utilities CONSTANT)

    Q_PROPERTY(QString releaseVersion READ releaseVersion WRITE setReleaseVersion NOTIFY releaseVersionChanged)
    Q_PROPERTY(QString buildInfo READ buildInfo WRITE setBuildInfo NOTIFY buildInfoChanged)


    Q_PROPERTY(SystemSettings*  systemSettings READ systemSettings NOTIFY systemSettingsChanged)

public:
    typedef QSharedPointer<AutomationStudio>       Ptr;
    typedef QSharedPointer<const AutomationStudio> ConstPtr;

public:
    ~AutomationStudio();

    static AutomationStudio::Ptr create(int argc, const char* const argv[],QQmlApplicationEngine* engine, QObject* parent = nullptr);

    void loadQml(const QUrl& url);


    static QString header();



    const QString& dir() const;

    void loadInternalPlugins();


#ifdef RPI
    Q_INVOKABLE void reboot();
#endif


#ifdef RPI
    Q_INVOKABLE void halt();
#endif


    Settings* settings();
    QQmlApplicationEngine*   engine();


    SystemSettings* systemSettings() const
    {
        return m_systemSettings;
    }

    QCoreApplication* coreApplication() const
    {
        return m_coreApplication;
    }

    void loadPlugins();
    as::Utilities* utilities() const
    {
        return m_utilities;
    }

    QString releaseVersion() const
    {
        return m_releaseVersion;
    }

    QString buildInfo() const
    {
        return m_buildInfo;
    }

public slots:

    void setCoreApplication(QCoreApplication* coreApplication)
    {
        if (m_coreApplication == coreApplication)
            return;

        m_coreApplication = coreApplication;
        emit coreApplicationChanged(m_coreApplication);
    }

    void setReleaseVersion(QString releaseVersion)
    {
        if (m_releaseVersion == releaseVersion)
            return;

        m_releaseVersion = releaseVersion;
        emit releaseVersionChanged(m_releaseVersion);
    }

    void setBuildInfo(QString buildInfo)
    {
        if (m_buildInfo == buildInfo)
            return;

        m_buildInfo = buildInfo;
        emit buildInfoChanged(m_buildInfo);
    }

signals:
    void systemSettingsChanged(SystemSettings* systemSettings);

    void coreApplicationChanged(QCoreApplication* coreApplication);

    void releaseVersionChanged(QString releaseVersion);

    void buildInfoChanged(QString buildInfo);

private:
    AutomationStudio(QQmlApplicationEngine* engine,QObject* parent = nullptr);
    AutomationStudio(const AutomationStudio&);
    AutomationStudio& operator = (const AutomationStudio&);

    void parseArguments(const QStringList& arguments);
    void solveImportPaths();

    QQmlApplicationEngine*          m_engine;

    QString  m_dir;
    QPluginLoader* m_pluginLoader;
    as::Settings*          m_settings;
    QString m_currentDir="";

    SystemSettings* m_systemSettings=nullptr;

    QCoreApplication* m_coreApplication=nullptr;


    as::Utilities* m_utilities=nullptr;



    QString m_releaseVersion="";
    QString m_buildInfo="";
};


inline const QString &AutomationStudio::dir() const{
    return m_dir;
}


inline Settings *AutomationStudio::settings(){
    return m_settings;
}

inline QQmlApplicationEngine *AutomationStudio::engine(){
    return m_engine;
}


}// namespace

#endif // AUTOMATIONSTUDIO_H
