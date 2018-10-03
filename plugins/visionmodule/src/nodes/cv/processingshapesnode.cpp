#include "processingshapesnode.h"

using namespace cv;
using namespace std;

ProcessingShapesNode::ProcessingShapesNode()
{
    m_type=Type::ProcessingShapesNode;
}

QQmlComponent *ProcessingShapesNode::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   qan_FlowNode_delegate;
    if ( !qan_FlowNode_delegate )
        qan_FlowNode_delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/Cv/ProcessingShapesNodeItem.qml"));
    return qan_FlowNode_delegate.get();
}


void ProcessingShapesNode::DeSerialize(QJsonObject &json)
{
    m_contoursPort= new FlowNodePort(this,qan::PortItem::Type::In,"contours");

    ProcessingNode::DeSerialize(json);
}

void ProcessingShapesNode::doProcess()
{


    std::vector<std::vector<cv::Point>> shapesContours;


    //  vector<vector<Point> > contours;
    //    vector<vector<Point> > filtered_contours;



//    if(!m_output){
//        setOutput(m_input);

//    }

    //    if(m_output && m_output->cvMat()->empty()==false){
    //        cvtColor(*m_processedFrame->cvMat(), *m_output->cvMat(), COLOR_GRAY2BGR);
    //    }




    //  Mat drawing = Mat::zeros( m_originalInput->cvMat()->size(), CV_8UC3 );

    for(int i = 0; i < m_contours.size(); i++)
    {
        vector<Point> contour=m_contours[i];
        vector<Point> approx;

        // Approximate contour with accuracy proportional
        // to the contour perimeter
        approxPolyDP(cv::Mat(contour), approx, cv::arcLength(cv::Mat(contour), true)*0.04, true);

        // non-convex objects
        if (!cv::isContourConvex(approx))
            continue;
        int approxSize=approx.size();
        if (approxSize== 3)
        {

            //   setLabel(dst, "TRI", contours[i]);    // Triangles
        }

        if(approxSize==4){

            shapesContours.push_back(approx);

        }


    }

    if(shapesContours.size()>0){

        if(m_output && m_output->cvMat()->empty()==false){
            drawContours(*m_output->cvMat(), shapesContours, -1, cv::Scalar(0,255,0), 1);

        }




    }

    emit outputChanged(m_output);


    ProcessingNode::doProcess();

}

void ProcessingShapesNode::setInput(QMat *input)
{
    ProcessingNode::setInput(input);

}
