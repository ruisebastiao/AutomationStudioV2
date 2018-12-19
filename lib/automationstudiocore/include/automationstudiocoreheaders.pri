INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/automationstudiocore

HEADERS += \    
    $$PWD/automationstudiocore/user.h \
    $$PWD/automationstudiocore/jsonserializable.h \    
    $$PWD/automationstudiocore/serializedlistmodel.h \
    $$PWD/automationstudiocore/systemsettings.h \
    $$PWD/automationstudiocore/plugincontext.h \
    $$PWD/automationstudiocore/utilities.h \
    $$PWD/automationstudiocore/keymap.h \
    $$PWD/automationstudiocore/socketio.h \
    $$PWD/automationstudiocore/appupdater.h \
    $$PWD/automationstudiocore/userslistmodel.h \
    $$PWD/automationstudiocore/userslistmodel.h
    $$PWD/automationstudiocore/tcpclient.h


include($$PWD/../../socket.io-client-cpp/socket.io-client-cpp-headers.pri)

