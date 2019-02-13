TEMPLATE = app
TARGET   = AutomationStudio
QT      += qml quick quickcontrols2 opengl concurrent
CONFIG +=c++14


#include(../qt-breakpad/qt-breakpad.pri)

include(../functions.pri)
include(../versioning/gitversion.pri)


QML_IMPORT_PATH += $${DEPLOY_PATH}

win32{
DESTDIR = $${DEPLOY_PATH}

}

RPI{
    message(Raspberry build)
    DEFINES += RPI
}

unix{


    DESTDIR = $$DEPLOY_PATH
    QMAKE_LFLAGS += "-Wl,-rpath,\'\$$ORIGIN\'"
}


# Application
# -----------

include($$PWD/src/main.pri)
include($$PWD/../lib/automationstudiocore/include/automationstudiocoreheaders.pri)
include($$PWD/../lib/CuteLogger/include/cuteloggerheaders.pri)

include($$PWD/../plugins/automationmodule/include/automationmoduleheaders.pri)

RESOURCES += $$PWD/application.qrc

OTHER_FILES += \

    $$PWD/qml/*.qml

win32{

OTHER_FILES += \
    $$PWD/qml/*.qml

}




#configfiles.files+=\
#    ../configfiles/basesettings.json \
#    ../configfiles/bsvalidation.json \
#    ../configfiles/projects.json

#DISTFILES += \
#    ../configfiles/basesettings.json \
#    ../configfiles/bsvalidation.json \
#    ../configfiles/projects.json




target.path = $${DEPLOY_PATH}
configfiles.path = $${DEPLOY_PATH}

RPI{


    REMOTE-RPI{

        target.path = $$REMOTE_PATH
        configfiles.path = $$REMOTE_PATH

    }


}


unix{


!BUILDROOT{
   INSTALLS += target
}
}





WITH-CONFIGS{

    QMAKE_EXTRA_TARGETS += configfiles
    POST_TARGETDEPS += configfiles
    INSTALLS += configfiles
}



linkLocalLib(CuteLogger)
linkLocalLib(automationstudiocore)

linkLocalPlugin(automationmodule)



message(Build id: $$BUILD_ID)

message(App id: $$APP_ID)



DO_PACKAGE{

message("Packaging app")

unix:QMAKE_CLEAN += rm -r * $$DEPLOY_PATH/
#win32:QMAKE_CLEAN +=  $$quote(cd $$DEPLOY_PATH/ && RMDIR /Y /S /Q .$$escape_expand(\n\t))


release_filename=$${BUILD_ID}~$${PRORELEASEVERS}~.zip

PACKAGE_PATH=$$BUILD_PATH/release

WINPACKAGE_PATH=$$replace(PACKAGE_PATH, /, $$QMAKE_DIR_SEP)\

unix:QMAKE_POST_LINK += $$quote(mkdir -p $$PACKAGE_PATH$$escape_expand(\n\t))
win32:QMAKE_POST_LINK += $$quote(RMDIR /S /Q $$WINPACKAGE_PATH && mkdir $$WINPACKAGE_PATH $$escape_expand(\n\t))

unix{
    QMAKE_POST_LINK += $$quote(cd $$DEPLOY_PATH/../ && zip -x *.json *.log -r $$PACKAGE_PATH/$$release_filename ./bin/  $$escape_expand(\n\t))
}
win32{
    QMAKE_POST_LINK += $$quote(cd $$DEPLOY_PATH/../ && 7z a -r $$PACKAGE_PATH/$$release_filename ./bin/  -x!*.json -x!*.log $$escape_expand(\n\t))


}

QMAKE_POST_LINK += $$quote(pscp -pw auto123 $$PACKAGE_PATH/$$release_filename automacao@keyeu-linux-svr:/home/automacao/automationstudiowebmanager/server/releases/$$escape_expand(\n\t))
#win32:QMAKE_POST_LINK += $$quote(pscp -pw auto123 $$WINPACKAGE_PATH$$release_filename automacao@keyeu-linux-svr:/home/automacao/automationstudiowebmanager/server/releases/$$escape_expand(\n\t))

unix{
    QMAKE_POST_LINK += $$quote(cp $$PACKAGE_PATH/$$release_filename /home/rui/projects/automationstudiowebmanager/server/releases/$$escape_expand(\n\t))
}

}

DISTFILES += \
    qml/errorMessage.qml






