#include "visualnode.h"

VisualNode::VisualNode()
{

}

void VisualNode::DeSerialize(QJsonObject &json)
{
    FlowNode::DeSerialize(json);
}

void VisualNode::Serialize(QJsonObject &json)
{
    FlowNode::Serialize(json);
}
