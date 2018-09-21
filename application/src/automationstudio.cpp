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

#include "automationstudio.h"


#include "automationstudiocore/keymap.h"

#include "automationstudiocore/settings.h"
#include "automationstudiocore/plugincontext.h"


#include <QUrl>
#include <QFileInfo>
#include <QDir>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>
#include <QGuiApplication>
#include <QPluginLoader>


namespace as{

AutomationStudio::AutomationStudio(QQmlApplicationEngine *engine, QObject *parent)
    : QObject(parent)
    , m_engine(engine)
    , m_settings(nullptr)
{
    m_currentDir=QCoreApplication::applicationDirPath();
    solveImportPaths();
    m_currentDir=m_currentDir+"/";
    QQmlContext* ctx{engine->rootContext()};
    ctx->setContextProperty("appDir", m_currentDir);
    m_settings= new Settings(this,m_currentDir+"/appsettings.json");
    m_systemSettings= new SystemSettings(this);


}

AutomationStudio::~AutomationStudio(){
    delete m_settings;
}

AutomationStudio::Ptr AutomationStudio::create(int argc, const char * const argv[], QQmlApplicationEngine *engine, QObject *parent){
    AutomationStudio::Ptr automationstudio = AutomationStudio::Ptr(new AutomationStudio(engine,parent));


    return automationstudio;
}

/**
 * Removes the application directory from the import paths. This is to avoid
 * having duplicate possible imports from within the application:
 *
 * \code
 * import automationstudio 1.0
 * \endcode
 *
 * \code
 * import plugins.automationmodules 1.0
 * \endcode
 */
void AutomationStudio::solveImportPaths(){
    QStringList importPaths = m_engine->importPathList();

    importPaths.removeAll(dir());
    importPaths.removeAll(PluginContext::executableDirPath());

    m_engine->setImportPathList(importPaths);

    // Add the plugins directory to the import paths
    m_engine->addImportPath(PluginContext::pluginPath());

    loadPlugins();
}

void AutomationStudio::loadPlugins(){
    QDir pluginsDir(PluginContext::pluginPath());


    qDebug()<<"Loading plugin modules";

    foreach (QString dirName, pluginsDir.entryList(QDir::Dirs)) {
        QString dirpath=pluginsDir.absoluteFilePath(dirName);
        QDir pluginsDirFiles(dirpath);

        foreach (QString fileName, pluginsDirFiles.entryList(QDir::Files)) {
            QPluginLoader pluginLoader(pluginsDirFiles.absoluteFilePath(fileName));
            QObject *plugin = pluginLoader.instance();
            if (plugin) {
                qDebug()<<"Plugin loaded:"<<plugin;
            }

        }


    }


}

void AutomationStudio::loadQml(const QUrl &url){

    m_engine->load(url);
}

void AutomationStudio::loadInternalPlugins(){

    qmlRegisterUncreatableType<as::AutomationStudio>(
                "base", 1, 0, "AutomationStudio", "AutomationStudio is available through the \'automationstudio\' property."
                );

    qmlRegisterUncreatableType<QCoreApplication>(
                "base", 1, 0, "QCoreApplication", "QCoreApplication is available through the \'automationstudio\' property."
                );


    qmlRegisterUncreatableType<as::Settings>(
                "base", 1, 0, "Settings", "Settings is available through the \'automationstudio.settings\' property."
                );

    qmlRegisterUncreatableType<SystemSettings >("base", 1, 0, "SystemSettings","SystemSettings is available through the \'automationstudio.systemsettings\' property.");

    m_engine->rootContext()->setContextProperty("appDir", m_currentDir);

    m_engine->rootContext()->setContextProperty("automationstudio",  this);

}



}// namespace
