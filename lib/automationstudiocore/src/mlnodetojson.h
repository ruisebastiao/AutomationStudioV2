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

#ifndef LVMLNODETOJSON_H
#define LVMLNODETOJSON_H

#include "automationstudiocore/mlnode.h"

class QJsonValue;

namespace as{

namespace ml{

void AUTOMATIONSTUDIO_CORE_EXPORT toJson(const MLNode& n, QJsonValue& result);
void AUTOMATIONSTUDIO_CORE_EXPORT toJson(const MLNode& n, QByteArray& result);

void AUTOMATIONSTUDIO_CORE_EXPORT fromJson(const QJsonValue& value, MLNode& n);
void AUTOMATIONSTUDIO_CORE_EXPORT fromJson(const QByteArray& data,  MLNode& n);

}// namespace ml

}// namespace

#endif // LVMLNODETOJSON_H
