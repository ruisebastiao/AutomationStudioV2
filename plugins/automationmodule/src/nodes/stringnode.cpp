#include "stringnode.h"

StringNode::StringNode()
{

    m_type=Type::StringNode;
}


QQmlComponent*  StringNode::delegate(QQmlEngine& engine) noexcept
{
    static std::unique_ptr<QQmlComponent>   delegate;
    if ( !delegate )
        delegate = std::make_unique<QQmlComponent>(&engine, "qrc:///Nodes/StringNodeItem.qml");
    return delegate.get();
}

void StringNode::Serialize(QJsonObject &json)
{
    FlowNode::Serialize(json);
}

void StringNode::DeSerialize(QJsonObject &json)
{
    m_stringValuePort=new FlowNodePort(this,qan::PortItem::Type::Out,"stringValue");

    m_outPorts.append(m_stringValuePort);


    FlowNode::DeSerialize(json);
}

