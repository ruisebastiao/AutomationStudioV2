TEMPLATE = lib
TARGET   = automationstudiocore
QT      += core qml quick concurrent
CONFIG  += qt

include(../../functions.pri)


include(../../lib.pri)

include($$PWD/3rdparty/minizip/minizip.pri)

RPI{
    message(is raspberry)
    DEFINES += RPI
}



DEFINES += AUTOMATIONSTUDIO_CORE_LIB

include($$PWD/src/automationstudiocore.pri)

linkLocalLib(sioclient)

include($$PWD/../../lib/CuteLogger/include/cuteloggerheaders.pri)
linkLocalLib(CuteLogger)



include($$PWD/../socket.io-client-cpp/socket.io-client-cpp-headers.pri)

QMAKE_POST_LINK += $$quote(rm settings.o$$escape_expand(\n\t))
