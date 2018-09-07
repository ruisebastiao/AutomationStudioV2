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

#include <qqml.h>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQuickWindow>
#include <qautomationmodule.h>
//#include "automationstudiocore/systemsettings.h"
#include "automationstudiocore/user.h"


void AutomationModulePlugin::registerTypes(const char *uri){
    // @uri modules.automationmodule
    qmlRegisterUncreatableType<as::User>(uri, 1, 0, "User","Cannot be created");
    qmlRegisterType<QAutomationModule>(uri, 1, 0, "QAutomationModule");

}

void AutomationModulePlugin::initializeEngine(QQmlEngine *engine, const char *){

}
