include(config.pri)

message(----PLUGIN---)

PLUGIN_PATH=$${DEPLOY_PATH}/$$TARGET/

win32:{
    DESTDIR    = $$DEPLOY_PATH/dev/$$TARGET/
    DLLDESTDIR = $$PLUGIN_PATH/../
}else:!REMOTE-RPI{
    DESTDIR = $$PLUGIN_PATH/../
}





unix{
     QMAKE_LFLAGS += "-Wl,-rpath,\'\$$ORIGIN\'"

     !REMOTE-RPI{
        QMAKE_POST_LINK += $$quote(mkdir -p $$DEPLOY_PATH/$$TARGET/$$escape_expand(\n\t))
        QMAKE_POST_LINK += $$quote(cp $$_PRO_FILE_PWD_/qml/qmldir $$DEPLOY_PATH/$$TARGET/$$escape_expand(\n\t))
    }
}
else{

    sourcefile= $$_PRO_FILE_PWD_/qml/qmldir
    QMAKE_POST_LINK +=  $$quote(xcopy \"$$replace(sourcefile, /, $$QMAKE_DIR_SEP)\" \"$$replace(PLUGIN_PATH, /, $$QMAKE_DIR_SEP)\" $$escape_expand(\n\t))

}




unix{
    qmldir.files = qmldir

    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
     REMOTE-RPI{
           installPath = $${REMOTE_PATH}/$$replace(uri, \\., /)
    }

    qmldir.path = $$installPath
    target.path = $$installPath
    !BUILDROOT{

        INSTALLS += target qmldir
    }
}

