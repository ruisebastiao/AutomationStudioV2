#include "setresetnode.h"

SetResetNode::SetResetNode()
{
    m_type=Type::SetResetNode;
}


QQmlComponent *SetResetNode::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/SetResetNodeItem.qml"));
    return delegate.get();

}
