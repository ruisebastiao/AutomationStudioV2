include(config.pri)

message(-----LIB----)
## Destination

win32:{
    DESTDIR    = $$DEPLOY_PATH/dev/$$TARGET/lib
    DLLDESTDIR = $$DEPLOY_PATH
}else:!RPI{
    DESTDIR = $$[QT_INSTALL_LIBS]
}


unix {
    target.path = $$[QT_SYSROOT]/usr/lib
    INSTALLS += target
}



