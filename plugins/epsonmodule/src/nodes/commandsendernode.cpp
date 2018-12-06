#include "commandsendernode.h"

void CommandSenderNode::doSendCommand()
{
    setSend(true);
}

CommandSenderNode::CommandSenderNode()
{
    m_type=Type::CommandSenderNode;
}


QQmlComponent *CommandSenderNode::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/CommandSenderNodeItem.qml"));
    return delegate.get();

}

