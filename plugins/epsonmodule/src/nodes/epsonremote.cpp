#include "epsonremote.h"

EpsonRemote::EpsonRemote()
{

}


QQmlComponent *EpsonRemote::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/EpsonNodeItem.qml"));
    return delegate.get();

}

