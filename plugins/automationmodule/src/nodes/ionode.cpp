#include "ionode.h"

IONode::IONode()
{

}

void IONode::setCommandReceived(QVariant commandReceived)
{


    m_commandReceived = commandReceived;
    emit commandReceivedChanged(m_commandReceived);
}

void IONode::Serialize(QJsonObject &json)
{
    FlowNode::Serialize(json);
}

void IONode::DeSerialize(QJsonObject &json)
{
    FlowNode::DeSerialize(json);
}

void IONode::setProjectLoaded(bool projectLoaded)
{
    if(autoConnect() && projectLoaded){
        doConnect();
    }
}
