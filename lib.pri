include(config.pri)

message(-----LIB----)
## Destination

win32:{
    DESTDIR    = $$DEPLOY_PATH/dev/$$TARGET/lib
    DLLDESTDIR = $$DEPLOY_PATH
}else:!REMOTE_RPI{
    DESTDIR = $$[QT_INSTALL_LIBS]
}

BUILDROOT{
    DESTDIR =
}

unix {
    target.path = /usr/lib
    INSTALLS += target
}



