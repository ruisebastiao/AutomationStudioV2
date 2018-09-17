#include "bsvalidationvisualnode.h"

BSValidationVisualNode::BSValidationVisualNode()
{
    m_type=Type::BSValidationVisualNode;
}

QQmlComponent*  BSValidationVisualNode::delegate(QQmlEngine& engine) noexcept
{
    static std::unique_ptr<QQmlComponent>   delegate;
    if ( !delegate )
        delegate = std::make_unique<QQmlComponent>(&engine, "qrc:///Nodes/BSValidationVisualNodeItem.qml");
    return delegate.get();
}



void BSValidationVisualNode::DeSerialize(QJsonObject &json)
{

    m_serialnumberPort=new FlowNodePort(this,qan::PortItem::Type::In,"serialnumber");
    m_BSOKPort=new FlowNodePort(this,qan::PortItem::Type::In,"BSOK");
    m_BSNOKPort=new FlowNodePort(this,qan::PortItem::Type::In,"BSNOK");
    m_leftsPort=new FlowNodePort(this,qan::PortItem::Type::In,"lefts");;

    m_WaitResultsPort=new FlowNodePort(this,qan::PortItem::Type::In,"WaitResults");

    VisualNode::DeSerialize(json);
}

void BSValidationVisualNode::Serialize(QJsonObject &json)
{
    VisualNode::Serialize(json);

}
