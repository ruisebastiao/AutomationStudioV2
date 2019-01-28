#include "subprojectinfonode.h"

SubProjectInfoNode::SubProjectInfoNode()
{
    m_type=Type::SubProjectInfoNode;
}

QQmlComponent *SubProjectInfoNode::delegate(QQmlEngine &engine)  noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/SubProjectInfoNodeItem.qml"));
    return delegate.get();
}
