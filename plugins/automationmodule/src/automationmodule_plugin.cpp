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
#include "qprojectcontainer.h"
#include "usbnotifier.h"

#include <qqml.h>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQuickWindow>
#include <qautomationmodule.h>
#include <tcpclient.h>

#include "automationstudiocore/user.h"

#include <project.h>
#include <qqmlsortfilterproxymodel.h>

#include <nodes/barcodereadernode.h>
#include <nodes/logicnode.h>
#include <nodes/proxynode.h>
#include <nodes/stringnode.h>
#include <nodes/subprojectinfonode.h>
#include <nodes/webservicenode.h>

#include <filters/alloffilter.h>
#include <filters/anyoffilter.h>
#include <filters/expressionfilter.h>
#include <filters/indexfilter.h>
#include <filters/rangefilter.h>
#include <filters/regexpfilter.h>
#include <filters/valuefilter.h>

#include <proxyroles/expressionrole.h>
#include <proxyroles/filterrole.h>
#include <proxyroles/joinrole.h>
#include <proxyroles/regexprole.h>
#include <proxyroles/switchrole.h>

#include <sorters/expressionsorter.h>
#include <sorters/filtersorter.h>
#include <sorters/rolesorter.h>
#include <sorters/stringsorter.h>


QQmlEngine* AutomationModulePlugin::engine=nullptr;

void AutomationModulePlugin::registerTypes(const char *uri){
    // @uri modules.automationmodule

    qmlRegisterUncreatableType<User>(uri, 1, 0, "User","Cannot be created");
    qmlRegisterUncreatableType<Project>(uri, 1, 0, "Project","Cannot be created");
    qmlRegisterUncreatableType<SubProject>(uri, 1, 0, "SubProject","Cannot be created");

    qmlRegisterUncreatableType<QAutomationModule>(uri, 1, 0, "AutomationModule","Cannot be created");
    qmlRegisterType<QProjectContainer>(uri, 1, 0, "QProjectContainer");



    //    qmlRegisterType<SceneGraph>(uri, 1, 0, "SceneGraph");

    qmlRegisterType<SceneGraph>(uri, 1, 0, "SceneGraph");

    qmlRegisterType<FlowNode>(uri, 1, 0, "FlowNode");
    qmlRegisterType<LogicNode>(uri, 1, 0, "LogicNode");

    qmlRegisterType<BarcodeReaderNode>(uri, 1, 0, "BarcodeReaderNode");
    qmlRegisterType<WebServiceNode>(uri, 1, 0, "WebServiceNode");
    qmlRegisterType<ProxyNode>(uri, 1, 0, "ProxyInputNode");


    qmlRegisterType<USBNotifier>(uri, 1, 0, "USBNotifier");

    qmlRegisterType<TCPClient>(uri, 1, 0, "TCPClient");
    qmlRegisterUncreatableType<QAbstractSocket>(uri, 1, 0, "QAbstractSocket","Cannot be created");
    qmlRegisterUncreatableType<ModuleListModel>(uri, 1, 0, "ModuleListModel","Cannot be created");
    qmlRegisterUncreatableType<FlowNodeManager>(uri, 1, 0, "FlowNodeManager","Cannot be created");
    qmlRegisterUncreatableType<StringNode>(uri, 1, 0, "StringNode","Cannot be created");
    qmlRegisterUncreatableType<SubProjectInfo>(uri, 1, 0, "SubProjectInfo","Cannot be created");


    qmlRegisterType<QQmlSortFilterProxyModel>("SortFilterProxyModel", 1, 0, "SortFilterProxyModel");
    registerSorterTypes();
    registerFiltersTypes();
    registerProxyRoleTypes();

}


void AutomationModulePlugin::registerSorterTypes() {
    qmlRegisterUncreatableType<Sorter>("SortFilterProxyModel", 1,0, "Sorter", "Sorter is an abstract class");
    qmlRegisterType<RoleSorter>("SortFilterProxyModel", 1, 0, "RoleSorter");
    qmlRegisterType<StringSorter>("SortFilterProxyModel", 1, 0, "StringSorter");
    qmlRegisterType<FilterSorter>("SortFilterProxyModel", 1, 0, "FilterSorter");
    qmlRegisterType<ExpressionSorter>("SortFilterProxyModel", 1, 0, "ExpressionSorter");
}

void AutomationModulePlugin::registerFiltersTypes() {
    qmlRegisterUncreatableType<Filter>("SortFilterProxyModel", 1, 0, "Filter", "Filter is an abstract class");
    qmlRegisterType<ValueFilter>("SortFilterProxyModel", 1, 0, "ValueFilter");
    qmlRegisterType<IndexFilter>("SortFilterProxyModel", 1, 0, "IndexFilter");
    qmlRegisterType<RegExpFilter>("SortFilterProxyModel", 1, 0, "RegExpFilter");
    qmlRegisterType<RangeFilter>("SortFilterProxyModel", 1, 0, "RangeFilter");
    qmlRegisterType<ExpressionFilter>("SortFilterProxyModel", 1, 0, "ExpressionFilter");
    qmlRegisterType<AnyOfFilter>("SortFilterProxyModel", 1, 0, "AnyOf");
    qmlRegisterType<AllOfFilter>("SortFilterProxyModel", 1, 0, "AllOf");
}

void AutomationModulePlugin::registerProxyRoleTypes() {
    qmlRegisterUncreatableType<ProxyRole>("SortFilterProxyModel", 1, 0, "ProxyRole", "ProxyRole is an abstract class");
    qmlRegisterType<JoinRole>("SortFilterProxyModel", 1, 0, "JoinRole");
    qmlRegisterType<SwitchRole>("SortFilterProxyModel", 1, 0, "SwitchRole");
    qmlRegisterType<ExpressionRole>("SortFilterProxyModel", 1, 0, "ExpressionRole");
    qmlRegisterType<RegExpRole>("SortFilterProxyModel", 1, 0, "RegExpRole");
    qmlRegisterType<FilterRole>("SortFilterProxyModel", 1, 0, "FilterRole");
}



void AutomationModulePlugin::initializeEngine(QQmlEngine *engine, const char *){
    engine->addImportPath("qrc:///");
    AutomationModulePlugin::engine=engine;


    // Create a QDir that points out to your path in the resources folder
    QDir directory(":/AutomationModules/");

    // Load all files with the *.PNG extension
    // (you can modify this to suit your needs.
    QStringList availableModules = directory.entryList();

    for (int var = 0; var < availableModules.length(); ++var) {
        QString modulename=availableModules.at(var);
        modulename.replace("Item.qml","");
        availableModules.replace(var,modulename);
    }
    engine->rootContext()->setContextProperty("availableModules", availableModules);



    //     QAutomationModule::proxyFlowNodes;
}
