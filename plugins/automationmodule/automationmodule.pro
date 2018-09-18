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


# Source

include($$PWD/src/automationmodule.pri)
include($$PWD/include/automationmoduleheaders.pri)

OTHER_FILES += \
    qml/*.qml \
    qml/qmldir

DISTFILES += \
    qml/plugins.qmltypes \
    src/qml/AutomationModuleItem.qml \
    src/qml/nodes/BarcodeReaderNodeItem.qml \
    src/qml/nodes/FlowNodeItem.qml \
    src/qml/nodes/ObjectPropertyNodeItem.qml \
    src/qml/nodes/ProxyInputNodeItem.qml \
    src/qml/nodes/SetResetNodeItem.qml \
    src/qml/nodes/StringNodeItem.qml \
    src/qml/nodes/WebServiceNodeItem.qml \
    src/qml/edges/SelectableEdgeItem.qml \
    src/qml/nodes/ModulePropertyBindNodeItem.qml


win32{
LIBS += -luser32
}

include($$PWD/../QuickQanava/include/quickqanavaheaders.pri)

RESOURCES += \
    src/automationmodule.qrc

qmldir.files = qmldir

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qml/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

unix {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
    qmldir.path = $$installPath
    target.path = $$installPath

    INSTALLS += target qmldir
}


