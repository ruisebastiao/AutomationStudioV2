
# Plugin build configuration,
# !!! Modify only if you know what you are doing

TEMPLATE = subdirs

# Optional build modules
CONFIG += ordered

SUBDIRS += \
    QuickQanava \
    automationmodule \
    bsvalidationmodule \
    guimodule \

WITH-VISION{
    message(With vision module)
    SUBDIRS += \
       visionmodule

}


unix{
WITH-NETWORKMANAGER{
    message(With network manager)    
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

WITH-VISION{

   visionmodule.depends     = automationmodule
}

