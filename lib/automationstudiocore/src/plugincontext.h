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

#ifndef LVPLUGINCONTEXT_H
#define LVPLUGINCONTEXT_H

#include "automationstudiocore/automationstudiocoreglobal.h"

class QQmlEngine;

namespace as{

class Settings;

class AUTOMATIONSTUDIO_CORE_EXPORT PluginContext{

public:
    static void initFromEngine(QQmlEngine* engine);

    static QQmlEngine*   engine();
    static as::Settings* settings();

    static QString executableDirPath();
    static QString applicationPath();
    static QString applicationFilePath();
    static QString linkPath();
    static QString pluginPath();
    static QString externalPath();
    static QString librariesPath();
    static QString developmentPath();
    static QString configPath();

private:
    static QString applicationFilePathImpl();

    PluginContext(){}

    static QQmlEngine*   m_engine;
    static as::Settings* m_settings;

    static QString m_applicationFilePath;
};

inline QQmlEngine *PluginContext::engine(){
    return m_engine;
}

inline Settings *PluginContext::settings(){
    return m_settings;
}

}// namespace

#endif // LVPLUGINCONTEXT_H
