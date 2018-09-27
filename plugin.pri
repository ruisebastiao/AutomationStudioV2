include(config.pri)

message(----PLUGIN---)
win32:{
    DESTDIR    = $$DEPLOY_PATH/dev/$$TARGET/lib
    DLLDESTDIR = $$DEPLOY_PATH
}else:!RPI{
    DESTDIR = $$DEPLOY_PATH/$$TARGET/
}



unix:!REMOTE_RPI{

    PLUGIN_PATH=$$[QT_SYSROOT]$${DEPLOY_PATH}/$$TARGET/

    #message($$PLUGIN_PATH)

    QMAKE_POST_LINK += $$quote(cp $$_PRO_FILE_PWD_/qml/qmldir $$PLUGIN_PATH$$escape_expand(\n\t))

    QMAKE_POST_LINK += $$quote(ln -s -f $${PLUGIN_PATH}lib$$qtLibraryTarget($$TARGET).so $$[QT_INSTALL_LIBS]/$$escape_expand(\n\t))
}


unix{
    qmldir.files = qmldir

    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)

    REMOTE_RPI{
        #message($$[QT_INSTALL_LIBS])
        installPath = $$DEPLOY_PATH/$$TARGET/
    }

    qmldir.path = $$installPath
    target.path = $$installPath

    INSTALLS += target qmldir
}
