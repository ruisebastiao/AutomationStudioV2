#include "epsonnode.h"

EpsonNode::EpsonNode()
{

}


QQmlComponent *EpsonNode::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/Cv/EpsonNodeItem.qml"));
    return delegate.get();

}

