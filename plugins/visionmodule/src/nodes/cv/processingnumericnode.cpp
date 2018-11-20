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

    m_valuePort= new FlowNodePort(this,qan::PortItem::Type::Out,"value");

    m_outPorts.append(m_valuePort);


    ProcessingNode::DeSerialize(json);

    m_inputPort->setHidden(true);
    m_outputPort->setHidden(true);
    m_processPort->setHidden(true);

    m_valuePort->setPortLabel("Value");

}
