#include "arraynode.h"


ArrayNode::ArrayNode()
{
    m_type=Type::ArrayNode;
}


QQmlComponent *ArrayNode::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/ArrayNodeItem.qml"));
    return delegate.get();

}


