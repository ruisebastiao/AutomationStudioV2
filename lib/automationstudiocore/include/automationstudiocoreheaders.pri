INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/automationstudiocore

INCLUDEPATH += $$PWD/../3rdparty/minizip/src/


HEADERS += \    
    $$PWD/automationstudiocore/user.h \
    $$PWD/automationstudiocore/jsonserializable.h \
    $$PWD/automationstudiocore/project.h \
    $$PWD/automationstudiocore/systemsettings.h \
    $$PWD/automationstudiocore/plugincontext.h \
    $$PWD/automationstudiocore/utilities.h \
    $$PWD/automationstudiocore/settings.h \
    $$PWD/automationstudiocore/keymap.h \
    $$PWD/automationstudiocore/socketio.h \


include($$PWD/../../socket.io-client-cpp/socket.io-client-cpp-headers.pri)

