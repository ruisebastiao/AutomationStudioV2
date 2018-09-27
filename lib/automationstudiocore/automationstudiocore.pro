TEMPLATE = lib
TARGET   = automationstudiocore
QT      += core qml quick
CONFIG  += qt


include(../../lib.pri)


RPI{
    message(is raspberry)
    DEFINES += RPI
}


DEFINES += AUTOMATIONSTUDIO_CORE_LIB

include($$PWD/src/automationstudiocore.pri)

