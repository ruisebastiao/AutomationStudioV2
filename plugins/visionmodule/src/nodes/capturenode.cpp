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


    FlowNode::DeSerialize(json);
}

