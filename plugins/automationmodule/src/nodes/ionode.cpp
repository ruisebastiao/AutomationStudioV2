#include "ionode.h"

IONode::IONode()
{

}

void IONode::Serialize(QJsonObject &json)
{
    FlowNode::Serialize(json);
}

void IONode::DeSerialize(QJsonObject &json)
{
 FlowNode::DeSerialize(json);
}
