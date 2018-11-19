#include "processingshapesnode.h"

ProcessingShapesNode::ProcessingShapesNode()
{
    m_processingType=ProcessingType::ProcessingShapesNode;
}

QQmlComponent *ProcessingShapesNode::delegate(QQmlEngine &engine) noexcept
{

    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/Cv/ProcessingShapeddNodeItem.qml"));
    return delegate.get();

}

void ProcessingShapesNode::DeSerialize(QJsonObject &json)
{
    ProcessingNode::DeSerialize(json);
    m_inputPort->setHidden(true);

}

void ProcessingShapesNode::setInput(QMat *input)
{

    ProcessingNode::setInput(input);

}

void ProcessingShapesNode::doProcess()
{

    ProcessingNode::doProcess();
}
