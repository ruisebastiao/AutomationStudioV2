#include "processinggeometricnode.h"


ProcessingGeometricNode::ProcessingGeometricNode()
{
    m_processingType=ProcessingType::ProcessingGeometricNode;

}


QQmlComponent *ProcessingGeometricNode::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/Cv/ProcessingGeometricNode.qml"));
    return delegate.get();

}



void ProcessingGeometricNode::setInput(QVariant input)
{

}

QLineF ProcessingGeometricNode::lineSegment(){

    QLineF result;

    cv::Point pt1,pt2;

    double angle,length;

    QMat* in=m_input.value<QMat*>();
//    QMat* out=m_output.value<QMat*>();

    switch (m_geometricType) {
    case GeometricPointAngleLengthLine:

        //        if(strcmp(m_input1.typeName(),"std::vector<cv::Rect>")==0) {
        //            std::vector<cv::Rect> rect_obj = m_input1.value<std::vector<cv::Rect>>();

        //            // TODO check empty vectors

        //            if(rect_obj.size()>0){


        //                // if vector take index 0 Rect

        //                cv::Rect input1_rect=rect_obj.at(0);
        //                pt1=cv::Point(input1_rect.x+(input1_rect.width/2),input1_rect.y+(input1_rect.height/2));
        //            }

        //        }
        //        else if(strcmp(m_input1.typeName(),"std::vector<cv::RotatedRect>")==0) {
        //            std::vector<cv::RotatedRect> rect_obj = m_input1.value<std::vector<cv::RotatedRect>>();

        //            // TODO process empty vectors

        //            if(rect_obj.size()>0){


        //                // if vector take index 0 Rect

        //                cv::RotatedRect input1_rect=rect_obj.at(0);
        //                pt1=input1_rect.center;
        //            }

        //        }


        //        if(strcmp(m_input2.typeName(),"double")==0) {
        //            double angle = m_input2.value<double>();


        //        }




        //        line(*m_output->cvMat(),pt1,pt2,cv::Scalar(255, 0, 0), 2, CV_AA);

        //        result=QLineF(QPointF(pt1.x,pt1.y),QPointF(pt2.x,pt2.y));


        break;
    case Geometric2PointLine:

        if(strcmp(m_input1.typeName(),"std::vector<cv::Rect>")==0) {
            std::vector<cv::Rect> rect_obj = m_input1.value<std::vector<cv::Rect>>();

            // TODO check empty vectors

            if(rect_obj.size()>0){


                // if vector take index 0 Rect

                cv::Rect input1_rect=rect_obj.at(0);
                pt1=cv::Point(input1_rect.x+(input1_rect.width/2),input1_rect.y+(input1_rect.height/2));
            }

        }
        else if(strcmp(m_input1.typeName(),"std::vector<cv::RotatedRect>")==0) {
            std::vector<cv::RotatedRect> rect_obj = m_input1.value<std::vector<cv::RotatedRect>>();

            // TODO process empty vectors

            if(rect_obj.size()>0){


                // if vector take index 0 Rect

                cv::RotatedRect input1_rect=rect_obj.at(0);
                pt1=input1_rect.center;
            }

        }


        if(strcmp(m_input2.typeName(),"std::vector<cv::Rect>")==0) {
            std::vector<cv::Rect> rect_obj = m_input2.value<std::vector<cv::Rect>>();

            // TODO process empty vectors

            if(rect_obj.size()>0){


                // if vector take index 0 Rect

                cv::Rect input2_rect=rect_obj.at(0);
                pt2=cv::Point(input2_rect.x+(input2_rect.width/2),input2_rect.y+(input2_rect.height/2));
            }

        }
        else if(strcmp(m_input2.typeName(),"std::vector<cv::RotatedRect>")==0) {
            std::vector<cv::RotatedRect> rect_obj = m_input2.value<std::vector<cv::RotatedRect>>();

            // TODO process empty vectors

            if(rect_obj.size()>1){


                // TODO add at index property value serializable

                cv::RotatedRect input2_rect=rect_obj.at(1);
                pt2=input2_rect.center;
            }

        }



        line(*m_drawSource->cvMat(),pt1,pt2,cv::Scalar(255, 0, 0), 2, CV_AA);

        result=QLineF(QPointF(pt1.x,pt1.y),QPointF(pt2.x,pt2.y));

        break;
    }





    return result;

}


void ProcessingGeometricNode::doProcess()
{


    // TODO during real time processing this should be removed, only needed if in config mode
    //m_originalFrame->cvMat()->copyTo(*m_output.value<QMat*>()->cvMat());


    switch (m_geometricType) {
    case Geometric2PointLine:

        if(m_input1.isValid() && m_input2.isValid()){
            m_output1=QVariant::fromValue(lineSegment());
        }
        break;
    case Geometric3PointCircle:
        break;
    }

    emit output1Changed(m_output1);

    ProcessingNode::doProcess();


}

void ProcessingGeometricNode::DeSerialize(QJsonObject &json)
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

    switch (m_geometricType) {
    case Geometric2PointLine:

        port=getPortFromKey("input1");
        if(port){
            port->setHidden(false);
            port->setPortLabel("Start Point");
        }
        port=getPortFromKey("input2");
        if(port){
            port->setHidden(false);
            port->setPortLabel("End Point");
        }

        port=getPortFromKey("input3");
        if(port){
            port->setHidden(true);

        }


        break;
    case GeometricPointAngleLengthLine:
        port=getPortFromKey("input1");
        if(port){
            port->setHidden(false);
            port->setPortLabel("Center Point");
        }
        port=getPortFromKey("input2");
        if(port){
            port->setHidden(false);
            port->setPortLabel("Angle");
        }

        port=getPortFromKey("input3");
        if(port){
            port->setHidden(false);
            port->setPortLabel("Length");
        }



        break;
    case Geometric3PointCircle:
        break;
    }

    port=getPortFromKey("output1");
    if(port){
        port->setHidden(false);
        port->setPortLabel("Line Segment");
    }
}
