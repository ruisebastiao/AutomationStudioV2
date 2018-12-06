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

#include "qvisionmodule.h"
#include "visionmodule_plugin.h"

#include <qqml.h>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQuickWindow>

#include <nodes/idscamera.h>
#include <nodes/idscameralistmodel.h>
#include <nodes/roinode.h>

#include <cv/qimagefile.h>
#include <cv/qimread.h>
#include <cv/qmatview.h>

#include <nodes/cv/processingenclosingnode.h>
#include <nodes/cv/processinggeometricnode.h>
#include <nodes/cv/processingthresholdnode.h>

#include <graphs/processingscenegraph.h>


void VisionModulePlugin::registerTypes(const char *uri){
    // @uri modules.visionmodule
    qmlRegisterType<QVisionModule>(uri, 1, 0, "VisionModule");
    qmlRegisterType<IDSCamera>(uri, 1, 0, "IDSCamera");
    qmlRegisterType<IDSCameraListModel>(uri, 1, 0, "IDSCameraListModel");

    qmlRegisterType<QImRead>(uri, 1, 0, "QImRead");
    qmlRegisterType<QMatView>(uri, 1, 0, "QMatView");
    qmlRegisterType<QMatDisplay>(uri, 1, 0, "QMatDisplay");
    qmlRegisterType<QImageFile>(uri, 1, 0, "QImageFile");


    qmlRegisterType<ROINode>(uri, 1, 0, "ROINode");

    qmlRegisterType<ProcessingSceneGraph>(uri, 1, 0, "ProcessingSceneGraph");


    qmlRegisterUncreatableType<ProcessingThresholdNode>(uri, 1, 0, "ProcessingThresholdNode","Uncreatable");
    qmlRegisterUncreatableType<ProcessingEnclosingNode>(uri, 1, 0, "ProcessingEnclosingNode","Uncreatable");
    qmlRegisterUncreatableType<ProcessingGeometricNode>(uri, 1, 0, "ProcessingGeometricNode","Uncreatable");

//

    qRegisterMetaType<std::vector<std::vector<cv::Point>>>("std::vector<std::vector<cv::Point>>");

    qRegisterMetaType<cv::RotatedRect>("cv::RotatedRect");
    qRegisterMetaType<std::vector<cv::RotatedRect>>("std::vector<cv::RotatedRect>");

    qRegisterMetaType<cv::Rect>("cv::Rect");
    qRegisterMetaType<std::vector<cv::Rect>>("std::vector<cv::Rect>");


    qRegisterMetaType<QMat*>("QMat*");

    qRegisterMetaType<std::vector<cv::Point>>("std::vector<cv::Point>");



}

void VisionModulePlugin::initializeEngine(QQmlEngine *engine, const char *){
    engine->addImportPath("qrc:///");
}
