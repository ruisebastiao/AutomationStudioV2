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
#include <QLocalSocket>
#include <QLocalServer>
#include <QQuickView>
//#include <automationstudiocore/libraryloadpath.h>
#include "automationstudiocore/plugincontext.h"
#include <ConsoleAppender.h>
#include <RollingFileAppender.h>
#include <qdir.h>
#include <qquickstyle.h>
#include "version.h"

#include "automationstudio.h"

#include "crash_handler.h"

//#include "qt_breakpad.h"



constexpr bool isequal(char const *one, char const *two) {
    return (*one && *two) ? (*one == *two && isequal(one + 1, two + 1))
                          : (!*one && !*two);
}

int buggyFunc() {
    delete reinterpret_cast<QString*>(0xFEE1DEAD);
    return 0;
}

bool isSingleInstanceRunning(QString appName) {
    QLocalSocket socket;
    int  error= socket.error();
    QString errorstr= socket.errorString();
    socket.connectToServer(appName);
    error= socket.error();
    errorstr= socket.errorString();

    bool isOpen = socket.isOpen();
    socket.close();
    return isOpen;
}

QLocalServer* startSingleInstanceServer(QString appName) {
    QLocalServer* server = new QLocalServer;
    server->setSocketOptions(QLocalServer::WorldAccessOption);
    server->listen(appName);
    return server;
}


int main(int argc, char *argv[]){




//      qRegisterMetaType<QVariant*>("QVariant*");


    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    QGuiApplication::addLibraryPath(PluginContext::librariesPath());

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QQuickStyle::setStyle("Material");

    QGuiApplication app(argc, argv);

    QGuiApplication::addLibraryPath(QCoreApplication::applicationDirPath());

    if(isSingleInstanceRunning(QGuiApplication::applicationName())){
         QQmlApplicationEngine engine;

         engine.load(QUrl(QStringLiteral("qrc:/errorMessage.qml")));

          return app.exec();
    }

    QLocalServer* singleinstaceserver=startSingleInstanceServer(QCoreApplication::applicationName());



    ConsoleAppender* consoleAppender = new ConsoleAppender;

    cuteLogger->registerAppender(consoleAppender);

    consoleAppender->setFormat("%{time}{yyyy-MM-ddTHH:mm:ss.zzz}|%{type:-7}|%{Function}|%{message}\n");

    QString m_currentDir=QCoreApplication::applicationDirPath();
    qDebug()<<"Crashes dir:"<<m_currentDir+"/crashes";



    QDir configsdir(m_currentDir);
    configsdir.cdUp();
    if(configsdir.exists("configs")==false){
        configsdir.mkdir("configs");
    }


    QString fileloggerpath=QDir(m_currentDir).filePath("app.log");

    qDebug()<<"log path:"<<fileloggerpath;


    QDir dumpsdir(m_currentDir);
    if(dumpsdir.exists("dumps")==false){
        dumpsdir.mkdir("dumps");
    }

    dumpsdir.cd("dumps");

    Breakpad::CrashHandler::instance()->Init(dumpsdir.absolutePath());

//    QtBreakpad::init(dumpsdir.absolutePath());


    //buggyFunc();


    //



    QFileInfo fi(fileloggerpath);

    auto fsize=fi.size()/(10*1024);

    if(fsize > 10){
        QFile file (fileloggerpath);
        file.remove();
    }

    //QProcess::startDetached("installer.exe");

    RollingFileAppender* rollingfileAppender = new RollingFileAppender(fileloggerpath);


    QString release(CURRENT_RELEASE);

    rollingfileAppender->setDatePattern(RollingFileAppender::DailyRollover);
    rollingfileAppender->setLogFilesLimit(5);
    rollingfileAppender->setFormat("%{time}{yyyy-MM-ddTHH:mm:ss.zzz}|%{type:-7}|%{Function}|%{message}\n");
    rollingfileAppender->setDetailsLevel(Logger::Info);

    cuteLogger->registerAppender(rollingfileAppender );


    cuteLogger->registerCategoryAppender("qml",consoleAppender);
    cuteLogger->registerCategoryAppender("qml",rollingfileAppender);




    LOG_INFO("-----------Application Start ("+release+")-------------");


    QGuiApplication::setApplicationName("Automation Studio");
    QGuiApplication::setApplicationVersion(release);

    try{
        QQmlApplicationEngine engine;

        AutomationStudio::Ptr automationstudio = AutomationStudio::create(argc, argv,&engine);
        automationstudio->loadInternalPlugins();


        automationstudio->loadQml(QUrl(QStringLiteral("qrc:/main.qml")));

        qDebug()<<"Main loaded";
        automationstudio->setCoreApplication(&app);


        int code=app.exec();
        if(singleinstaceserver){
            singleinstaceserver->close();
            delete singleinstaceserver;
        }

        return code;


    } catch (std::exception e){


        if(singleinstaceserver){
            singleinstaceserver->close();
            delete singleinstaceserver;
        }

        qDebug()<<"Error:"<<e.what();

    }


}
