TEMPLATE = app
TARGET   = AutomationStudio
QT      += qml quick quickcontrols2 opengl
CONFIG +=c++14


include(../functions.pri)



QML_IMPORT_PATH += $${DEPLOY_PATH}

win32{


}

RPI{
    message(Raspberry build)
    DEFINES += RPI
}

unix:!macx{

#    RPI{
#        DESTDIR = $${TARGET_PATH}
#    }
}

#message(App:$$DEPLOY_PATH)

#QML_IMPORT_PATH += $$OUT_PWD/../plugins/

unix{
    target.path = $${DEPLOY_PATH}
    INSTALLS += target
}


unix:!RPI {
    DESTDIR = $$DEPLOY_PATH
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

target.path = $${DEPLOY_PATH}
configfiles.path = $${DEPLOY_PATH}

INSTALLS += target

WITH-CONFIGS{

    QMAKE_EXTRA_TARGETS += configfiles
    POST_TARGETDEPS += configfiles
    INSTALLS += configfiles
}

DISTFILES += \
    ../configfiles/appsettings.json \
    ../configfiles/bsvalidation.json \
    ../configfiles/projects.json


linkLocalLib(CuteLogger)
linkLocalLib(automationstudiocore)

#win32:CONFIG(release, debug|release): LIBS += -L$$DEPLOY_PATH -lCuteLogger
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$DEPLOY_PATH -lCuteLogger
#else:unix:!macx: LIBS += -L$$DEPLOY_PATH -lCuteLogger
#unix:!macx|win32: LIBS += -L$$DEPLOY_PATH -lautomationstudiocore
