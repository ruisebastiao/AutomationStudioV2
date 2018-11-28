#include "processinglogicalnode.h"

ProcessingLogicalNode::ProcessingLogicalNode()
{
    m_processingType=ProcessingType::ProcessingLogicalNode;


}


QQmlComponent *ProcessingLogicalNode::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/Cv/ProcessingLogicalNodeItem.qml"));
    return delegate.get();

}


void ProcessingLogicalNode::setInput(QVariant input)
{

}

void ProcessingLogicalNode::doProcess()
{

    if(configsLoaded() ){
        setLogicalOutput(m_logicalInput1==true && m_logicalInput2==true);
    }

    //ProcessingNode::doProcess();
}

void ProcessingLogicalNode::DeSerialize(QJsonObject &json)
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
    port=getPortFromKey("processingDone");
    if(port){
        port->setHidden(true);
    }



}
