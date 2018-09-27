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

#include "plugincontext.h"

#include "settings.h"
#include <QQmlEngine>
#include <QQmlContext>
#include <QCoreApplication>
#include <QDir>

namespace as{

QString       PluginContext::m_applicationFilePath = "";
QQmlEngine*   PluginContext::m_engine   = nullptr;
as::Settings* PluginContext::m_settings = nullptr;

void PluginContext::initFromEngine(QQmlEngine *engine){
    QObject* automationstudio = engine->rootContext()->contextProperty("automationstudio").value<QObject*>();

    m_engine   = qobject_cast<QQmlEngine*>(automationstudio->property("engine").value<QObject*>());
    m_settings = qobject_cast<as::Settings*>(automationstudio->property("settings").value<QObject*>());

}

QString PluginContext::executableDirPath(){
    return QCoreApplication::applicationDirPath();
}

QString PluginContext::applicationPath(){
#ifdef Q_OS_DARWIN
    return QDir(QFileInfo(applicationFilePath()).path() + "/..").absolutePath();
#else
    return QFileInfo(applicationFilePath()).path();
#endif
}

QString PluginContext::applicationFilePath(){
    if ( m_applicationFilePath.isEmpty() )
        m_applicationFilePath = applicationFilePathImpl();

    return m_applicationFilePath;
}

QString PluginContext::linkPath(){
#ifdef Q_OS_DARWIN
    return applicationPath() + "/Link";
#else
    return applicationPath() + "/link";
#endif
}

QString PluginContext::pluginPath(){
#ifdef Q_OS_DARWIN
    return applicationPath() + "/PlugIns";
#else
    return applicationPath() + "/plugins";
#endif
}

QString PluginContext::externalPath(){
#ifdef Q_OS_DARWIN
    return applicationPath() + "/External";
#else
    return applicationPath() + "/external";
#endif
}

QString PluginContext::librariesPath(){
#ifdef Q_OS_DARWIN
    return applicationPath() + "/Libraries";
#else
    return applicationPath() + "/libraries";
#endif
}

QString PluginContext::developmentPath(){
#ifdef Q_OS_DARWIN
    return applicationPath() + "/Dev";
#else
    return applicationPath() + "/dev";
#endif
}

QString PluginContext::configPath(){
    return applicationPath() + "/config";
}


}// namespace
