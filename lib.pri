include(config.pri)

message(-----LIB----)
## Destination

win32:{
    DESTDIR    = $$DEPLOY_PATH/dev/$$TARGET/
    DLLDESTDIR = $$DEPLOY_PATH
}else:!REMOTE-RPI{
        DESTDIR = $$DEPLOY_PATH
}


unix {
     QMAKE_LFLAGS += "-Wl,-rpath,\'\$$ORIGIN\'"

    target.path = /usr/lib
    REMOTE-RPI{
        target.path = $$REMOTE_PATH
    }


    !BUILDROOT{
        INSTALLS += target
    }
}



