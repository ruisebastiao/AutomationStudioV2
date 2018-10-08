#include "cannyedgesnode.h"

using namespace cv;
using namespace std;

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

    Mat temp;

    (*m_input->cvMat()).copyTo(temp);


    cv::GaussianBlur(temp, temp, cv::Size(7, 7), 0);
    cv::Canny(temp, temp,this->thresholdlow(), this->thresholdhigh(),5,true );

    //        m_cannyContours.clear();
    //        vector<Vec4i> hierarchy;
    //        findContours(*m_output->cvMat(), m_cannyContours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE, Point(0,0) );


    temp.copyTo(*m_output->cvMat());

    emit outputChanged(m_output);



    ProcessingNode::doProcess();

}

void CannyEdgesNode::DeSerialize(QJsonObject &json)
{


    ProcessingNode::DeSerialize(json);
}
