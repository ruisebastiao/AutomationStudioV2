

QMAKE_CXXFLAGS+=-DBOOST_SYSTEM_NO_DEPRECATED


CONFIG += ordered
CONFIG -= qml_debug

# --- Project structure ---

TEMPLATE = subdirs

SUBDIRS += \
    lib \
    plugins \
    application


# --- Subdir configurations ---
application.subdir  = $$PWD/application
plugins.subdir      = $$PWD/plugins


# --- Dependency configuration ---
application.depends = lib
application.depends = plugins
plugins.depends     = lib


OTHER_FILES += config.pri

OTHER_FILES += plugin.pri
OTHER_FILES += lib.pri

OTHER_FILES += functions.pri
OTHER_FILES += module.pri
OTHER_FILES += .qmake.conf






include($$PWD/functions.pri)

!qtVersionCheck(5, 11)::error( \
    This project requires at least Qt version 5.11. \
    Make sure you have Qt 5.11 installed and running the correct qmake. \
)




