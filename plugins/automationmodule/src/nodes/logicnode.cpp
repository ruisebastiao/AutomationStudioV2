#include "logicnode.h"

LogicNode::LogicNode()
{
    m_type=Type::LogicNode;


}


QQmlComponent *LogicNode::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/Cv/ProcessingLogicalNodeItem.qml"));
    return delegate.get();

}




void LogicNode::DeSerialize(QJsonObject &json)
{

    FlowNode::DeSerialize(json);


}
