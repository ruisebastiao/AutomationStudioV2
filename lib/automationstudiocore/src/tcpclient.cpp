#include "tcpclient.h"

TCPClient::TCPClient(QObject *parent) : QObject(parent)
{

}

void TCPClient::Serialize(QJsonObject &json)
{

    JsonSerializable::Serialize(json,this);
}

void TCPClient::DeSerialize(QJsonObject &json)
{
    JsonSerializable::DeSerialize(json,this);
}
