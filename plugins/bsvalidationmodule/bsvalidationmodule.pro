PLUGIN_NAME = bsvalidationmodule
PLUGIN_PATH = bsvalidationmodule

# PLUGIN_NAME and PLUGIN_PATH must be set up prior to including this config file
include($$getGlobalFile(plugin.pri))

DEFINES += BSVALIDATIONMODULE_LIB

uri = bsvalidationmodule


linkLocalLibrary(automationstudiocore,   automationstudiocore)
linkLocalPlugin(automationmodule, automationmodule)

# Source

include($$PWD/src/bsvalidationmodule.pri)
include($$PWD/include/bsvalidationmoduleheaders.pri)

OTHER_FILES += \
    qml/*.qml \
    qml/qmldir

DISTFILES += \
    qml/plugins.qmltypes \
    qml/BSValidationModuleItem.qml


include($$PWD/../automationmodule/3rdparty/QuickQanava/src/quickqanavaheaders.pri)
