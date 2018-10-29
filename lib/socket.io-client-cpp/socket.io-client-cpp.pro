QT       -= gui

TARGET = sioclient
TEMPLATE = lib

DEFINES += SIOCLIENT_LIBRARY


include($$PROJECT_PATH/shared/crashhandler/crash_handler.pri)

include(../../lib.pri)
include(lib/websocketpp/websocketpp.pri)
include(lib/rapidjson/rapidjson.pri)

include($$PWD/../../external/boost/boost.pri)



INCLUDEPATH += $$PWD/src

HEADERS += \
    src/sio_client.h \
    src/sio_message.h \
    src/sio_socket.h \
    src/internal/sio_client_impl.h \
    src/internal/sio_packet.h \
    src/sio_socket_global.h

SOURCES += \
    src/sio_client.cpp \
    src/sio_socket.cpp \
    src/internal/sio_client_impl.cpp \
    src/internal/sio_packet.cpp

