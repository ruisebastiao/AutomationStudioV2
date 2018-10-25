
INCLUDEPATH+=$$PWD

unix:LIBS += -lboost_system
win32: LIBS += -lboost_system-vc140-mt-gd-x64-1_66 -L$$PWD/lib/
