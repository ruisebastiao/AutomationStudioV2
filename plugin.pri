include(config.pri)

message(----PLUGIN---)
win32:{
    DESTDIR    = $$DEPLOY_PATH/dev/$$TARGET/lib
    DLLDESTDIR = $$DEPLOY_PATH
}else:!RPI{
    DESTDIR = $$DEPLOY_PATH/$$TARGET/
}



unix:!REMOTE_RPI{
    QMAKE_POST_LINK += $$quote(cp $${OUT_PWD}/qmldir $${DEPLOY_PATH}/$$TARGET/$$escape_expand(\n\t))

    QMAKE_POST_LINK += $$quote(ln -s -f $${DEPLOY_PATH}/$${TARGET}/lib$$qtLibraryTarget($$TARGET).so $$[QT_INSTALL_LIBS]/$$escape_expand(\n\t))
}


unix{
    qmldir.files = qmldir

    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)

    REMOTE_RPI{
#    message($$[QT_INSTALL_LIBS])
        installPath = $$DEPLOY_PATH/$$TARGET/
    }

    qmldir.path = $$installPath
    target.path = $$installPath

    INSTALLS += target qmldir
}

