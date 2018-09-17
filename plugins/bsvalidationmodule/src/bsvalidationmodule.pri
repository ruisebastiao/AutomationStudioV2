INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/bsvalidationmoduleglobal.h \
    $$PWD/bsvalidationmodule_plugin.h \
    $$PWD/qbsvalidationmodule.h \
    $$PWD/nodes/bsvalidationnode.h \
    $$PWD/nodes/bsvalidationvisualnode.h

SOURCES += \
    $$PWD/bsvalidationmodule_plugin.cpp \
    $$PWD/qbsvalidationmodule.cpp \
    $$PWD/nodes/bsvalidationnode.cpp \
    $$PWD/nodes/bsvalidationvisualnode.cpp

DISTFILES += \
    $$PWD/qml/BSValidationModuleItem.qml \
    $$PWD/qml/nodes/BSValidationNodeItem.qml \
    $$PWD/qml/nodes/BSValidationVisualNodeItem.qml
