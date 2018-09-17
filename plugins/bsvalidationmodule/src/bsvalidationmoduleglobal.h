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

#ifndef BSVALIDATIONMODULEGLOBAL_H
#define BSVALIDATIONMODULEGLOBAL_H

#include <qglobal.h>

#ifndef BSVALIDATIONMODULE_STATIC
#  ifdef BSVALIDATIONMODULE_LIB
#    define BSVALIDATIONMODULE_EXPORT Q_DECL_EXPORT
#  else
#    define BSVALIDATIONMODULE_EXPORT Q_DECL_IMPORT
#  endif
#else
#  define BSVALIDATIONMODULE_EXPORT
#endif

#endif // BSVALIDATIONMODULEGLOBAL_H
