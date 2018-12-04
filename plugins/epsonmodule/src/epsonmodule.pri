INCLUDEPATH += $$PWD

SOURCES += \
    $$PWD/qepsonmodule.cpp \
    $$PWD/epsonmodule_plugin.cpp \
    $$PWD/nodes/epsonnode.cpp


HEADERS += \
    $$PWD/qepsonmodule.h \
    $$PWD/epsonmodule_plugin.h \
    $$PWD/nodes/epsonnode.h


RESOURCES += \
    $$PWD/epsonmodule.qrc

DISTFILES += \
    $$PWD/qml/EpsonModuleItem.qml \


