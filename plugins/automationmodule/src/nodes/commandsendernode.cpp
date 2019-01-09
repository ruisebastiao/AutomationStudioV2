#include "commandsendernode.h"

void CommandSenderNode::doSendCommand()
{
    setSend(true);
}

void CommandSenderNode::setBindedIONode(IONode *node)
{
    if(node==m_bindedIONode){
        return;
    }

    m_bindedIONode=node;

    if(!node){
        return;
    }

    //    if(node->id()!=selectedBindedNodeID()){
    setSelectedBindedNodeID(node->id());

    if(configsLoaded()==false){
        return;
    }
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

