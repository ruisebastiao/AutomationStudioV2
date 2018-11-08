#include "multiplexedinputnode.h"

MultiplexedInputNode::MultiplexedInputNode()
{
    m_type=FlowNode::Type::MultiplexedInputNode;

}




QQmlComponent *MultiplexedInputNode::delegate(QQmlEngine &engine) noexcept
{


    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/MultiplexedInputNodeItem.qml"));
    return delegate.get();

}

void MultiplexedInputNode::Serialize(QJsonObject &json)
{
    FlowNode::Serialize(json) ;
}

void MultiplexedInputNode::DeSerialize(QJsonObject &json)
{
    /// in
    ///
    m_in1Port= new FlowNodePort(this,qan::PortItem::Type::In,"in1");
    m_inPorts.append(m_in1Port);

    m_in2Port= new FlowNodePort(this,qan::PortItem::Type::In,"in2");
    m_inPorts.append(m_in2Port);


    /// Out

    m_outPort=new FlowNodePort(this,qan::PortItem::Type::Out,"out");
    m_outPorts.append(m_outPort);


    FlowNode::DeSerialize(json) ;
}

