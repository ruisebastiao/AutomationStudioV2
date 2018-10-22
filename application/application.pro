TEMPLATE = app
TARGET   = AutomationStudio
QT      += qml quick quickcontrols2 opengl
CONFIG +=c++14


include(../functions.pri)



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
}

unix{
    QMAKE_LFLAGS += "-Wl,-rpath,\'\$$ORIGIN\'"
}


# Application
# -----------

include($$PWD/src/main.pri)
include($$PWD/../lib/automationstudiocore/include/automationstudiocoreheaders.pri)
include($$PWD/../lib/CuteLogger/include/cuteloggerheaders.pri)

RESOURCES += $$PWD/application.qrc

OTHER_FILES += \
    $$PWD/qml/*.qml


configfiles.files+=\
    ../configfiles/appsettings.json \
    ../configfiles/bsvalidation.json \
    ../configfiles/projects.json

DISTFILES += \
    ../configfiles/appsettings.json \
    ../configfiles/bsvalidation.json \
    ../configfiles/projects.json



target.path = $${DEPLOY_PATH}
configfiles.path = $${DEPLOY_PATH}

RPI{
    target.path = $${DEPLOY_PATH}
    configfiles.path = $${DEPLOY_PATH}
    REMOTE-RPI{
        target.path = $$REMOTE_PATH
        configfiles.path = $$REMOTE_PATH

    }
    BUILDROOT{
    target.path = /root/AutomationStudio
    configfiles.path = /root/AutomationStudio
    }

}

unix{

    INSTALLS += target
}


WITH-CONFIGS{

    QMAKE_EXTRA_TARGETS += configfiles
    POST_TARGETDEPS += configfiles
    INSTALLS += configfiles
}



linkLocalLib(CuteLogger)
linkLocalLib(automationstudiocore)

LIBS += -lboost_system



message(Build id: $$BUILD_ID)


DO_PACKAGE{

message("Packaging app")

QMAKE_CLEAN += rm -r * $$DEPLOY_PATH/


release_filename=$${BUILD_ID}~$${PRORELEASEVERS}~.zip

PACKAGE_PATH=$$BUILD_PATH/release

QMAKE_POST_LINK += $$quote(mkdir -p $$PACKAGE_PATH$$escape_expand(\n\t))
QMAKE_POST_LINK += $$quote(cd $$DEPLOY_PATH/ && zip -r $$PACKAGE_PATH/$$release_filename ./ $$escape_expand(\n\t))
QMAKE_POST_LINK += $$quote(pscp -pw auto123 $$PACKAGE_PATH/$$release_filename automacao@keyeu-linux-svr:/home/automacao/automationstudiowebmanager/server/releases/$$escape_expand(\n\t))
#QMAKE_POST_LINK += $$quote(cp $$PACKAGE_PATH/$$release_filename /home/rui/projects/automationstudiowebmanager/server/releases/$$escape_expand(\n\t))

#QMAKE_POST_LINK += $$quote(tar -zcvf $$PACKAGE_PATH/$$release_filename -C $$DEPLOY_PATH/ ./ $$escape_expand(\n\t))
}






