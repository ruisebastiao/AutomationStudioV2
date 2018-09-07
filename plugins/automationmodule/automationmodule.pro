TEMPLATE = lib
TARGET = automationmodule
QT += qml quick
CONFIG += plugin c++11

TARGET = automationmodule

PLUGIN_NAME = automationmodule
PLUGIN_PATH = automationmodule

# PLUGIN_NAME and PLUGIN_PATH must be set up prior to including this config file
include($$getGlobalFile(plugin.pri))

DEFINES += AUTOMATIONMODULE_LIB

uri = automationmodule

linkLocalLibrary(automationstudiocore,   automationstudiocore)
linkLocalPlugin(QuickQanava, QuickQanava)

# Source

include($$PWD/src/automationmodule.pri)
include($$PWD/include/automationmoduleheaders.pri)

OTHER_FILES += \
    qml/*.qml \
    qml/qmldir

DISTFILES += \
    qml/plugins.qmltypes \
    qml/AutomationModuleItem.qml



