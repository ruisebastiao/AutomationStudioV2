
CONFIG      += warn_on qt thread c++14
# --- Project structure ---





TEMPLATE = subdirs

SUBDIRS += \
    application \
    lib \
    plugins

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
