#include "processingmasknode.h"

using namespace cv;

ProcessingMaskNode::ProcessingMaskNode()
{
    m_processingType=ProcessingType::ProcessingMaskNode;
    ProcessingNode::processingTypeTable[m_processingType]="Masking";
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

void ProcessingMaskNode::setInput(QMat *input)
{
    ProcessingNode::setInput(input);
}

void ProcessingMaskNode::doProcess()
{

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

        if(m_input2.canConvert<double>()) {
            radius = m_input2.value<double>();
        }


        if(m_input3.canConvert<double>()) {
            inner_radius= m_input3.value<double>();
        }


        Mat temp;



        break;
    }
    ProcessingNode::doProcess();
}
