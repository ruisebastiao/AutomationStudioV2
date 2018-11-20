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



void ProcessingGeometricNode::setInput(QMat *input)
{

}

QLineF ProcessingGeometricNode::lineSegment(){

    QLineF result;

    cv::Point pt1,pt2;

    double angle,length;


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



        line(*m_output->cvMat(),pt1,pt2,cv::Scalar(255, 0, 0), 2, CV_AA);

        result=QLineF(QPointF(pt1.x,pt1.y),QPointF(pt2.x,pt2.y));

        break;
    }





    return result;

}

void ProcessingGeometricNode::doProcess()
{
    m_output1=QVariant();

    // TODO during real time processing this should be removed, only needed if in config mode
    m_originalFrame->cvMat()->copyTo(*m_output->cvMat());


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

    m_input1Port= new FlowNodePort(this,qan::PortItem::Type::In,"input1");
    m_input2Port= new FlowNodePort(this,qan::PortItem::Type::In,"input2");
    m_input3Port= new FlowNodePort(this,qan::PortItem::Type::In,"input3");

    m_output1Port= new FlowNodePort(this,qan::PortItem::Type::Out,"output1");


    m_inPorts.append(m_input1Port);
    m_inPorts.append(m_input2Port);
    m_inPorts.append(m_input3Port);

    m_outPorts.append(m_output1Port);


    ProcessingNode::DeSerialize(json);

    m_inputPort->setHidden(true);
    m_outputPort->setHidden(true);

    if(m_processPort->portLabel()==""){
        m_processPort->setPortLabel("process");
    }


    switch (m_geometricType) {
    case Geometric2PointLine:
        m_input1Port->setPortLabel("Start Point");
        m_input2Port->setHidden(false);
        m_input2Port->setPortLabel("End Point");

        m_input3Port->setHidden(true);
        m_output1Port->setPortLabel("Line Segment");

        break;
    case GeometricPointAngleLengthLine:
        m_input1Port->setPortLabel("Center Point");
        m_input2Port->setPortLabel("Angle");
        m_input3Port->setHidden(false);
        m_input3Port->setPortLabel("Length");
        m_output1Port->setPortLabel("Line Segment");

        break;
    case Geometric3PointCircle:
        break;
    }

}
