#include "processingmasknode.h"

using namespace cv;

ProcessingMaskNode::ProcessingMaskNode()
{
    m_processingType=ProcessingType::ProcessingMaskNode;
}

QQmlComponent *ProcessingMaskNode::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/Cv/ProcessingMaskNodeItem.qml"));
    return delegate.get();

}

void ProcessingMaskNode::DeSerialize(QJsonObject &json)
{

    ProcessingNode::DeSerialize(json);

    FlowNodePort* port=getPortFromKey("input");
    if(port){
        port->setHidden(false);
        port->setPortLabel("Reference Image");

    }

    switch (m_maskType) {
    case MaskCircleRadius:

        port=getPortFromKey("input1");
        if(port){
            port->setHidden(false);
            port->setPortLabel("Center Point");
        }
        port=getPortFromKey("input2");
        if(port){
            port->setHidden(false);
            port->setPortLabel("Radius");
        }

        port=getPortFromKey("input3");
        if(port){
            port->setHidden(false);
            port->setPortLabel("Inner Radius");
        }

        port=getPortFromKey("input4");
        if(port){
            port->setHidden(true);

        }


        break;
    }

}

void ProcessingMaskNode::setInput(QVariant input)
{
    ProcessingNode::setInput(input);
}

void ProcessingMaskNode::doProcess()
{

    if(disabled().value<bool>()){
        return;
    }

    QMat* in=m_input.value<QMat*>();
    QMat* out=m_output.value<QMat*>();


    if(!in || in->cvMat()->empty()){
        // TODO Send Error
        return;
    }

    in->cvMat()->copyTo(*out->cvMat());

    switch (m_maskType) {
    case MaskCircleRadius:

        cv::Point center(-1,-1);
        double radius=-1;
        double inner_radius=-1;

        if(m_input1.canConvert<std::vector<cv::Rect>>()) {
            std::vector<cv::Rect> rect_obj = m_input1.value<std::vector<cv::Rect>>();

            // TODO check empty vectors

            if(rect_obj.size()>0){
                // if vector take index 0 Rect

                cv::Rect input1_rect=rect_obj.at(0);
                center=cv::Point(input1_rect.x+(input1_rect.width/2),input1_rect.y+(input1_rect.height/2));
            }



        }
        else if(m_input1.canConvert<cv::Point>()) {



                center=m_input1.value<cv::Point>();



        }

        if(m_input2.canConvert<double>()) {
            radius = m_input2.value<double>();
        }
        else{
            std::vector<cv::Rect> rect_obj = m_input1.value<std::vector<cv::Rect>>();
            if(rect_obj.size()>0){
                // if vector take index 0 Rect

                cv::Rect input2_rect=rect_obj.at(0);
                radius=std::max(input2_rect.width,input2_rect.height)/2;
            }
        }


        if(m_input3.canConvert<double>()) {
            inner_radius= m_input3.value<double>();
        }


        Mat temp= Mat::zeros(in->cvMat()->size(), CV_8UC1);
//        Mat temp= Mat(in->cvMat()->size(),CV_8UC1,Scalar(255));

        if(inner_radius<=0){
//            circle(*out->cvMat(),center,radius,Scalar(255),-1);
            circle(temp,center,radius,Scalar(255),-1);

        }
        else{

            circle(temp,center,radius,Scalar(255),-1);

            circle(temp,center,inner_radius,Scalar(0),-1);

//            floodFill(temp, cv::Point(0,0), Scalar(255));



//            // Invert floodfilled image
//            Mat im_floodfill_inv;
//            bitwise_not(temp, im_floodfill_inv);

//            // Combine the two images to get the foreground.
//            temp= (temp| im_floodfill_inv);

//            bitwise_not(*out->cvMat(),temp);



            //            circle(*out->cvMat(),center,radius-inner_radius,Scalar(255),inner_radius);
            //            circle(temp,center,radius-inner_radius,Scalar(255),inner_radius);

        }

        QMat* mask=m_maskOutput.value<QMat*>();
        temp.copyTo(*mask->cvMat());

        *out->cvMat()=*out->cvMat()|temp;

        emit maskOutputChanged(m_maskOutput);
        break;

    }
    ProcessingNode::doProcess();
}

void ProcessingMaskNode::Serialize(QJsonObject &json)
{
    ProcessingNode::Serialize(json);
}
