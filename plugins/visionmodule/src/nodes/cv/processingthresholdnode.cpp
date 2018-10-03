#include "processingthresholdnode.h"

#include "opencv2/imgproc.hpp"

ProcessingThresholdNode::ProcessingThresholdNode()
{

    m_type=Type::ProcessingThresholdNode;
}

QQmlComponent *ProcessingThresholdNode::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   qan_FlowNode_delegate;
    if ( !qan_FlowNode_delegate )
        qan_FlowNode_delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/Cv/ProcessingThresholdNodeItem.qml"));
    return qan_FlowNode_delegate.get();
}


void ProcessingThresholdNode::doProcess()
{
    if(!m_input){
        return;
    }

    cv::threshold(*m_input->cvMat(), *m_output->cvMat(),m_value, 255,cv::THRESH_BINARY );


    emit outputChanged(m_output);



    ProcessingNode::doProcess();

}

void ProcessingThresholdNode::setInput(QMat *input)
{
    ProcessingNode::setInput(input);
    process();

}
