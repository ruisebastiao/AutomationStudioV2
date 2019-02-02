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
    $$PWD/nodes/cv/processingnode.cpp \
    $$PWD/nodes/framebuffernode.cpp \
    $$PWD/nodes/cv/processingbasenode.cpp \
    $$PWD/nodes/cv/processingthresholdnode.cpp \
    $$PWD/nodes/cv/processingdrawingnode.cpp \
    $$PWD/nodes/cv/processingfilternode.cpp \
    $$PWD/nodes/cv/processingendnode.cpp \
    $$PWD/nodes/cv/processingcontoursnode.cpp \
    $$PWD/nodes/cv/processingshapesnode.cpp \
    $$PWD/nodes/cv/processingenclosingnode.cpp \
    $$PWD/nodes/cv/processinggeometricnode.cpp \    
    $$PWD/nodes/cv/processingmasknode.cpp \
    $$PWD/graphs/processingscenegraph.cpp \
    $$PWD/graphs/visiongraph.cpp \
    $$PWD/graphs/visionmodulegraph.cpp \
    $$PWD/nodes/cv/cvserialization.cpp \
    $$PWD/nodes/cv/processingcannynode.cpp

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
    $$PWD/nodes/cv/processingnode.h \
    $$PWD/nodes/framebuffernode.h \
    $$PWD/nodes/cv/processingbasenode.h \
    $$PWD/nodes/cv/processingthresholdnode.h \
    $$PWD/nodes/cv/processingdrawingnode.h \
    $$PWD/nodes/cv/processingfilternode.h \
    $$PWD/nodes/cv/processingendnode.h \
    $$PWD/nodes/cv/processingcontoursnode.h \
    $$PWD/nodes/cv/processingshapesnode.h \
    $$PWD/nodes/cv/processingenclosingnode.h \
    $$PWD/nodes/cv/processinggeometricnode.h \
    $$PWD/nodes/cv/processingmasknode.h \
    $$PWD/graphs/processingscenegraph.h \
    $$PWD/graphs/visiongraph.h \
    $$PWD/graphs/visionmodulegraph.h \
    $$PWD/nodes/cv/cvserialization.h \
    $$PWD/nodes/cv/processingcannynode.h

RESOURCES += \
    $$PWD/visionmodule.qrc

DISTFILES += \
    $$PWD/qml/VisionModuleItem.qml \
    $$PWD/qml/nodes/FileCaptureNodeItem.qml \
    $$PWD/qml/nodes/FrameViewerNodeItem.qml \
    $$PWD/qml/nodes/IDSCaptureNodeItem.qml \
    $$PWD/qml/nodes/ROINodeItem.qml \
    $$PWD/qml/nodes/VisionSystemNodeItem.qml \
    $$PWD/qml/nodes/cv/ProcessingNodeItem.qml \
    $$PWD/qml/utils/ROIEditor.qml \
    $$PWD/qml/utils/ROIProcessingViewer.qml \    
    $$PWD/qml/cv/processing/postprocessing/PreProcessingContoursItem.qml

