INCLUDEPATH += $$PWD

SOURCES += \
    $$PWD/qepsonmodule.cpp \
    $$PWD/epsonmodule_plugin.cpp \
    $$PWD/nodes/epsonnode.cpp \    
    $$PWD/graph/epsongraph.cpp \
    $$PWD/nodes/epsonremote.cpp \
    $$PWD/nodes/toolnode.cpp


HEADERS += \
    $$PWD/qepsonmodule.h \
    $$PWD/epsonmodule_plugin.h \
    $$PWD/nodes/epsonnode.h \    
    $$PWD/graph/epsongraph.h \
    $$PWD/nodes/epsonremote.h \
    $$PWD/nodes/toolnode.h


RESOURCES += \
    $$PWD/epsonmodule.qrc

DISTFILES += \
    $$PWD/qml/EpsonModuleItem.qml \
    $$PWD/qml/nodes/ToolNodeItem.qml


