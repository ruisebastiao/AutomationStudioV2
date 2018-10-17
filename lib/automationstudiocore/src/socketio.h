#ifndef SOCKETIO_H
#define SOCKETIO_H

#include "automationstudiocoreglobal.h"
#include "jsonserializable.h"

#include <QObject>
#include <QJsonObject>


#undef emit
#include <sio_client.h>
# define emit
using namespace sio;


#ifdef WIN32
#define BIND_EVENT(IO,EV,FN) \
    do{ \
    socket::event_listener_aux l = FN;\
    IO->on(EV,l);\
    } while(0)

#else
#define BIND_EVENT(IO,EV,FN) \
    IO->on(EV,FN)
#endif



class AUTOMATIONSTUDIO_CORE_EXPORT  SocketIO :public QObject,public JsonSerializable
{
    Q_OBJECT

    Q_PROPERTY(QString serverUrl READ serverUrl WRITE setServerUrl NOTIFY serverUrlChanged USER("serialize"))

    Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged)



public:
    SocketIO(QObject *parent = nullptr);


private:

    std::unique_ptr<client> _io;

    void OnConnected(const std::string &nsp);
    void OnDisConnected(client::close_reason const& reason);
    void OnFailed();
    void onSocketDisconnect(std::string const& nsp);

    void OnDoUpdate(const std::string &name, const message::ptr &data, bool hasAck, message::list &ack_resp);

    // JsonSerializable interface
    QString m_serverUrl="";

    bool m_connected=false;

public:
    virtual void Serialize(QJsonObject &json) override;
    virtual void DeSerialize(QJsonObject &json) override;
    QString serverUrl() const
    {
        return m_serverUrl;
    }
    void init();
    void send(QString eventname, QString eventdata, const std::function<void (const message::list &)> &ack=nullptr);

    bool connected() const
    {
        return m_connected;
    }



public slots:
    void setServerUrl(QString serverUrl)
    {
        if (m_serverUrl == serverUrl)
            return;

        m_serverUrl = serverUrl;
        emit serverUrlChanged(m_serverUrl);
    }
    void setConnected(bool connected)
    {
        if (m_connected == connected)
            return;

        m_connected = connected;
        emit connectedChanged(m_connected);
    }

signals:
    void serverUrlChanged(QString serverUrl);
    void socketIOConnected();
    void socketIODiscConnected();

    void doUpdate(QString releasename);

    void connectedChanged(bool connected);
};

#endif // SOCKETIO_H
