#include "cannyedgesnode.h"

CannyEdgesNode::CannyEdgesNode()
{

    m_type=Type::CannyEdgesNode;

}

QQmlComponent *CannyEdgesNode::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   qan_FlowNode_delegate;
    if ( !qan_FlowNode_delegate )
        qan_FlowNode_delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/Cv/CannyEdgesNodeItem.qml"));
    return qan_FlowNode_delegate.get();
}


void CannyEdgesNode::setInput(QMat *input)
{
    ProcessingNode::setInput(input);
    process();
}

void CannyEdgesNode::doProcess()
{
    if(!m_input){
        return;
    }

    if(m_showOriginal){

        m_input->cvMat()->copyTo(*output()->cvMat());

    }
    else{
        cv::Canny(*m_input->cvMat(), *m_output->cvMat(),this->thresholdlow(), this->thresholdhigh(),3,false );

    }


    emit outputChanged(m_output);



    ProcessingNode::doProcess();

}
