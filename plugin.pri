include(config.pri)



PLUGIN_PATH=$${DEPLOY_PATH}/$$TARGET/
#QML_IMPORT_PATH += $${PLUGIN_PATH}
win32{
    DESTDIR    = $$DEPLOY_PATH/dev/$$TARGET/
    DLLDESTDIR = $$PLUGIN_PATH/../
}
unix{
    DESTDIR = $$PLUGIN_PATH/../
#    REMOTE-RPI:!DO_PACKAGE{
#        DESTDIR =
#    }

}





unix{
     QMAKE_LFLAGS += "-Wl,-rpath,\'\$$ORIGIN\'"


        QMAKE_POST_LINK += $$quote(mkdir -p $$DEPLOY_PATH/$$TARGET/$$escape_expand(\n\t))
        QMAKE_POST_LINK += $$quote(cp $$_PRO_FILE_PWD_/qml/qmldir $$DEPLOY_PATH/$$TARGET/$$escape_expand(\n\t))
}
else{

    sourcefile= $$_PRO_FILE_PWD_/qml/qmldir
    QMAKE_POST_LINK +=  $$quote(xcopy /Y \"$$replace(sourcefile, /, $$QMAKE_DIR_SEP)\" \"$$replace(PLUGIN_PATH, /, $$QMAKE_DIR_SEP)\" $$escape_expand(\n\t))

}




unix{
    qmldir.files = qmldir

    qmldirinstallPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
    plugininstallPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)

     REMOTE-RPI{
           qmldirinstallPath = $${REMOTE_PATH}/$$replace(uri, \\., /)
           plugininstallPath = $${REMOTE_PATH}
    }

    qmldir.path = $$qmldirinstallPath
    target.path = $$plugininstallPath
    !BUILDROOT{

        INSTALLS += target qmldir
    }
}

