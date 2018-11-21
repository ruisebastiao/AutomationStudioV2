#include "processingmasknode.h"

ProcessingMaskNode::ProcessingMaskNode()
{
    m_processingType=ProcessingType::ProcessingMaskNode;
    ProcessingNode::processingTypeTable[m_processingType]="Masking";
}

QQmlComponent *ProcessingMaskNode::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/Cv/ProcessingMaskNodeItem.qml"));
    return delegate.get();

}

void ProcessingMaskNode::DeSerialize(QJsonObject &json)
{

    ProcessingNode::DeSerialize(json);
}

void ProcessingMaskNode::setInput(QMat *input)
{
    ProcessingNode::setInput(input);
}

void ProcessingMaskNode::doProcess()
{

    ProcessingNode::doProcess();
}
