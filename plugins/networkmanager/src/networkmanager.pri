 INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/networkmanager_plugin.h \
    $$PWD/networkmanagerglobal.h \
    $$PWD/networkinfo.h \
    $$PWD/networkmanager.h \
    $$PWD/networkslistmodel.h \
    $$PWD/os.h \
    $$PWD/scanresults.h \
    $$PWD/wpa_ctrl.h \
    $$PWD/wpa_debug.h \
    $$PWD/wpabuf.h \
    $$PWD/wpamsg.h \
    $$PWD/common.h \
    $$PWD/includes.h

SOURCES += \
    $$PWD/networkmanager_plugin.cpp \
    $$PWD/networkinfo.cpp \
    $$PWD/networkmanager.cpp \
    $$PWD/networkslistmodel.cpp \
    $$PWD/scanresults.cpp \
    $$PWD/os_unix.c \
    $$PWD/wpa_ctrl.c

