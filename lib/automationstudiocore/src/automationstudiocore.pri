INCLUDEPATH += $$PWD


HEADERS += \
    $$PWD/libraryloadpath.h \
    $$PWD/settings.h \
    $$PWD/lockedfileiosession.h \
    $$PWD/plugincontext.h \
    $$PWD/filter.h \
    $$PWD/shareddata.h \
    $$PWD/filterworker.h \
    $$PWD/filterworker_p.h \
    $$PWD/keymap.h \
    $$PWD/automationstudiocoreglobal.h \
    $$PWD/systemsettings.h \
    $$PWD/user.h \
    $$PWD/userslistmodel.h \
    $$PWD/jsonserializable.h \
    $$PWD/utilities.h \
    $$PWD/socketio.h \
    $$PWD/appupdater.h \
    $$PWD/tcpclient.h \
    $$PWD/serializedlistmodel.h

SOURCES += \
    $$PWD/libraryloadpath.cpp \
    $$PWD/settings.cpp \
    $$PWD/lockedfileiosession.cpp \
    $$PWD/plugincontext.cpp \
    $$PWD/filter.cpp \
    $$PWD/shareddata.cpp \
    $$PWD/filterworker.cpp \
    $$PWD/keymap.cpp \
    $$PWD/systemsettings.cpp \
    $$PWD/user.cpp \
    $$PWD/userslistmodel.cpp \
    $$PWD/jsonserializable.cpp \
    $$PWD/utilities.cpp \
    $$PWD/socketio.cpp \
    $$PWD/appupdater.cpp \
    $$PWD/tcpclient.cpp \
    $$PWD/serializedlistmodel.cpp

win32{
    SOURCES +=
    SOURCES += $$PWD/libraryloadpath_win.cpp
    SOURCES += $$PWD/plugincontext_win.cpp
}

unix{
    !macx:SOURCES += $$PWD/plugincontext_unix.cpp
    SOURCES +=
    SOURCES += $$PWD/libraryloadpath_unix.cpp
}
macx:SOURCES += $$PWD/plugincontext_mac.cpp


