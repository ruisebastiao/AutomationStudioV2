include(config.pri)

message(-----LIB----)
## Destination

win32:{
    DESTDIR    = $$DEPLOY_PATH/dev/$$TARGET/lib
    DLLDESTDIR = $$DEPLOY_PATH
}else:DESTDIR = $$[QT_INSTALL_LIBS]


