#include "capturenode.h"

CaptureNode::CaptureNode()
{

}

CaptureNode::~CaptureNode()
{
    LOG_INFO()<<"Deleting capture node:"<<this->id()<<"|"<<this->name();
}

void CaptureNode::setNewFrame(QVariant newFrame)
{
    m_newFrame = newFrame;

    emit newFrameChanged(m_newFrame);

    m_newFrame=false;
}

void CaptureNode::setFrameCaptured(QVariant frameCaptured)
{
    m_frameCaptured = frameCaptured;
    emit frameCapturedChanged(m_frameCaptured);
}

void CaptureNode::setFrameSink(QVariant frameSink)
{

    m_frameSink = frameSink;
    emit frameSinkChanged(m_frameSink);
}

void CaptureNode::DeSerialize(QJsonObject &json)
{


    FlowNode::DeSerialize(json);
}

