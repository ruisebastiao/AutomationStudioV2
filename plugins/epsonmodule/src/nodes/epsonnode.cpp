#include "epsonnode.h"

EpsonNode::EpsonNode()
{
    m_type=Type::EpsonNode;
    m_tcpClient=new TCPClient();

    connect(m_tcpClient,&TCPClient::serverMessage,[this](const QString &message){
        this->setDataReceived(QVariant::fromValue(message));
    });

    connect(m_tcpClient,&TCPClient::stateChanged,[this](QAbstractSocket::SocketState state){
        switch (state) {
        case QAbstractSocket::SocketState::ConnectedState:
            this->setConnected(true);
            break;
        default:
            this->setConnected(false);
            break;
        }
    });


}

EpsonNode::~EpsonNode()
{
 m_tcpClient->disconnect();
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
    if(autoConnect()){
        doConnect();

    }
}

void EpsonNode::Serialize(QJsonObject &json)
{
    IONode::Serialize(json);
}

void EpsonNode::doConnect()
{
    if(m_tcpClient->state()!=QAbstractSocket::ConnectedState){
        m_tcpClient->connect();

    }
}

void EpsonNode::doDisconnect()
{
//    if(m_tcpClient->state()==QAbstractSocket::ConnectedState){
        m_tcpClient->disconnect();
//    }
}

void EpsonNode::doSend()
{
    sendCommand(sendData().value<QString>());
}

