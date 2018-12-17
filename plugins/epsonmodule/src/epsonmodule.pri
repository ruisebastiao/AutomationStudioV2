INCLUDEPATH += $$PWD

SOURCES += \
    $$PWD/qepsonmodule.cpp \
    $$PWD/epsonmodule_plugin.cpp \
    $$PWD/nodes/epsonnode.cpp \
    $$PWD/nodes/commandparsernode.cpp \
    $$PWD/nodes/commandsendernode.cpp \
    $$PWD/graph/epsongraph.cpp


HEADERS += \
    $$PWD/qepsonmodule.h \
    $$PWD/epsonmodule_plugin.h \
    $$PWD/nodes/epsonnode.h \
    $$PWD/nodes/commandparsernode.h \
    $$PWD/nodes/commandsendernode.h \
    $$PWD/graph/epsongraph.h


RESOURCES += \
    $$PWD/epsonmodule.qrc

DISTFILES += \
    $$PWD/qml/EpsonModuleItem.qml \


