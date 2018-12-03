#-------------------------------------------------
#
# Project created by QtCreator 2018-10-02T13:32:28
#
#-------------------------------------------------

TARGET = epsonmodule


QT += concurrent

DEFINES += EPSONMODULE_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

include(../../module.pri)



linkLocalPlugin(automationmodule)
include($$PWD/../automationmodule/include/automationmoduleheaders.pri)
linkLocalPlugin(QuickQanava)
include($$PWD/../QuickQanava/include/quickqanavaheaders.pri)

include(src/epsonmodule.pri)
