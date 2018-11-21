#include "processingendnode.h"

ProcessingEndNode::ProcessingEndNode()
{
    m_processingType=ProcessingType::ProcessingEndNode;

// TODO this shold appear should be dynamic created impossible to remove???
    ProcessingNode::processingTypeTable[m_processingType]="End Node";
}


QQmlComponent *ProcessingEndNode::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/Cv/ProcessingEndNodeItem.qml"));
    return delegate.get();

}

void ProcessingEndNode::setInput(QMat *input)
{
    ProcessingNode::setInput(input);
}

void ProcessingEndNode::doProcess()
{
    if(m_input && m_input->cvMat()->empty()==false){

        m_input->cvMat()->copyTo(*m_output->cvMat());
    }
    ProcessingNode::doProcess();
    emit processingCompleted(this);
}

void ProcessingEndNode::DeSerialize(QJsonObject &json)
{
    ProcessingNode::DeSerialize(json);

    FlowNodePort* port=getPortFromKey("input");
    if(port){
        port->setHidden(true);
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
