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

#ifndef QMATDISPLAY_H
#define QMATDISPLAY_H

#include <QMutex>
#include <QQuickItem>
#include "qmat.h"

class QMatDisplay : public QQuickItem{

    Q_OBJECT
    Q_PROPERTY(QMat* output       READ output       WRITE setOutput       NOTIFY outputChanged)
    Q_PROPERTY(bool  linearFilter READ linearFilter WRITE setLinearFilter NOTIFY linearFilterChanged)

public:
    explicit QMatDisplay(QQuickItem *parent = 0);
    QMatDisplay(QMat* output, QQuickItem *parent = 0);
    virtual ~QMatDisplay();

    QMat* output();

    bool linearFilter() const;
    void setLinearFilter(bool filter);
    void setOutput(QMat* mat);

signals:
    void outputChanged();
    void linearFilterChanged();

protected:

    virtual QSGNode *updatePaintNode(QSGNode *node, UpdatePaintNodeData *nodeData);
    QMutex mutex;
private:
    QMat* m_output=nullptr;
    bool  m_linearFilter;

};

inline QMat *QMatDisplay::output(){
    return m_output;
}

inline void QMatDisplay::setOutput(QMat *mat){
    m_output = mat;
    emit outputChanged();
    update();
}

inline bool QMatDisplay::linearFilter() const{
    return m_linearFilter;
}

inline void QMatDisplay::setLinearFilter(bool filter){
    if ( filter != m_linearFilter ){
        m_linearFilter = filter;
        emit linearFilterChanged();
        update();
    }
}

#endif // QMATDISPLAY_H
