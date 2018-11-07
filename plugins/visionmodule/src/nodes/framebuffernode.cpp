#include "framebuffernode.h"

FrameBufferNode::FrameBufferNode()
{
    m_type=FlowNode::Type::FrameBufferNode;
}


QQmlComponent *FrameBufferNode::delegate(QQmlEngine &engine)noexcept
{


    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/FrameBufferNodeItem.qml"));
    return delegate.get();

}

void FrameBufferNode::Serialize(QJsonObject &json)
{

    FlowNode::Serialize(json);
}

void FrameBufferNode::DeSerialize(QJsonObject &json)
{

    m_numBuffersPort= new FlowNodePort(this,qan::PortItem::Type::In,"numBuffers");
    m_inPorts.append(m_numBuffersPort);

    m_frameSinkPort=new FlowNodePort(this,qan::PortItem::Type::Out,"frameSink");
    m_outPorts.append(m_frameSinkPort);


    FlowNode::DeSerialize(json);
}
