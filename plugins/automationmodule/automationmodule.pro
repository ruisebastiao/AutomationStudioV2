TEMPLATE = lib
TARGET = automationmodule
QT += qml quick serialport
CONFIG += plugin c++14

TARGET = automationmodule

PLUGIN_NAME = automationmodule
PLUGIN_PATH = automationmodule

# PLUGIN_NAME and PLUGIN_PATH must be set up prior to including this config file
include($$getGlobalFile(plugin.pri))

DEFINES += AUTOMATIONMODULE_LIB

uri = automationmodule

linkLocalLibrary(automationstudiocore,   automationstudiocore)
linkLocalLibrary(CuteLogger,CuteLogger)
linkLocalPlugin(QuickQanava,   QuickQanava)


unix {
#QMAKE_LFLAGS += "-Wl,-rpath,\'\$$ORIGIN/plugins/QuickQanava\'"

#    QMAKE_LFLAGS_RPATH =
#    # add custom path
       QMAKE_LFLAGS += -Wl,-rpath,$$TARGET_PATH/plugins/QuickQanava

}




# Source

include($$PWD/src/automationmodule.pri)
include($$PWD/include/automationmoduleheaders.pri)

OTHER_FILES += \
    qml/*.qml \
    qml/qmldir


win32{
LIBS += -luser32
}

include($$PWD/../QuickQanava/include/quickqanavaheaders.pri)

RESOURCES += \
    src/automationmodule.qrc



!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qml/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}


#TARGET_PLUGIN_PATH=$$TARGET_PATH/plugins/$$PLUGIN_PATH

#qmldir.files = qmldir

#unix {
#    message($$TARGET_PLUGIN_PATH)
#    qmldir.path = $$TARGET_PLUGIN_PATH
#    target.path += $$TARGET_PLUGIN_PATH
#    INSTALLS += target qmldir
#}



