INCLUDEPATH += $$PWD

SOURCES += \
    $$PWD/qvisionmodule.cpp \
    $$PWD/visionmodule_plugin.cpp \
    $$PWD/nodes/cameracapturenode.cpp \
    $$PWD/nodes/capturenode.cpp \
    $$PWD/nodes/filecapturenode.cpp \
    $$PWD/nodes/frameviewernode.cpp \
    $$PWD/nodes/idscamera.cpp \
    $$PWD/nodes/idscameralistmodel.cpp \
    $$PWD/nodes/idscapturenode.cpp \
    $$PWD/nodes/roinode.cpp \
    $$PWD/nodes/visionsystemnode.cpp \
    $$PWD/nodes/webcamcapturenode.cpp \
    $$PWD/cv/postprocessing.cpp \
    $$PWD/cv/postprocessingcontours.cpp \
    $$PWD/cv/preprocessing.cpp \
    $$PWD/cv/preprocessinggaussian.cpp \
    $$PWD/cv/preprocessingthreshold.cpp \
    $$PWD/cv/processing.cpp \
    $$PWD/cv/processinglistmodel.cpp \
    $$PWD/cv/qimagefile.cpp \
    $$PWD/cv/qimread.cpp \
    $$PWD/cv/qmat.cpp \
    $$PWD/cv/qmatdisplay.cpp \
    $$PWD/cv/qmatfilter.cpp \
    $$PWD/cv/qmatnode.cpp \
    $$PWD/cv/qmatread.cpp \
    $$PWD/cv/qmatroi.cpp \
    $$PWD/cv/qmatshader.cpp \
    $$PWD/cv/qmatstate.cpp \
    $$PWD/cv/qmatview.cpp \
    $$PWD/nodes/cv/processingcontoursnode.cpp \
    $$PWD/nodes/cv/processingnode.cpp \
    $$PWD/nodes/cv/processingshapesnode.cpp \
    $$PWD/nodes/cv/processingthresholdnode.cpp \
    $$PWD/nodes/cv/cannyedgesnode.cpp

HEADERS += \
    $$PWD/qvisionmodule.h \
    $$PWD/visionmodule_plugin.h \
    $$PWD/nodes/cameracapturenode.h \
    $$PWD/nodes/capturenode.h \
    $$PWD/nodes/filecapturenode.h \
    $$PWD/nodes/frameviewernode.h \
    $$PWD/nodes/idscamera.h \
    $$PWD/nodes/idscameralistmodel.h \
    $$PWD/nodes/idscapturenode.h \
    $$PWD/nodes/roinode.h \
    $$PWD/nodes/visionsystemnode.h \
    $$PWD/nodes/webcamcapturenode.h \
    $$PWD/cv/postprocessing.h \
    $$PWD/cv/postprocessingcontours.h \
    $$PWD/cv/preprocessing.h \
    $$PWD/cv/preprocessinggaussian.h \
    $$PWD/cv/preprocessingthreshold.h \
    $$PWD/cv/processing.h \
    $$PWD/cv/processinglistmodel.h \
    $$PWD/cv/qimagefile.h \
    $$PWD/cv/qimread.h \
    $$PWD/cv/qmat.h \
    $$PWD/cv/qmatdisplay.h \
    $$PWD/cv/qmatfilter.h \
    $$PWD/cv/qmatnode.h \
    $$PWD/cv/qmatread.h \
    $$PWD/cv/qmatroi.h \
    $$PWD/cv/qmatshader.h \
    $$PWD/cv/qmatstate.h \
    $$PWD/cv/qmatview.h \
    $$PWD/nodes/cv/processingcontoursnode.h \
    $$PWD/nodes/cv/processingnode.h \
    $$PWD/nodes/cv/processingshapesnode.h \
    $$PWD/nodes/cv/processingthresholdnode.h \
    $$PWD/nodes/cv/cannyedgesnode.h

RESOURCES += \
    $$PWD/visionmodule.qrc

DISTFILES += \
    $$PWD/qml/VisionModuleItem.qml \
    $$PWD/qml/nodes/FileCaptureNodeItem.qml \
    $$PWD/qml/nodes/FrameViewerNodeItem.qml \
    $$PWD/qml/nodes/IDSCaptureNodeItem.qml \
    $$PWD/qml/nodes/ROINodeItem.qml \
    $$PWD/qml/nodes/VisionSystemNodeItem.qml \
    $$PWD/qml/nodes/cv/ProcessingContoursNodeItem.qml \
    $$PWD/qml/nodes/cv/ProcessingNodeItem.qml \
    $$PWD/qml/nodes/cv/ProcessingShapesNodeItem.qml \
    $$PWD/qml/nodes/cv/ProcessingThresholdNodeItem.qml \
    $$PWD/qml/utils/ROIEditor.qml \
    $$PWD/qml/utils/ROIProcessingViewer.qml \
    $$PWD/qml/utils/ROISideContainer.qml
