
# Plugin build configuration,
# !!! Modify only if you know what you are doing

TEMPLATE = subdirs

# Optional build modules

SUBDIRS += \
    automationmodule \
    bsvalidationmodule \
    guimodule

QML_IMPORT_PATH += \
                $${PLUGIN_DEPLOY_PATH}


# --- Subdir configuration ---

automationmodule.subdir          = $$PWD/automationmodule

#include($$PWD/QuickQanava/src/quickqanava.pri)

# --- Dependency configuration ---

bsvalidationmodule.depends       = automationmodule

