INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/exception.h \
    $$PWD/libraryloadpath.h \
    $$PWD/stacktrace.h \
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
    $$PWD/project.h \
    $$PWD/projectslistmodel.h \
    $$PWD/modulelistmodel.h \
    $$PWD/module.h \
    $$PWD/utilities.h

SOURCES += \
    $$PWD/exception.cpp \
    $$PWD/libraryloadpath.cpp \
    $$PWD/stacktrace.cpp \
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
    $$PWD/project.cpp \
    $$PWD/projectslistmodel.cpp \
    $$PWD/modulelistmodel.cpp \
    $$PWD/module.cpp \
    $$PWD/utilities.cpp

win32{
    SOURCES += $$PWD/stacktrace_win.cpp
    SOURCES += $$PWD/libraryloadpath_win.cpp
    SOURCES += $$PWD/plugincontext_win.cpp
}

unix{
    !macx:SOURCES += $$PWD/plugincontext_unix.cpp
    SOURCES += $$PWD/stacktrace_unix.cpp
    SOURCES += $$PWD/libraryloadpath_unix.cpp
}
macx:SOURCES += $$PWD/plugincontext_mac.cpp

