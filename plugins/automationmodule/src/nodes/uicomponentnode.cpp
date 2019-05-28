#include "uicomponentnode.h"

UIComponentNode::UIComponentNode()
{
 m_type=Type::UIComponentNode;
}

QQmlComponent *UIComponentNode::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/UIComponentNodeItem.qml"));
    return delegate.get();
}
