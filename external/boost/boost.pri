

win32{
    INCLUDEPATH+=$$PWD
}
unix{
    LIBS += -lboost_system

}
win32:CONFIG(release, debug|release):LIBS += -L$$PWD/lib/ -llibboost_system-vc141-mt-x64-1_68
else:win32:CONFIG(debug, debug|release):LIBS += -L$$PWD/lib/ -llibboost_system-vc141-mt-gd-x64-1_68

#win32:linkExternalLib(boost/lib,boost,_system-vc140-mt-gd-x64-1_66)
