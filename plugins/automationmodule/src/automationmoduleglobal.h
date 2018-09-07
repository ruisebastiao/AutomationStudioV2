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

#ifndef AUTOMATIONMODULEGLOBAL_H
#define AUTOMATIONMODULEGLOBAL_H

#include <qglobal.h>

#ifndef AUTOMATIONMODULE_STATIC
#  ifdef AUTOMATIONMODULE_LIB
#    define AUTOMATIONMODULE_EXPORT Q_DECL_EXPORT
#  else
#    define AUTOMATIONMODULE_EXPORT Q_DECL_IMPORT
#  endif
#else
#  define AUTOMATIONMODULE_EXPORT
#endif

#endif // AUTOMATIONMODULEGLOBAL_H
