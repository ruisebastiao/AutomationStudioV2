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


#include <cv/processing/preprocessing/preprocessingthreshold.h>

#include <cv/processing/postprocessing/postprocessingcontours.h>

void VisionModulePlugin::registerTypes(const char *uri){
    // @uri modules.visionmodule
    qmlRegisterType<QVisionModule>(uri, 1, 0, "VisionModule");
    qmlRegisterType<IDSCamera>(uri, 1, 0, "IDSCamera");
    qmlRegisterType<IDSCameraListModel>(uri, 1, 0, "IDSCameraListModel");

    qmlRegisterType<QImRead>(uri, 1, 0, "QImRead");
    qmlRegisterType<QMatView>(uri, 1, 0, "QMatView");
    qmlRegisterType<QMatDisplay>(uri, 1, 0, "QMatDisplay");
    qmlRegisterType<QImageFile>(uri, 1, 0, "QImageFile");


    qmlRegisterUncreatableType<Processing>(uri, 1, 0, "Processing","Not creatable");

    qmlRegisterType<PreProcessingListModel>(uri, 1, 0, "PreProcessingListModel");
    qmlRegisterType<PostProcessingListModel>(uri, 1, 0, "PostProcessingListModel");


    qmlRegisterUncreatableType<PreProcessingThreshold>(uri, 1, 0, "PreProcessingThreshold","Not creatable");


    qmlRegisterUncreatableType<PostProcessingContours>(uri, 1, 0, "PostProcessingContours","Not creatable");



    qmlRegisterType<ROINode>(uri, 1, 0, "ROINode");


    qRegisterMetaType<std::vector<std::vector<cv::Point>>>("std::vector<std::vector<cv::Point>>");
    qRegisterMetaType<QMat*>("QMat*");

    qRegisterMetaType<std::vector<cv::Point>>("std::vector<cv::Point>");



}

void VisionModulePlugin::initializeEngine(QQmlEngine *engine, const char *){
    engine->addImportPath("qrc:///");
}
