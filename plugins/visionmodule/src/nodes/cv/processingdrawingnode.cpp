#include "processingdrawingnode.h"

ProcessingDrawingNode::ProcessingDrawingNode()
{
    m_processingType=ProcessingType::ProcessingDrawingNode;
}


QQmlComponent *ProcessingDrawingNode::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/Cv/ProcessingDrawingNodeItem.qml"));
    return delegate.get();

}


void ProcessingDrawingNode::setInput(QVariant input)
{
    ProcessingNode::setInput(input);
    doProcess();
}

void ProcessingDrawingNode::doProcess()
{

    QMat* in=m_input.value<QMat*>();
    QMat* out=m_output.value<QMat*>();

//    in->cvMat()->copyTo(*out->cvMat());
    //    m_output=m_input;

    cvtColor(*in->cvMat(),*out->cvMat(),CV_GRAY2BGR);


    ProcessingNode::doProcess();

}

void ProcessingDrawingNode::DeSerialize(QJsonObject &json)
{

    ProcessingNode::DeSerialize(json);

    FlowNodePort* port=getPortFromKey("maskInput");
    if(port){
        port->setHidden(true);
    }
    port=getPortFromKey("drawSource");
    if(port){
        port->setHidden(true);
    }
    port=getPortFromKey("process");
    if(port){
        port->setHidden(true);
    }
    port=getPortFromKey("processingDone");
    if(port){
        port->setHidden(true);
    }
//    port=getPortFromKey("drawSource");
//    if(port){
//        port->setHidden(true);
//    }

}
