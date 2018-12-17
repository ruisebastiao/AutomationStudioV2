INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/automationmodule

HEADERS += \
    $$PWD/automationmodule/qautomationmodule.h \
    $$PWD/automationmodule/projectslistmodel.h \
    $$PWD/automationmodule/flownodemanager.h \
    $$PWD/automationmodule/project.h \
    $$PWD/automationmodule/automationmoduleglobal.h \
    $$PWD/automationmodule/selectableedge.h \
    $$PWD/automationmodule/flownode.h \
    $$PWD/automationmodule/flownodeport.h \
    $$PWD/automationmodule/connectioninfo.h \
    $$PWD/automationmodule/scenegraph.h \
    $$PWD/automationmodule/tcpclient.h


include($$PWD/../../QuickQanava/include/quickqanavaheaders.pri)
