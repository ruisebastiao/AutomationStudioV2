#include "processingendnode.h"

ProcessingEndNode::ProcessingEndNode()
{
    m_processingType=ProcessingType::ProcessingEndNode;

}


QQmlComponent *ProcessingEndNode::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/Cv/ProcessingEndNodeItem.qml"));
    return delegate.get();

}

void ProcessingEndNode::setInput(QVariant input)
{
    ProcessingNode::setInput(input);
}

void ProcessingEndNode::doProcess()
{
    if(disabled().value<bool>()){
        return;
    }

    m_output=m_input;
    ProcessingNode::doProcess();
    emit processingCompleted(this);
}

void ProcessingEndNode::DeSerialize(QJsonObject &json)
{
    ProcessingNode::DeSerialize(json);

    FlowNodePort* port=getPortFromKey("input");
    if(port){
        port->setHidden(false);
    }

    port=getPortFromKey("output");
    if(port){
        port->setHidden(true);
    }
    port=getPortFromKey("processing");
    if(port){
        port->setHidden(true);
    }

}
