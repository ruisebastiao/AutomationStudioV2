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
    cv::Canny(temp, temp,this->thresholdlow(), this->thresholdhigh() );

    //        m_cannyContours.clear();
    //        vector<Vec4i> hierarchy;
    //        findContours(*m_output->cvMat(), m_cannyContours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE, Point(0,0) );

    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    findContours( temp, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE );
    Mat drawing = Mat::zeros( temp.size(), CV_8UC3 );

    std::vector<std::vector<cv::Point>> m_filteredContours;

    for(int i = 0; i < contours.size(); i++)
    {

        vector<Point> contour=contours[i];
        //        vector<Point> approx;

        //        approxPolyDP(countour,approx,arcLength(Mat(countour), true)*0.02,true);

        double contourlength=arcLength(contour,true);
        if(contourlength>500 && 10000){
            m_filteredContours.push_back(contour);
        }

    }

   drawContours(drawing, m_filteredContours, -1, cv::Scalar(0,255,0), 1);


    drawing.copyTo(*m_output->cvMat());

    emit outputChanged(m_output);



    ProcessingNode::doProcess();

}

void CannyEdgesNode::DeSerialize(QJsonObject &json)
{


    ProcessingNode::DeSerialize(json);
}
