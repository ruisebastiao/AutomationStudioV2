#include "processingendnode.h"

ProcessingEndNode::ProcessingEndNode()
{
    m_type=Type::ProcessingEndNode;
}



QQmlComponent *ProcessingEndNode::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   qan_FlowNode_delegate;
    if ( !qan_FlowNode_delegate )
        qan_FlowNode_delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/Cv/ProcessingEndNodeItem.qml"));
    return qan_FlowNode_delegate.get();

}

void ProcessingEndNode::setInput(QMat *input)
{
    ProcessingNode::setInput(input);
    process();
}

void ProcessingEndNode::doProcess()
{
    if(!m_input){
        return;
    }

    (*m_input->cvMat()).copyTo(*m_output->cvMat());


    emit outputChanged(m_output);
    ProcessingNode::doProcess();

    emit processingCompleted(this);


}
