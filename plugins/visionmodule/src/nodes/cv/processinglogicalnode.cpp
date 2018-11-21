#include "processinglogicalnode.h"

ProcessingLogicalNode::ProcessingLogicalNode()
{
    m_processingType=ProcessingType::ProcessingLogicalNode;
    ProcessingNode::processingTypeTable[m_processingType]="Logical Operations";
}


QQmlComponent *ProcessingLogicalNode::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/Cv/ProcessingLogicalNodeItem.qml"));
    return delegate.get();

}


void ProcessingLogicalNode::setInput(QMat *input)
{

}

void ProcessingLogicalNode::doProcess()
{

    if(configsLoaded() && connectionsLoaded()){
        setLogicalOutput(m_logicalInput1==true && m_logicalInput2==true);
    }

    //ProcessingNode::doProcess();
}

void ProcessingLogicalNode::DeSerialize(QJsonObject &json)
{

    m_logicalInput1Port= new FlowNodePort(this,qan::PortItem::Type::In,"logicalInput1");
    m_logicalInput2Port= new FlowNodePort(this,qan::PortItem::Type::In,"logicalInput2");

    m_inPorts.append(m_logicalInput1Port);
    m_inPorts.append(m_logicalInput2Port);

    m_logicalOutputPort= new FlowNodePort(this,qan::PortItem::Type::Out,"logicalOutput");

    m_outPorts.append(m_logicalOutputPort);


    ProcessingNode::DeSerialize(json);

    m_inputPort->setHidden(true);
    m_processPort->setHidden(true);
    m_processingDonePort->setHidden(true);
    m_outputPort->setHidden(true);

    if(m_logicalInput1Port->portLabel()==""){
        m_logicalInput1Port->setPortLabel("Logical Input 1");
    }
    if(m_logicalInput2Port->portLabel()==""){
        m_logicalInput2Port->setPortLabel("Logical Input 2");
    }

    if(m_logicalOutputPort->portLabel()==""){
        m_logicalOutputPort->setPortLabel("Logical Output");
    }



}
