#include "processingcontoursnode.h"

using namespace cv;
using namespace std;

ProcessingContoursNode::ProcessingContoursNode()
{
    m_type=Type::ProcessingContoursNode;
}

QQmlComponent *ProcessingContoursNode::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   qan_FlowNode_delegate;
    if ( !qan_FlowNode_delegate )
        qan_FlowNode_delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/Cv/ProcessingContoursNodeItem.qml"));
    return qan_FlowNode_delegate.get();

}

double ProcessingContoursNode::contourPerimeter(std::vector<Point> contour)
{
    return arcLength(contour,true);
}

void ProcessingContoursNode::DeSerialize(QJsonObject &json)
{
    m_filteredContoursPort=new FlowNodePort(this,qan::PortItem::Type::Out,"filteredContours");

    m_outPorts.append(m_filteredContoursPort);


    ProcessingNode::DeSerialize(json);
}


void ProcessingContoursNode::doProcess()
{
    if(!m_input){
        return;
    }

    vector<vector<Point> > contours;


    if(m_input->cvMat()->empty()){
        return;
    }



    m_filteredContours.clear();

    Mat drawing = Mat::zeros( m_input->cvMat()->size(), CV_8UC3 );

    //CV_RETR_LIST
    findContours(*m_input->cvMat(),contours, RETR_LIST, CHAIN_APPROX_NONE);

    //   drawContours(drawing, contours, -1, cv::Scalar(0,255,0), 1);

    setTotalContours(contours.size());

    for(int i = 0; i < contours.size(); i++)
    {

        vector<Point> contour=contours[i];
        //        vector<Point> approx;

        //        approxPolyDP(countour,approx,arcLength(Mat(countour), true)*0.02,true);

        double contourlength=arcLength(contour,true);
        if(contourlength>minCountourLength() && contourlength<maxCountourLength()){
            m_filteredContours.push_back(contour);
        }

    }
    setTotalFilteredContours(m_filteredContours.size());

    drawContours(drawing, m_filteredContours, -1, cv::Scalar(0,255,0), 1);

//    if(drawInSource()){
//        if(m_processedFrame && m_processedFrame->cvMat()->empty()==false){
//            drawContours(*m_processedFrame->cvMat(), m_filteredContours, -1, cv::Scalar(0,255,0), 1);

//        }
//    }


    drawing.copyTo(*m_output->cvMat());

    emit filteredContoursChanged(m_filteredContours);

    emit outputChanged(m_output);


    ProcessingNode::doProcess();

}

void ProcessingContoursNode::setInput(QMat *input)
{
    ProcessingNode::setInput(input);
    process();
}
