TEMPLATE = lib
TARGET = bsvalidationmodule
QT += qml quick
CONFIG += plugin c++14

PLUGIN_NAME = bsvalidationmodule
PLUGIN_PATH = bsvalidationmodule

CONFIG += plugin c++14


# PLUGIN_NAME and PLUGIN_PATH must be set up prior to including this config file
include($$getGlobalFile(plugin.pri))

DEFINES += BSVALIDATIONMODULE_LIB

uri = bsvalidationmoduleQuickQanava


linkLocalLibrary(automationstudiocore,   automationstudiocore)
linkLocalLibrary(CuteLogger,   CuteLogger)
linkLocalPlugin(automationmodule, automationmodule)
linkLocalPlugin(QuickQanava,   QuickQanava)


    # add custom path
    QMAKE_LFLAGS += -Wl,-rpath,$$TARGET_PATH/plugins/automationmodule
    QMAKE_LFLAGS += -Wl,-rpath,$$TARGET_PATH/plugins/QuickQanava

# Source

include($$PWD/src/bsvalidationmodule.pri)
include($$PWD/include/bsvalidationmoduleheaders.pri)

OTHER_FILES += \
    qml/*.qml \
    qml/qmldir


include($$PWD/../automationmodule/include/automationmoduleheaders.pri)

include($$PWD/../QuickQanava/include/quickqanavaheaders.pri)

RESOURCES += \
    src/bsvalidationmodule.qrc

qmldir.files = qmldir

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
