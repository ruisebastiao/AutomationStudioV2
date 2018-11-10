#include "processingbasenode.h"

ProcessingBaseNode::ProcessingBaseNode()
{
    m_type=Type::ProcessingBaseNode;
}

QQmlComponent *ProcessingBaseNode::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   qan_FlowNode_delegate;
    if ( !qan_FlowNode_delegate )
        qan_FlowNode_delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/Cv/ProcessingBaseNodeItem.qml"));
    return qan_FlowNode_delegate.get();

}

void ProcessingBaseNode::setInput(QMat *input)
{
    ProcessingNode::setInput(input);
    process();
}

void ProcessingBaseNode::doProcess()
{
    if(!m_input){
        return;
    }

    (*m_input->cvMat()).copyTo(*m_output->cvMat());


    emit outputChanged(m_output);
    ProcessingNode::doProcess();

}
