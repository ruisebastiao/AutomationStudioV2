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

#include "qepsonmodule.h"
#include "epsonmodule_plugin.h"

#include <qqml.h>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQuickWindow>

#include <nodes/epsonnode.h>
#include <nodes/epsonremote.h>


#include <graph/epsongraph.h>


void EpsonModulePlugin::registerTypes(const char *uri){
    // @uri modules.visionmodule
    qmlRegisterType<QEpsonModule>(uri, 1, 0, "EpsonModule");
    qmlRegisterUncreatableType<EpsonNode>(uri, 1, 0, "EpsonNode","Cannot be created");
    qmlRegisterUncreatableType<EpsonRemote>(uri, 1, 0, "EpsonRemote","Cannot be created");
    qmlRegisterUncreatableType<IONode>(uri, 1, 0, "IONode","Cannot be created");


    qmlRegisterType<EpsonGraph>(uri, 1, 0, "EpsonGraph");




}

void EpsonModulePlugin::initializeEngine(QQmlEngine *engine, const char *){
    engine->addImportPath("qrc:///");
}

//Q_DECLARE_METATYPE(EpsonNode);
