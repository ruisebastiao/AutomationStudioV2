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


#include "plugincontext.h"
#include "settings.h"


#include <QUrl>
#include <QFileInfo>
#include <QDir>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>
#include <QGuiApplication>
#include <QPluginLoader>
#include "version.h"

#include <automationstudiocore/utilities.h>




AutomationStudio::AutomationStudio(QQmlApplicationEngine *engine, QObject *parent)
    : QObject(parent)
    , m_engine(engine)
    , m_settings(nullptr)
{
    m_currentDir=QCoreApplication::applicationDirPath();

    setReleaseVersion(CURRENT_RELEASE);
    setBuildInfo(BUILD_ID);

    solveImportPaths();
    m_currentDir=m_currentDir+"/";
    QQmlContext* ctx{engine->rootContext()};

//    ctx->setContextProperty("appDir", m_currentDir);

    m_settings= new Settings(this,m_currentDir);
    m_systemSettings= new SystemSettings(this);
    m_utilities= new Utilities(this);

    m_appTranslator= new AppTranslator();


    m_appTranslator->setFilesLocation(m_currentDir+"i18n");

    connect(m_settings,&Settings::updateDone,this,[&](){

        this->coreApplication()->exit(1337);
        qApp->quit();

#ifndef RPI
        QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
#endif

    });







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
    //m_engine->addImportPath(PluginContext::pluginPath());
    QString appdir=PluginContext::executableDirPath();
    m_engine->addImportPath(appdir);

    loadPlugins();
}

void AutomationStudio::loadPlugins(){
    QDir pluginsDirFiles(PluginContext::executableDirPath());


    LOG_INFO()<<"Loading plugin modules";





    QPluginLoader pluginLoader;


    QStringList filters;
#if defined(Q_OS_WIN32)
    filters << "*.dll";
#endif


#if defined(Q_OS_LINUX)
    filters << "*.so*";

#endif


    pluginsDirFiles.setNameFilters(filters);


    foreach (QString fileName, pluginsDirFiles.entryList(QDir::Files | QDir::NoDotAndDotDot)) {
        QString filePath=pluginsDirFiles.absoluteFilePath(fileName);


        pluginLoader.setFileName(pluginsDirFiles.absoluteFilePath(filePath));
        pluginLoader.load();

        QObject *plugin = pluginLoader.instance();
        if (plugin) {
            LOG_INFO()<<"Plugin loaded:"<<plugin;

        }
        else{
            auto metadata=pluginLoader.metaData();
            if(metadata.size()>0){
                LOG_INFO()<<"Error loading plugin:"<<pluginLoader.errorString();
            }
        }

    }


}

void AutomationStudio::loadQml(const QUrl &url){

    m_engine->load(url);
}

void AutomationStudio::loadInternalPlugins(){

    qmlRegisterUncreatableType<AutomationStudio>(
                "base", 1, 0, "AutomationStudio", "AutomationStudio is available through the \'automationstudio\' property."
                );

    qmlRegisterUncreatableType<QCoreApplication>(
                "base", 1, 0, "QCoreApplication", "QCoreApplication is available through the \'automationstudio\' property."
                );


    qmlRegisterUncreatableType<Settings>(
                "base", 1, 0, "Settings", "Settings is available through the \'automationstudio.settings\' property."
                );

    qmlRegisterUncreatableType<Utilities>(
                "base", 1, 0, "Utilities", "Settings is available through the \'automationstudio.utilities\' property."
                );


    qmlRegisterUncreatableType<SystemSettings >("base", 1, 0, "SystemSettings","SystemSettings is available through the \'automationstudio.systemsettings\' property.");
    qmlRegisterUncreatableType<SocketIO>("base", 1, 0, "SocketIO","SocketIO");
    qmlRegisterUncreatableType<AppUpdater>("base", 1, 0, "AppUpdater","AppUpdater");

    qmlRegisterUncreatableType<AppTranslator>("base", 1, 0, "AppTranslator","AppTranslator");



    m_engine->rootContext()->setContextProperty("appDir", m_currentDir);

    m_engine->rootContext()->setContextProperty("automationstudio",  this);

}


#ifdef RPI

void AutomationStudio::reboot()
{

    this->utilities()->executeCommand("reboot",true);

    //QtConcurrent::run(executeProcess, QString("wpa_supplicant -D"+wpaDriver()+" -B -i wlan0 -c /etc/wpa_supplicant.conf"));
}

#endif

#ifdef RPI

void AutomationStudio::halt()
{

    this->utilities()->executeCommand("halt",false);

    //QtConcurrent::run(executeProcess, QString("wpa_supplicant -D"+wpaDriver()+" -B -i wlan0 -c /etc/wpa_supplicant.conf"));
}

#endif

