#include "capturenode.h"

CaptureNode::CaptureNode()
{

}

void CaptureNode::setNewFrame(bool newFrame)
{
    m_newFrame = newFrame;

    emit newFrameChanged(m_newFrame);

    m_newFrame=false;
}

void CaptureNode::setFrameCaptured(bool frameCaptured)
{
    m_frameCaptured = frameCaptured;
    emit frameCapturedChanged(m_frameCaptured);
}

void CaptureNode::setFrameSink(QMat *frameSink)
{

    m_frameSink = frameSink;
    emit frameSinkChanged(m_frameSink);
}

void CaptureNode::DeSerialize(QJsonObject &json)
{
    m_newFramePort= new FlowNodePort(this,qan::PortItem::Type::In,"newFrame");
    m_frameSinkPort=new FlowNodePort(this,qan::PortItem::Type::Out,"frameSink");
    m_frameCapturedPort=new FlowNodePort(this,qan::PortItem::Type::Out,"frameCaptured");

    FlowNode::DeSerialize(json);
}
