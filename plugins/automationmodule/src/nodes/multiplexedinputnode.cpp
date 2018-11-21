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

    FlowNode::DeSerialize(json) ;
}

