#include "processingenclosingnode.h"

using namespace cv;
using namespace std;

ProcessingEnclosingNode::ProcessingEnclosingNode()
{
    m_processingType=ProcessingType::ProcessingEnclosingNode;
}


QQmlComponent *ProcessingEnclosingNode::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/Cv/ProcessingEnclosingNodeItem.qml"));
    return delegate.get();

}

void ProcessingEnclosingNode::setInput(QMat *input)
{

}

void ProcessingEnclosingNode::doProcess()
{

    // TODO during real time processing this should be removed, only needed if in config mode
    m_originalFrame->cvMat()->copyTo(*m_output->cvMat());




    vector<RotatedRect> rotatedenclosingshapes;
    vector<Rect> rectenclosingshapes;


    for(int i = 0; i < m_contours.size(); i++)
    {
        vector<Point> contour=m_contours[i];
        vector<Point> approx_contour;

        //        approxPolyDP(contour,contour,contourlength*0.02,true);
        approxPolyDP(contour,approx_contour,3,true);
        //        Rect contour_rect=boundingRect(contour);

        switch (m_enclosingType) {
        case RotatedRectEnclosing:
        {
            RotatedRect minrect=minAreaRect(approx_contour);
            rotatedenclosingshapes.push_back(minrect);
            cv::Point2f vertices[4];
            minrect.points(vertices);
            for(int i = 0; i < 4; ++i){
                cv::line(*m_output->cvMat(), vertices[i], vertices[(i + 1) % 4], cv::Scalar(0, 0, 255), 2, CV_AA);
            }

            drawMarker(*m_output->cvMat(),minrect.center,cv::Scalar(0, 0, 255),MARKER_CROSS,20, 2,8);
        }

            break;
        case BoundingRectEnclosing:
            Rect minrect=boundingRect(approx_contour);
            cv::rectangle(*m_output->cvMat(), minrect, cv::Scalar(0, 0, 255), 2, CV_AA);
            drawMarker(*m_output->cvMat(),Point(minrect.x+minrect.width/2,minrect.y+minrect.height/2),cv::Scalar(0, 0, 255),MARKER_CROSS,20, 2,8);
            rectenclosingshapes.push_back(minrect);
            break;
        }

    }

    switch (m_enclosingType) {
    case RotatedRectEnclosing:
          m_enclosingShapes=QVariant::fromValue(rotatedenclosingshapes);
        break;
    case BoundingRectEnclosing:
        m_enclosingShapes=QVariant::fromValue(rectenclosingshapes);
        break;
    }

    emit enclosingShapesChanged(m_enclosingShapes);

    ProcessingNode::doProcess();




}

void ProcessingEnclosingNode::DeSerialize(QJsonObject &json)
{
    m_contoursPort= new FlowNodePort(this,qan::PortItem::Type::In,"contours");
    m_enclosingShapesPort= new FlowNodePort(this,qan::PortItem::Type::Out,"enclosingShapes");

    m_inPorts.append(m_contoursPort);
    m_outPorts.append(m_enclosingShapesPort);

    ProcessingNode::DeSerialize(json);
    m_inputPort->setHidden(true);
    m_outputPort->setHidden(true);

    if(m_contoursPort->portLabel()==""){
        m_contoursPort->setPortLabel("Contours");
    }

    if(m_enclosingShapesPort->portLabel()==""){
        m_enclosingShapesPort->setPortLabel("Enclosing Shapes");
    }
}
