include(config.pri)

message(----PLUGIN---)

PLUGIN_PATH=$${DEPLOY_PATH}/$$TARGET/

win32:{
    DESTDIR    = $$DEPLOY_PATH/dev/$$TARGET/lib
    DLLDESTDIR = $$DEPLOY_PATH
}else:{
    DESTDIR = $$PLUGIN_PATH
}





unix:!REMOTE_RPI{

    !BUILDROOT{
    #message($$PLUGIN_PATH)

        QMAKE_POST_LINK += $$quote(cp $$_PRO_FILE_PWD_/qml/qmldir $$PLUGIN_PATH$$escape_expand(\n\t))

        QMAKE_POST_LINK += $$quote(ln -s -f $${PLUGIN_PATH}lib$$qtLibraryTarget($$TARGET).so $$[QT_INSTALL_LIBS]/$$escape_expand(\n\t))
    }
}


unix{
    qmldir.files = qmldir

    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)

#    REMOTE_RPI{
#        #message($$[QT_INSTALL_LIBS])
#        installPath = $$DEPLOY_PATH/$$TARGET/
#    }

    qmldir.path = $$installPath
    target.path = $$installPath

    INSTALLS += target qmldir
}

