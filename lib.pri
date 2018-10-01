include(config.pri)

message(-----LIB----)
## Destination

win32:{
    DESTDIR    = $$DEPLOY_PATH/dev/$$TARGET/
    DLLDESTDIR = $$DEPLOY_PATH
}else:!REMOTE_RPI{
        DESTDIR = $$DEPLOY_PATH
}


unix {
    QMAKE_RPATHDIR += $ORIGIN

    target.path = /usr/lib
    !BUILDROOT{
        INSTALLS += target
    }
}



