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

void ProcessingEnclosingNode::setInput(QVariant input)
{

}

void ProcessingEnclosingNode::doProcess()
{

    if(disabled().value<bool>()){
        return;
    }

    std::vector<std::vector<cv::Point>> _contours=m_contours.value<std::vector<std::vector<cv::Point>>>();
    QMat* output=m_output.value<QMat*>();
    QMat* drawsource=m_drawSource.value<QMat*>();

    //    if(!in || in->cvMat()->empty() || !out){
    //        // TODO Send Error
    //        return;
    //    }

    // TODO during real time processing this should be removed, only needed if in config mode
    //   m_originalFrame->cvMat()->copyTo(*out->cvMat());




    std::vector<cv::RotatedRect> rotatedenclosingshapes;
    vector<Rect> rectenclosingshapes;


    for(int i = 0; i < _contours.size(); i++)
    {
        vector<Point> contour=_contours[i];
        vector<Point> approx_contour;

        //        approxPolyDP(contour,contour,contourlength*0.02,true);
        approxPolyDP(contour,approx_contour,3,true);
        //        Rect contour_rect=boundingRect(contour);

        switch (m_enclosingType) {
        case RotatedRectEnclosing:
        {


            RotatedRect minrect=minAreaRect(approx_contour);

            double ratio=minrect.size.width/minrect.size.height;

            if((ratio<minRatio() || ratio>1/minRatio() ) ||  (ratio>maxRatio()   && ratio<1/maxRatio())){
                continue;
            }


            rotatedenclosingshapes.push_back(minrect);
            cv::Point2f vertices[4];
            minrect.points(vertices);

            QMat* drawsource=m_drawSource.value<QMat*>();

            if(drawsource && drawsource->cvMat()->empty()==false){


                for(int i = 0; i < 4; ++i){

                    cv::line(*drawsource->cvMat(), vertices[i], vertices[(i + 1) % 4], cv::Scalar(0, 0, 255), 2, CV_AA);
                     if(output){
                         cv::line(*output->cvMat(), vertices[i], vertices[(i + 1) % 4], cv::Scalar(0, 0, 255), 2, CV_AA);
                     }
                }

                drawMarker(*drawsource->cvMat(),minrect.center,cv::Scalar(0, 0, 255),MARKER_CROSS,20, 2,8);
                if(output){
                    drawMarker(*output->cvMat(),minrect.center,cv::Scalar(0, 0, 255),MARKER_CROSS,20, 2,8);
                }
            }

            break;
        }
        case BoundingRectEnclosing:
        {
            cv::Rect minrect=boundingRect(approx_contour);



            if(drawsource && drawsource->cvMat()->empty()==false){


                rectangle(*drawsource->cvMat(), minrect, cv::Scalar(0, 0, 255), 2, CV_AA);
                drawMarker(*drawsource->cvMat(),Point(minrect.x+minrect.width/2,minrect.y+minrect.height/2),cv::Scalar(0, 0, 255),MARKER_CROSS,20, 2,8);


                if(output){
                    rectangle(*output->cvMat(), minrect, cv::Scalar(0, 0, 255), 2, CV_AA);
                    drawMarker(*output->cvMat(),Point(minrect.x+minrect.width/2,minrect.y+minrect.height/2),cv::Scalar(0, 0, 255),MARKER_CROSS,20, 2,8);
                }



                rectenclosingshapes.push_back(minrect);
            }
            break;

        }
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

    ;

    emit enclosingShapesChanged(m_enclosingShapes);

    ProcessingNode::doProcess();




}

void ProcessingEnclosingNode::DeSerialize(QJsonObject &json)
{


    ProcessingNode::DeSerialize(json);
    FlowNodePort* port=getPortFromKey("input");
    if(port){
        port->setHidden(true);
    }
    port=getPortFromKey("output");
    if(port){
        port->setHidden(true);
    }

}
