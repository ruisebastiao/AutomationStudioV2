#include "numericnode.h"

NumericNode::NumericNode()
{
    m_type=Type::NumericNode;

}

QQmlComponent *NumericNode::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/NumericNodeItem.qml"));
    return delegate.get();
}


void NumericNode::DeSerialize(QJsonObject &json)
{


    FlowNode::DeSerialize(json);

    FlowNodePort* port=getPortFromKey("value");
    if(port){
        port->setPortLabel("Value");
    }



}

void NumericNode::Serialize(QJsonObject &json)
{
    FlowNode::Serialize(json);
}

