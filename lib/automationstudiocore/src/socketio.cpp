#include "socketio.h"
#include "Logger.h"
#include <QNetworkInterface>
#include <QUrl>
#include <QJsonDocument>


SocketIO::SocketIO(QObject *parent, QString appid)
{
    _io=std::unique_ptr<client>(new client());
    using std::placeholders::_1;
    using std::placeholders::_2;
    using std::placeholders::_3;
    using std::placeholders::_4;


    socket::ptr sock = _io->socket();


    QString ioeventname="toapp:"+appid+":doupdate";

    BIND_EVENT(sock,ioeventname.toStdString(),std::bind(&SocketIO::OnDoUpdate,this,_1,_2,_3,_4));



    _io->set_socket_open_listener(std::bind(&SocketIO::OnConnected,this,std::placeholders::_1));
    _io->set_close_listener(std::bind(&SocketIO::OnDisConnected,this,_1));
    _io->set_socket_close_listener(std::bind(&SocketIO::onSocketDisconnect,this,_1));

}


void SocketIO::OnDoUpdate(std::string const& name,message::ptr const& data,bool hasAck,message::list &ack_resp)
{

    LOG_INFO("Update message received");

    if(data->get_flag() == message::flag_object)
    {


        std::map<std::string, message::ptr> eventData= data->get_map();
        message::ptr data_ptr= eventData["updatefile"];
        if(data_ptr){
            QString updatefile=QString::fromStdString(data_ptr->get_string());

            emit doUpdate(updatefile);
        }
    }
}


void SocketIO::OnConnected(const std::string &nsp)
{
    LOG_INFO("Socket IO connected");

    emit socketIOConnected();

    setConnected(true);



}

void SocketIO::OnDisConnected(const client::close_reason &reason)
{
    LOG_INFO("Socket IO disconnected:");

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

    QUrl serverurl(this->m_serverUrl);

    QString host=serverurl.host();
    int port=serverurl.port();

    QString formatedSocketIOUrl="ws://"+host;

    if(port!=-1){
        formatedSocketIOUrl+=":"+QString::number(port);
    }



    LOG_INFO("Connecting to socket IO @:"+formatedSocketIOUrl);
    _io->connect(formatedSocketIOUrl.toStdString());
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
    LOG_INFO("Socket IO disconnected");
}

