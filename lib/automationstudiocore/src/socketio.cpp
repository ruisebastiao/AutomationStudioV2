#include "socketio.h"
#include "Logger.h"

#include <QJsonDocument>


SocketIO::SocketIO(QObject *parent)
{
    _io=std::unique_ptr<client>(new client());
    using std::placeholders::_1;
    using std::placeholders::_2;
    using std::placeholders::_3;
    using std::placeholders::_4;


    socket::ptr sock = _io->socket();



    _io->set_socket_open_listener(std::bind(&SocketIO::OnConnected,this,std::placeholders::_1));
    _io->set_close_listener(std::bind(&SocketIO::OnDisConnected,this,_1));
    _io->set_socket_close_listener(std::bind(&SocketIO::onSocketDisconnect,this,_1));

}

void SocketIO::OnConnected(const std::string &nsp)
{
    LOG_INFO("Socket IO connected");

    emit socketIOConnected();

    setConnected(true);



}

void SocketIO::OnDisConnected(const client::close_reason &reason)
{
    LOG_INFO("Socket IO disconnected");

    emit socketIODiscConnected();

    setConnected(false);
}

void SocketIO::Serialize(QJsonObject &json)
{
    JsonSerializable::Serialize(json,this);
}

void SocketIO::DeSerialize(QJsonObject &json)
{
    JsonSerializable::DeSerialize(json,this);
}

void SocketIO::init(){

    _io->set_fail_listener(std::bind(&SocketIO::OnFailed,this));


    LOG_INFO("Connecting to socket IO @:"+this->serverUrl());
    _io->connect("ws://"+this->serverUrl().toStdString());
}

void SocketIO::send(QString eventname,QString eventdata, std::function<void (message::list const&)> const& ack){

#undef emit
    _io->socket()->emit(eventname.toStdString(), eventdata.toStdString(),ack);
# define emit


}

void SocketIO::OnFailed(){
    LOG_INFO("Socket IO failed to connect");

    setConnected(false);

}

void SocketIO::onSocketDisconnect(const std::string &nsp)
{
    LOG_INFO("Socket IO disconnected 2");
}

