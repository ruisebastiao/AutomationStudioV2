TEMPLATE = lib
TARGET   = automationstudiocore
QT      += core qml quick concurrent
CONFIG  += qt c++14

include(../../functions.pri)

include(../../lib.pri)


RPI{
    message(is raspberry)
    DEFINES += RPI
}

#TODO
#include($$PROJECT_PATH/shared/crashhandler/crash_handler.pri)


DEFINES += AUTOMATIONSTUDIO_CORE_LIB

include($$PWD/src/automationstudiocore.pri)



linkLocalLib(sioclient)
linkLocalLib(quazip)


include($$PWD/../../lib/CuteLogger/include/cuteloggerheaders.pri)
linkLocalLib(CuteLogger)



include($$PWD/../socket.io-client-cpp/socket.io-client-cpp-headers.pri)


#unix:QMAKE_POST_LINK += $$quote(rm settings.o$$escape_expand(\n\t))
#win32:CONFIG(release, debug|release): QMAKE_POST_LINK += $$quote(del release\settings.obj$$escape_expand(\n\t))
#else:win32:CONFIG(debug, debug|release): QMAKE_POST_LINK += $$quote(del debug\settings.obj$$escape_expand(\n\t))


include($$PWD/../quazip/quazip/quazip-headers.pri)
