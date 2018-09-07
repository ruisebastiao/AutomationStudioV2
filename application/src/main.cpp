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
#include <qquickstyle.h>

#include "automationstudio.h"


using namespace as;

int main(int argc, char *argv[]){
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QGuiApplication::addLibraryPath(as::PluginContext::librariesPath());
    QQuickStyle::setStyle("Material");
    QGuiApplication app(argc, argv);
    QGuiApplication::setApplicationName("Automation Studio");
    QGuiApplication::setApplicationVersion(AutomationStudio::versionString());

    try{

        AutomationStudio::Ptr automationstudio = AutomationStudio::create(argc, argv);
        automationstudio->loadInternalPlugins();

        //        if ( livecv->arguments()->helpFlag() ){
        //            printf("%s", qPrintable(livecv->arguments()->helpString()));
        //            return 0;
        //        } else if ( livecv->arguments()->versionFlag() ){
        //            printf("%s\n", qPrintable(livecv->versionString()));
        //            return 0;
        //        }

        LibraryLoadPath::addRecursive(PluginContext::pluginPath(), PluginContext::linkPath());
        if ( QFileInfo(PluginContext::externalPath()).exists() )
            LibraryLoadPath::addRecursive(PluginContext::externalPath(), PluginContext::linkPath());


        automationstudio->loadQml(QUrl(QStringLiteral("qrc:/main.qml")));

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
