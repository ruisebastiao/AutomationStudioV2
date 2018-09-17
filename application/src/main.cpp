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

#include <QtGui/QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QFileInfo>
#include <automationstudiocore/exception.h>
#include <automationstudiocore/libraryloadpath.h>
#include "automationstudiocore/plugincontext.h"
#include <ConsoleAppender.h>
#include <RollingFileAppender.h>
#include <qdir.h>
#include <qquickstyle.h>

#include "automationstudio.h"


using namespace as;

int main(int argc, char *argv[]){
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    QGuiApplication::addLibraryPath(as::PluginContext::librariesPath());
    QQuickStyle::setStyle("Material");
    QGuiApplication app(argc, argv);


    ConsoleAppender* consoleAppender = new ConsoleAppender;

    cuteLogger->registerAppender(consoleAppender);

    consoleAppender->setFormat("%{time}{yyyy-MM-ddTHH:mm:ss.zzz}|%{type:-7}|%{Function}|%{message}\n");

    QString m_currentDir=QCoreApplication::applicationDirPath();//QDir::currentPath();

    QString fileloggerpath=QDir(m_currentDir).filePath("app.log");

    qDebug()<<"log path:"<<fileloggerpath;
    RollingFileAppender* rollingfileAppender = new RollingFileAppender(fileloggerpath);

    rollingfileAppender->setDatePattern(RollingFileAppender::DailyRollover);
    rollingfileAppender->setLogFilesLimit(5);
    rollingfileAppender->setFormat("%{time}{yyyy-MM-ddTHH:mm:ss.zzz}|%{type:-7}|%{Function}|%{message}\n");
    rollingfileAppender->setDetailsLevel(Logger::Info);

    cuteLogger->registerAppender(rollingfileAppender );


    cuteLogger->registerCategoryAppender("qml",consoleAppender);
    cuteLogger->registerCategoryAppender("qml",rollingfileAppender);


    LOG_INFO("-----------Application Start-------------");


    QGuiApplication::setApplicationName("Automation Studio");
    QGuiApplication::setApplicationVersion(AutomationStudio::versionString());
    QQmlApplicationEngine engine;
    try{

        AutomationStudio::Ptr automationstudio = AutomationStudio::create(argc, argv,&engine);
        automationstudio->loadInternalPlugins();



        LibraryLoadPath::addRecursive(PluginContext::pluginPath(), PluginContext::linkPath());
        if ( QFileInfo(PluginContext::externalPath()).exists() )
            LibraryLoadPath::addRecursive(PluginContext::externalPath(), PluginContext::linkPath());


        automationstudio->loadQml(QUrl(QStringLiteral("qrc:/main.qml")));

        automationstudio->setCoreApplication(&app);

        return app.exec();

    } catch ( as::Exception& e ){
        if ( e.code() < 0 ){
            printf("Uncaught exception when initializing: %s\n", qPrintable(e.message()));
            return e.code();
        } else {
            //vlog() << "Uncaught exception: " << e.message();
            return e.code();
        }
    }
}
