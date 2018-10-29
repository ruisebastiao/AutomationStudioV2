
include($$PROJECT_PATH/functions.pri)

INCLUDEPATH+=$$PWD

unix:LIBS += -lboost_system
win32:linkExternalLib(boost/lib,boost,_system-vc140-mt-gd-x64-1_66)
