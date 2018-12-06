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



    double angle,length;

    QMat* in=m_input.value<QMat*>();

    QMat* output=m_output.value<QMat*>();
    QMat* drawsource=m_drawSource.value<QMat*>();



    switch (m_geometricType) {
    case GeometricLinePointLine:
    {
        cv::Point2f startpt;
        cv::Point2f endpoint;

        if(strcmp(m_input1.typeName(),"cv::Point")==0) {
            startpt = m_input1.value<cv::Point>();
        }
        else if(strcmp(m_input1.typeName(),"std::vector<cv::Rect>")==0) {
            std::vector<cv::Rect> rect_obj = m_input1.value<std::vector<cv::Rect>>();

            // TODO check empty vectors

            if(rect_obj.size()>0){


                // if vector take index 0 Rect

                cv::Rect input1_rect=rect_obj.at(0);
                startpt=cv::Point2f(input1_rect.x+(input1_rect.width/2),input1_rect.y+(input1_rect.height/2));
            }

        }

        if(strcmp(m_input2.typeName(),"QLineF")==0) {
            QLineF segment=m_input2.value<QLineF>();
            endpoint= cv::Point2f(segment.center().x(),segment.center().y());
        }

        result=QLineF(QPointF(endpoint.x,endpoint.y),QPointF(startpt.x,startpt.y));

        QMat* drawsource=m_drawSource.value<QMat*>();

        if(drawsource && drawsource->cvMat()->empty()==false){

            line(*drawsource->cvMat(),startpt,endpoint,cv::Scalar(255, 0, 0), 2, CV_AA);
            putText(*drawsource->cvMat(),
                    qPrintable(QString::number(result.angle(), 'f', 2)),
                    startpt, // Coordinates
                    cv::FONT_HERSHEY_COMPLEX_SMALL, // Font
                    2.0, // Scale. 2.0 = 2x bigger
                    cv::Scalar(255,0,0), // BGR Color
                    1, // Line Thickness (Optional)
                    CV_AA); // Anti-alias (Optional)
            if(output){
                line(*output->cvMat(),startpt,endpoint,cv::Scalar(255, 0, 0), 2, CV_AA);
                putText(*output->cvMat(),
                        qPrintable(QString::number(result.angle(), 'f', 2)),
                        startpt, // Coordinates
                        cv::FONT_HERSHEY_COMPLEX_SMALL, // Font
                        2.0, // Scale. 2.0 = 2x bigger
                        cv::Scalar(255,0,0), // BGR Color
                        1, // Line Thickness (Optional)
                        CV_AA); // Anti-alias (Optional)
            }

        }





    }

        break;
    case GeometricPointAngleLengthLine:


        break;
    case Geometric2PointLine:
    {
        cv::Point pt1,pt2;
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

        result=QLineF(QPointF(pt1.x,pt1.y),QPointF(pt2.x,pt2.y));

        QMat* drawsource=m_drawSource.value<QMat*>();

        if(drawsource && drawsource->cvMat()->empty()==false){

            line(*drawsource->cvMat(),pt1,pt2,cv::Scalar(255, 0, 0), 2, CV_AA);
            putText(*drawsource->cvMat(),
                    qPrintable(QString::number(result.angle(), 'f', 2)),
                    pt1, // Coordinates
                    cv::FONT_HERSHEY_COMPLEX_SMALL, // Font
                    2.0, // Scale. 2.0 = 2x bigger
                    cv::Scalar(255,0,0), // BGR Color
                    1, // Line Thickness (Optional)
                    CV_AA); // Anti-alias (Optional)
            if(output){
                line(*output->cvMat(),pt1,pt2,cv::Scalar(255, 0, 0), 2, CV_AA);
                putText(*output->cvMat(),
                        qPrintable(QString::number(result.angle(), 'f', 2)),
                        pt1, // Coordinates
                        cv::FONT_HERSHEY_COMPLEX_SMALL, // Font
                        2.0, // Scale. 2.0 = 2x bigger
                        cv::Scalar(255,0,0), // BGR Color
                        1, // Line Thickness (Optional)
                        CV_AA); // Anti-alias (Optional)
            }

        }
    }

        //qDebug()<<"Result:"<<result.angle();
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
            QLineF result=lineSegment();
            m_output1=QVariant::fromValue(result);

            emit output1Changed(m_output1);

            m_output2=QVariant::fromValue(QString::number(result.angle(), 'f', 2));
            emit output2Changed(m_output2);

        }
        break;
    case GeometricLinePointLine:
        if(m_input1.isValid() && m_input2.isValid()){
            QLineF result=lineSegment();
            m_output1=QVariant::fromValue(result);

            emit output1Changed(m_output1);

            m_output2=QVariant::fromValue(QString::number(result.angle(), 'f', 2));
            emit output2Changed(m_output2);

        }
        break;
    case Geometric3PointCircle:
        break;
    }



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

}
