#include "epsonnode.h"

EpsonNode::EpsonNode()
{
    m_type=Type::EpsonNode;
    m_tcpClient=new TCPClient(this);

}


QQmlComponent *EpsonNode::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/EpsonNodeItem.qml"));
    return delegate.get();

}

void EpsonNode::toogleConnection()
{
    if(m_tcpClient->state()==QAbstractSocket::ConnectedState){
        m_tcpClient->disconnect();
    }
    else{
        m_tcpClient->connect();
    }
}

void EpsonNode::sendCommand(QString command)
{
    if(m_tcpClient->state()==QAbstractSocket::ConnectedState){
        m_tcpClient->write(command);
    }
}

void EpsonNode::DeSerialize(QJsonObject &json)
{
    FlowNode::DeSerialize(json);
    setEpsonNode(QVariant::fromValue(this));
}

