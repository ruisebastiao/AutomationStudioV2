include(config.pri)

message(----PLUGIN---)

PLUGIN_PATH=$${DEPLOY_PATH}/$$TARGET/

win32:{
    DESTDIR    = $$DEPLOY_PATH/dev/$$TARGET/
    DLLDESTDIR = $$PLUGIN_PATH/../
}else:{
    DESTDIR = $$PLUGIN_PATH/../
}





unix{
    QMAKE_RPATHDIR += $ORIGIN
    QMAKE_POST_LINK += $$quote(mkdir -p $$DEPLOY_PATH/$$TARGET/$$escape_expand(\n\t))

    QMAKE_POST_LINK += $$quote(cp $$_PRO_FILE_PWD_/qml/qmldir $$DEPLOY_PATH/$$TARGET/$$escape_expand(\n\t))
}
else{

    targetdir=$$DEPLOY_PATH/$$TARGET
    exists($$targetdir){
        message(dir ok)
    }else{
     QMAKE_POST_LINK += $${QMAKE_MKDIR} $$replace(targetdir, /, $$QMAKE_DIR_SEP)$$escape_expand(\n\t))

    }
    targetdir=$$DEPLOY_PATH/$$TARGET
    sourcefile= $$_PRO_FILE_PWD_/qml/qmldir

    QMAKE_POST_LINK += $(COPY_FILE) \"$$replace(sourcefile, /, $$QMAKE_DIR_SEP)\" \"$$replace(targetdir, /, $$QMAKE_DIR_SEP)\" $$escape_expand(\n\t))

}




unix{
    qmldir.files = qmldir

    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)

    qmldir.path = $$installPath
    target.path = $$installPath
    !BUILDROOT{
        INSTALLS += target qmldir
    }
}

