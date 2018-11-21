#include "stringnode.h"

StringNode::StringNode()
{

    m_type=Type::StringNode;

}


QQmlComponent*  StringNode::delegate(QQmlEngine& engine) noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/StringNodeItem.qml"));
    return delegate.get();
}

void StringNode::Serialize(QJsonObject &json)
{
    FlowNode::Serialize(json);
}

void StringNode::DeSerialize(QJsonObject &json)
{



    FlowNode::DeSerialize(json);
}


