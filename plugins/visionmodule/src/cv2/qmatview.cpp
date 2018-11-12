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

#include "qmatview.h"
#include "qmatnode.h"
#include "qmatshader.h"
#include <QSGSimpleMaterial>

//TODO: Document

QMatView::QMatView(QQuickItem *parent)
    : QQuickItem(parent)
    , m_mat(QMat::nullMat())
    , m_linearFilter(true)
{
    setFlag(ItemHasContents, true);


}

QMatView::~QMatView(){
}

void QMatView::setMat(QMat *arg)
{
    if ( arg == 0 )
        return;
    m_sizeUpdated=false;
    cv::Mat* matData = arg->cvMat();
    if ( implicitWidth() != matData->cols || implicitHeight() != matData->rows ){
        setImplicitWidth(matData->cols);
        setImplicitHeight(matData->rows);
        setSizeUpdated(true);
    }
    m_mat = arg;
    update();
    emit matChanged(arg);

}

QSGNode *QMatView::updatePaintNode(QSGNode *node, QQuickItem::UpdatePaintNodeData *){
    QMatNode *n = static_cast<QMatNode*>(node);
    if (!node)
        n = new QMatNode();

    QSGGeometry::updateTexturedRectGeometry(n->geometry(), boundingRect(), QRectF(0, 0, 1, 1));
    QMatState* state = static_cast<QSGSimpleMaterial<QMatState>*>(n->material())->state();
    state->mat          = m_mat;
    state->textureSync  = false;
    state->linearFilter = m_linearFilter;
    n->markDirty(QSGNode::DirtyGeometry | QSGNode::DirtyMaterial);

    return n;
}

