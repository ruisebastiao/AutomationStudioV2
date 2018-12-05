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

#include "automationmodule_plugin.h"
#include "usbnotifier.h"

#include <qqml.h>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQuickWindow>
#include <qautomationmodule.h>
#include <tcpclient.h>

#include "automationstudiocore/user.h"

#include <automationstudiocore/project.h>

#include <nodes/barcodereadernode.h>
#include <nodes/proxyinputnode.h>
#include <nodes/webservicenode.h>

#include <graphs/commonscenegraph.h>


void AutomationModulePlugin::registerTypes(const char *uri){
    // @uri modules.automationmodule

    qmlRegisterUncreatableType<User>(uri, 1, 0, "User","Cannot be created");
    qmlRegisterUncreatableType<Project>(uri, 1, 0, "Project","Cannot be created");

    qmlRegisterUncreatableType<QAutomationModule>(uri, 1, 0, "AutomationModule","Cannot be created");

//    qmlRegisterType<SceneGraph>(uri, 1, 0, "SceneGraph");

    qmlRegisterType<CommonSceneGraph>(uri, 1, 0, "CommonSceneGraph");

    qmlRegisterType<FlowNode>(uri, 1, 0, "FlowNode");
    qmlRegisterType<BarcodeReaderNode>(uri, 1, 0, "BarcodeReaderNode");
    qmlRegisterType<WebServiceNode>(uri, 1, 0, "WebServiceNode");
    qmlRegisterType<ProxyInputNode>(uri, 1, 0, "ProxyInputNode");


    qmlRegisterType<USBNotifier>(uri, 1, 0, "USBNotifier");

    qmlRegisterType<TCPClient>(uri, 1, 0, "TCPClient");
    qmlRegisterUncreatableType<QAbstractSocket>(uri, 1, 0, "QAbstractSocket","Cannot be created");


}

void AutomationModulePlugin::initializeEngine(QQmlEngine *engine, const char *){
    engine->addImportPath("qrc:///");
     QAutomationModule::flownodemanager=new FlowNodeManager();
}
