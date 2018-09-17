TEMPLATE = app
TARGET   = AutomationStudio
QT      += qml quick quickcontrols2


linkLocalLibrary(automationstudiocore,   automationstudiocore)
linkLocalLibrary(CuteLogger,    CuteLogger)


win32{
    QML_IMPORT_PATH += $${DEPLOY_PATH}/plugins

}


unix:!macx{
linkPluginLibrary(QuickQanava,   QuickQanava)
linkPluginLibrary(automationmodule,   automationmodule)

# Load library paths
# ------------------
    QML_IMPORT_PATH += \
    /home/rui/Qt/5.10.1/gcc_64/qml

    QMAKE_LFLAGS += \
        '-Wl,-rpath,\'\$$ORIGIN\'' \
        '-Wl,-rpath,\'\$$ORIGIN/link\'' \
	'-Wl,-rpath,\'\$$ORIGIN/lib\''


    createlinkdir.commands += $${QMAKE_MKDIR_CMD} $$shell_path($${DEPLOY_PATH}/link)
    QMAKE_EXTRA_TARGETS    += createlinkdir
    POST_TARGETDEPS        += createlinkdir
}

macx{
    QMAKE_LFLAGS += \
        '-Wl,-rpath,\'@executable_path/../Link\'' \
        '-Wl,-rpath,\'@executable_path/../Frameworks\''

    createlinkdir.commands += $${QMAKE_MKDIR_CMD} $$shell_path($${DEPLOY_PATH}/Link)
    QMAKE_EXTRA_TARGETS    += createlinkdir
    POST_TARGETDEPS        += createlinkdir
}

DESTDIR = $$BUILD_PATH/bin

# Application
# -----------

include($$PWD/src/main.pri)

RESOURCES += $$PWD/application.qrc

OTHER_FILES += \
    $$PWD/qml/*.qml

