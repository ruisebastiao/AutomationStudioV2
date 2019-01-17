#include "tcpclient.h"


TCPClient::TCPClient(QObject *parent) : QObject(parent)
{
    m_socket= new QTcpSocket();

    m_socket->setSocketOption(QAbstractSocket::KeepAliveOption,true);

    m_connectTimer.setSingleShot(true);
    QObject::connect(&m_connectTimer, &QTimer::timeout,[this](){
       this->connect();
    });

    QObject::connect(m_socket, &QAbstractSocket::stateChanged,
                     [=](QAbstractSocket::SocketState state)
    {
        switch (state) {
        case QAbstractSocket::HostLookupState:

            break;
        case QAbstractSocket::ConnectedState:

        default:
            break;
        }
        setState(state);
    });

    QObject::connect(m_socket, &QAbstractSocket::readyRead,
                     [=]()
    {
        emit serverMessage(m_socket->readAll());
    });

    QObject::connect(m_socket, &QAbstractSocket::connected,
                     [=]() {
        LOG_INFO()<<this->host()+"|"+QString::number(this->port())+"|"<<"Socket connected";
         m_connectTimer.stop();
    });

    QObject::connect(m_socket, &QAbstractSocket::disconnected,
                     [=]() {
        LOG_INFO()<<this->host()+"|"+QString::number(this->port())+"|"<<"Socket disconnected";

    });


    QObject::connect(m_socket, static_cast<void(QAbstractSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error),
                     [=](QAbstractSocket::SocketError socketError){
        LOG_INFO()<<this->host()+"|"+QString::number(this->port())+"|"<<"Socket error:"<<socketError;

        m_socket->close();
        if(reconnectOnClose()){

            m_connectTimer.stop();
            m_connectTimer.start(500);
        }


    });


}

TCPClient::~TCPClient()
{
    m_reconnectOnClose=false;
    m_connectTimer.stop();
    m_socket->abort();
    m_socket->disconnectFromHost();
    m_socket->deleteLater();
}

void TCPClient::write(QString message)
{
    if(m_socket->state()== QAbstractSocket::ConnectedState){

        message.append("\r\n");
        int byteswritten=m_socket->write(message.toLocal8Bit());

        if(byteswritten<0)
            m_socket->close();

    }


}


void TCPClient::Serialize(QJsonObject &json)
{

    JsonSerializable::Serialize(json,this);
}

void TCPClient::DeSerialize(QJsonObject &json)
{
    JsonSerializable::DeSerialize(json,this);


    if(connectOnInit()){
        connect();
    }
}

void TCPClient::connect()
{
    disconnect();
    m_socket->connectToHost(m_host,m_port);
}

void TCPClient::disconnect()
{

    m_socket->disconnectFromHost();
}

void TCPClient::setState(const QAbstractSocket::SocketState &state)
{
    m_state = state;
    emit stateChanged(m_state);
}
