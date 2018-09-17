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

#include <automationstudiocore/systemsettings.h>
#include <QCoreApplication>
// Versioning
// ----------

#define AUTOMATIONSTUDIO_VERSION_MAJOR 1
#define AUTOMATIONSTUDIO_VERSION_MINOR 5
#define AUTOMATIONSTUDIO_VERSION_PATCH 0

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
    Q_PROPERTY(SystemSettings*     systemSettings READ systemSettings NOTIFY systemSettingsChanged)

public:
    typedef QSharedPointer<AutomationStudio>       Ptr;
    typedef QSharedPointer<const AutomationStudio> ConstPtr;

public:
    ~AutomationStudio();

    static AutomationStudio::Ptr create(int argc, const char* const argv[],QQmlApplicationEngine* engine, QObject* parent = nullptr);

    void loadQml(const QUrl& url);

    static int versionMajor();
    static int versionMinor();
    static int versionPatch();
    static QString versionString();
    static QString header();

    const QString& dir() const;

    void loadInternalPlugins();



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

public slots:

    void setCoreApplication(QCoreApplication* coreApplication)
    {
        if (m_coreApplication == coreApplication)
            return;

        m_coreApplication = coreApplication;
        emit coreApplicationChanged(m_coreApplication);
    }

signals:
    void systemSettingsChanged(SystemSettings* systemSettings);

    void coreApplicationChanged(QCoreApplication* coreApplication);

private:
    AutomationStudio(QQmlApplicationEngine* engine,QObject* parent = nullptr);
    AutomationStudio(const AutomationStudio&);
    AutomationStudio& operator = (const AutomationStudio&);

    void parseArguments(const QStringList& arguments);
    void solveImportPaths();

    QQmlApplicationEngine*          m_engine;

    QString  m_dir;

    as::Settings*          m_settings;
    QString m_currentDir="";

    SystemSettings* m_systemSettings=nullptr;
    QCoreApplication* m_coreApplication=nullptr;
};

inline int AutomationStudio::versionMajor(){
    return AUTOMATIONSTUDIO_VERSION_MAJOR;
}

inline int AutomationStudio::versionMinor(){
    return AUTOMATIONSTUDIO_VERSION_MINOR;
}

inline int AutomationStudio::versionPatch(){
    return AUTOMATIONSTUDIO_VERSION_PATCH;
}

inline QString AutomationStudio::versionString(){
    return
            QString::number(versionMajor()) + "." +
            QString::number(versionMinor()) + "." +
            QString::number(versionPatch());
}

inline const QString &AutomationStudio::dir() const{
    return m_dir;
}


inline Settings *AutomationStudio::settings(){
    return m_settings;
}

inline QQmlApplicationEngine *AutomationStudio::engine(){
    return m_engine;
}


inline QString AutomationStudio::header(){
    return " AutomationStudio v" + versionString() + "\n"
                                                     " --------------------------------------------------- ";
}

}// namespace

#endif // AUTOMATIONSTUDIO_H
