#include "commandparsernode.h"

CommandParserNode::CommandParserNode()
{
    m_type=Type::CommandParserNode;
}

void CommandParserNode::setBindedIONode(IONode* node)
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

    disconnect(node,&IONode::commandReceivedChanged,this,&CommandParserNode::setCommandReceived);
    connect(node,&IONode::commandReceivedChanged,this,&CommandParserNode::setCommandReceived);

    if(configsLoaded()==false){
        return;
    }
}


QQmlComponent *CommandParserNode::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/CommandParserNodeItem.qml"));
    return delegate.get();

}

void CommandParserNode::DeSerialize(QJsonObject &json)
{
    FlowNode::DeSerialize(json);

}

