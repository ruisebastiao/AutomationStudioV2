#include "processingnumericnode.h"

ProcessingNumericNode::ProcessingNumericNode()
{
    m_processingType=ProcessingType::ProcessingNumericNode;

}

QQmlComponent *ProcessingNumericNode::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/Cv/ProcessingNumericNodeItem.qml"));
    return delegate.get();
}

void ProcessingNumericNode::setInput(QMat *input)
{

}

void ProcessingNumericNode::doProcess()
{

    ProcessingNode::doProcess();
}

void ProcessingNumericNode::DeSerialize(QJsonObject &json)
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

    port=getPortFromKey("process");
    if(port){
        port->setHidden(true);
    }


    port=getPortFromKey("value");
    if(port){
        port->setPortLabel("Value");
    }



}

void ProcessingNumericNode::Serialize(QJsonObject &json)
{
 ProcessingNode::Serialize(json);
}

