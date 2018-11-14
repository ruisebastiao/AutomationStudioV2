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

#ifndef QMATFILTER_H
#define QMATFILTER_H

#include "qmatdisplay.h"

class QMatFilter : public QMatDisplay{

    Q_OBJECT
    Q_PROPERTY(QMat* input READ inputMat WRITE setInputMat NOTIFY inputChanged)
    Q_PROPERTY(bool processing READ processing WRITE setProcessing NOTIFY processingChanged)

public:
    explicit QMatFilter(QQuickItem *parent = 0);
    virtual ~QMatFilter();
    
    QMat* inputMat();
    void setInputMat(QMat* mat);

    void transform();
    virtual void transform(const cv::Mat& in, cv::Mat& out);

    bool processing() const
    {
        return m_processing;
    }

public slots:


signals:
    void inputChanged();

    void processingChanged(bool processing);

protected:
    void componentComplete();

private:
    QMat* m_in=nullptr;
    void setProcessing(bool processing)
    {
        if (m_processing == processing)
            return;

        m_processing = processing;
        emit processingChanged(m_processing);
    }
    bool m_processing=false;
};

inline QMat *QMatFilter::inputMat(){
    return m_in;
}

inline void QMatFilter::setInputMat(QMat *mat){
    if ( mat == 0 )
        return;

    cv::Mat* matData = mat->cvMat();
    if ( implicitWidth() != matData->cols || implicitHeight() != matData->rows ){
        setImplicitWidth(matData->cols);
        setImplicitHeight(matData->rows);
    }
    m_in = mat;
    emit inputChanged();
    transform();
}

#endif // QMATFILTER_H
