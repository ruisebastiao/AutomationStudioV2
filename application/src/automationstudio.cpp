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
#include "automationstudiocore/visuallog.h"
#include "automationstudiocore/visuallogqt.h"
#include "automationstudiocore/visuallogmodel.h"
#include "automationstudiocore/visuallognetworksender.h"
#include "automationstudiocore/visuallogjsobject.h"
#include "automationstudiocore/engine.h"
#include "automationstudiocore/errorhandler.h"
#include "automationstudiocore/settings.h"
#include "automationstudiocore/plugincontext.h"


//#include "automationstudiocore/qmljssettings.h"
//#include "automationstudiocore/codeqmlhandler.h"
//#include "automationstudiocore/documentqmlinfo.h"
//#include "automationstudiocore/plugininfoextractor.h"

#include <QUrl>
#include <QFileInfo>
#include <QDir>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>
#include <QGuiApplication>


namespace as{

AutomationStudio::AutomationStudio(QObject *parent)
    : QObject(parent)
    , m_engine(new Engine(new QQmlApplicationEngine))
    , m_settings(nullptr)
{
     m_currentDir=QCoreApplication::applicationDirPath();//QDir::currentPath();
    solveImportPaths();

    m_settings= new Settings(this,m_currentDir+"/appsettings.json");
    m_systemSettings= new SystemSettings(this);


}

AutomationStudio::~AutomationStudio(){
    delete m_settings;
    delete m_engine;
}

AutomationStudio::Ptr AutomationStudio::create(int argc, const char * const argv[], QObject *parent){
    AutomationStudio::Ptr automationstudio = AutomationStudio::Ptr(new AutomationStudio(parent));


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
    QStringList importPaths = m_engine->engine()->importPathList();

    importPaths.removeAll(dir());
    importPaths.removeAll(PluginContext::executableDirPath());

    m_engine->engine()->setImportPathList(importPaths);

    // Add the plugins directory to the import paths
    m_engine->engine()->addImportPath(PluginContext::pluginPath());
}

void AutomationStudio::loadQml(const QUrl &url){


    static_cast<QQmlApplicationEngine*>(m_engine->engine())->load(url);
}

void AutomationStudio::loadInternalPlugins(){
    qmlRegisterType<as::ErrorHandler>(
        "base", 1, 0, "ErrorHandler");
    qmlRegisterUncreatableType<as::AutomationStudio>(
        "base", 1, 0, "AutomationStudio", "AutomationStudio is available through the \'automationstudio\' property."
    );


    qmlRegisterUncreatableType<as::Engine>(
        "base", 1, 0, "AutomationStudioEngine", "AutomationStudioEngine is available through \'automationstudio.engine\' property."
    );

    qmlRegisterUncreatableType<as::Settings>(
        "base", 1, 0, "Settings", "Settings is available through the \'automationstudio.settings\' property."
    );

    qmlRegisterUncreatableType<SystemSettings >("base", 1, 0, "SystemSettings","SystemSettings is available through the \'automationstudio.systemsettings\' property.");

    qmlRegisterUncreatableType<as::VisualLogModel>(
        "base", 1, 0, "VisualLogModel", "VisualLogModel is available through the \'automationstudio.log\' property."
    );


    m_engine->engine()->rootContext()->setContextProperty("appDir", m_currentDir);

    m_engine->engine()->rootContext()->setContextProperty("automationstudio",  this);

}



}// namespace
