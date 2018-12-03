
# Plugin build configuration,
# !!! Modify only if you know what you are doing
include($$PWD/../config.pri)


TEMPLATE = subdirs

# Optional build modules
CONFIG += ordered

SUBDIRS += \
    QuickQanava \
    automationmodule \
    guimodule \



PLUGIN-BSVALIDATION{
    message(With bsvalidation module)
    SUBDIRS += \
       bsvalidationmodule

}

PLUGIN-VISION{
    message(With vision module)
    SUBDIRS += \
       visionmodule

}


PLUGIN-EPSON{
    message(With Epson module)
    SUBDIRS += \
       epsonmodule

}


unix{
PLUGIN-NETWORKMANAGER{
    message(With network manager module)
    SUBDIRS += \
        networkmanager
    }
}

QML_IMPORT_PATH += \
                $${PLUGIN_DEPLOY_PATH}


# --- Subdir configuration ---
QuickQanava.subdir          = $$PWD/QuickQanava
automationmodule.subdir          = $$PWD/automationmodule

#include($$PWD/QuickQanava/src/quickqanava.pri)

# --- Dependency configuration ---
automationmodule.depends       = automationstudiocore
automationmodule.depends       = QuickQanava
automationmodule.depends       = guimodule
automationmodule.depends       = usbnotifier
bsvalidationmodule.depends     = automationmodule

PLUGIN-VISION{

   visionmodule.depends     = automationmodule
}

