#include "propertiesnode.h"

PropertiesNode::PropertiesNode()
{
    m_type=Type::PropertiesNode;
}

QQmlComponent *PropertiesNode::delegate(QQmlEngine &engine)  noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/PropertiesNodeItem.qml"));
    return delegate.get();
}
