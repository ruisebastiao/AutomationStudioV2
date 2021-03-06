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

/**
 * Rotate an image (source: http://opencv-code.com/quick-tips/how-to-rotate-image-in-opencv/)
 */
void rotate(cv::Mat& src, double angle, cv::Mat& dst)
{
    int len = std::max(src.cols, src.rows);
    cv::Point2f pt(len/2., len/2.);
    cv::Mat r = cv::getRotationMatrix2D(pt, angle, 1.0);

    cv::warpAffine(src, dst, r, cv::Size(len, len));
}


QList<cv::Point> process_inputs(QVariant input){

    QList<cv::Point> list;
    if(input.canConvert<cv::Rect>()) {

        cv::Rect input_rect= input.value<cv::Rect>();
        list.append(cv::Point(input_rect.x+(input_rect.width/2),input_rect.y+(input_rect.height/2)));


    }
    else if(input.canConvert<cv::RotatedRect>()) {
        cv::RotatedRect input_rotacted_rect= input.value<cv::RotatedRect>();

        list.append(input_rotacted_rect.center);


    }
    else if(input.canConvert<QVariantList>()) {
        QVariantList rect_list= input.value<QVariantList>();

        for (int var = 0; var < rect_list.length(); ++var) {


            QVariant variant_rect=rect_list.at(var);

            if(variant_rect.canConvert<cv::Rect>()){

                cv::Rect rect=variant_rect.value<cv::Rect>();
                list.append(cv::Point2f(rect.x+(rect.width/2),rect.y+(rect.height/2)));


            }
            else if(variant_rect.canConvert<cv::RotatedRect>()){

                cv::RotatedRect rect=variant_rect.value<cv::RotatedRect>();
                list.append(rect.center);


            }

        }

    }
    else if(input.canConvert<QLineF>()) {
        QLineF segment=input.value<QLineF>();
        list.append(cv::Point2f(segment.center().x(),segment.center().y()));
    }

    return list;

}

void ProcessingGeometricNode::processLineSegments(){


    QVariantList result_lines;


    QVariantList  result_angles;

    QMat* in=m_input.value<QMat*>();

    QMat* output=m_output.value<QMat*>();
    QMat* drawsource=m_drawSource.value<QMat*>();


    QList<cv::Point> start_points,end_points;


    if(m_input1.isValid() && m_input2.isValid()){

        switch (m_geometricType) {
        case GeometricLinePointLine:
        {
            start_points.append(process_inputs(m_input1));
            end_points.append(process_inputs(m_input2));
            break;
        }
        case GeometricPointAngleLengthLine:


            break;
        case Geometric2PointLine:
        {


            start_points.append(process_inputs(m_input1));
            end_points.append(process_inputs(m_input2));

            break;


        }


        }
    }


    for (int start_point_inc = 0; start_point_inc < start_points.length(); ++start_point_inc) {
        cv::Point start_pt=start_points.at(start_point_inc);
        for (int end_point_inc = 0; end_point_inc < end_points.length(); ++end_point_inc) {

            cv::Point end_pt=end_points.at(end_point_inc);

            if((start_pt.x!=0 && start_pt.y!=0) && (end_pt.x!=0 && end_pt.y!=0)){

                QLineF result_line=QLineF(QPointF(start_pt.x,start_pt.y),QPointF(end_pt.x,end_pt.y));

                if(result_line.length()>0){

                    if(result_line.angle()>=minAngle() && result_line.angle()<=maxAngle()){
                        result_lines.append(result_line);
                        result_angles.append(result_line.angle());
                    }



                    QMat* drawsource=m_drawSource.value<QMat*>();

                    if(drawsource && drawsource->cvMat()->empty()==false){

                        // Create and rotate the text
                        //                        cv::Mat textImg = cv::Mat::zeros((*drawsource->cvMat()).rows, (*drawsource->cvMat()).cols, (*drawsource->cvMat()).type());


                        cv::Scalar linecolor;
                        if(result_line.angle()>=minAngle() && result_line.angle()<=maxAngle()){
                            linecolor=cv::Scalar(0, 255, 0);
                        }
                        else{
                            linecolor=cv::Scalar(0, 0, 255);
                        }
                        line(*drawsource->cvMat(),start_pt,end_pt,linecolor, 2, CV_AA);
                        putText(*drawsource->cvMat(),
                                qPrintable(QString::number(result_line.angle(), 'f', 2)),
                                cv::Point(result_line.center().x(),result_line.center().y()), // Coordinates
                                cv::FONT_HERSHEY_COMPLEX_SMALL, // Font
                                2.0, // Scale. 2.0 = 2x bigger
                               linecolor, // BGR Color
                                1, // Line Thickness (Optional)
                                CV_AA); // Anti-alias (Optional)

                        //                        rotate(textImg, result_line.angle(), textImg);
                        //                        *drawsource->cvMat()=*drawsource->cvMat()+textImg;
                        if(output){
                            line(*output->cvMat(),start_pt,end_pt,linecolor, 2, CV_AA);
                            //                            *output->cvMat()=*output->cvMat()+textImg;
                        }

                    }
                }
            }

        }

    }
    m_output1=QVariant::fromValue(result_lines);
    emit output1Changed(m_output1);
    //    m_output2=QVariant::fromValue(QString::number(result_line.angle(), 'f', 2));
    m_output2=QVariant::fromValue(result_angles);

    emit output2Changed(m_output2);

}
void ProcessingGeometricNode::doProcess()
{

    if(disabled().value<bool>()){
        return;
    }

    // TODO during real time processing this should be removed, only needed if in config mode
    //m_originalFrame->cvMat()->copyTo(*m_output.value<QMat*>()->cvMat());


    switch (m_geometricType) {
    case Geometric2PointLine:


        processLineSegments();

        break;
    case GeometricLinePointLine:

        processLineSegments();


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
