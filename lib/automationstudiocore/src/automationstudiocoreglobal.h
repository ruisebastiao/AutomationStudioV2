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

#ifndef AUTOMATIONSTUDIOCOREGLOBAL_H
#define AUTOMATIONSTUDIOCOREGLOBAL_H

#include <qglobal.h>

#ifndef AUTOMATIONSTUDIO_CORE_STATIC
#  ifdef AUTOMATIONSTUDIO_CORE_LIB
#    define AUTOMATIONSTUDIO_CORE_EXPORT Q_DECL_EXPORT
#  else
#    define AUTOMATIONSTUDIO_CORE_EXPORT Q_DECL_IMPORT
#  endif
#else
#  define AUTOMATIONSTUDIOCORE_EXPORT
#endif

#endif //AUTOMATIONSTUDIOCOREGLOBAL
