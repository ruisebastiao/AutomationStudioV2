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

#ifndef LVSHAREDDATA_H
#define LVSHAREDDATA_H

#include "automationstudiocoreglobal.h"

#include <QSet>

class QObject;
class QReadWriteLock;



class Filter;

//TODO: Optimize size

class AUTOMATIONSTUDIO_CORE_EXPORT SharedData{

public:
    SharedData();
    virtual ~SharedData();

    bool lockForRead(Filter* filter);
    bool lockForWrite(Filter* filter);

    void unlock(Filter* filter);

    QReadWriteLock* lock();
    void createLock();

private:
    void releaseObservers();
    QReadWriteLock* m_lock;

    Filter*       m_writer;
    QSet<Filter*> m_readers;
    QSet<Filter*> m_observers;
};



#endif // LVSHAREDDATA_H
