#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <qtimer.h>
#include "automationstudiocoreglobal.h"
#include "jsonserializable.h"
#include "QAbstractSocket"
#include "Logger.h"

class AUTOMATIONSTUDIO_CORE_EXPORT TCPClient : public QObject, public JsonSerializable
{
    Q_OBJECT

    Q_PROPERTY(QString host READ host WRITE setHost NOTIFY hostChanged USER("seriablizable"))
    Q_PROPERTY(uint port READ port WRITE setPort NOTIFY portChanged USER("seriablizable"))

    Q_PROPERTY(bool connectOnInit READ connectOnInit WRITE setConnectOnInit NOTIFY connectOnInitChanged USER("seriablizable"))
    Q_PROPERTY(bool reconnectOnClose READ reconnectOnClose WRITE setReconnectOnClose NOTIFY reconnectOnCloseChanged USER("seriablizable"))

    Q_PROPERTY(QAbstractSocket::SocketState state READ state NOTIFY stateChanged)


public:
    Q_ENUMS(QAbstractSocket::SocketState)
    explicit TCPClient(QObject *parent = nullptr);
    ~TCPClient() override;

    void write(QString message);

    void closeConnection();


signals:

    void hostChanged(QString host);

    void portChanged(uint port);

    void connectOnInitChanged(bool connectOnInit);

    void stateChanged(QAbstractSocket::SocketState state);

    void serverMessage(const QString &message);

    void reconnectOnCloseChanged(bool reconnectOnClose);

public slots:

    // JsonSerializable interface
    void setHost(QString host)
    {
        if (m_host == host)
            return;

        m_host = host;
        emit hostChanged(m_host);
    }

    void setPort(uint port)
    {
        if (m_port == port)
            return;

        m_port = port;
        emit portChanged(m_port);
    }

    void setConnectOnInit(bool connectOnInit)
    {
        if (m_connectOnInit == connectOnInit)
            return;

        m_connectOnInit = connectOnInit;
        emit connectOnInitChanged(m_connectOnInit);
    }

    void setReconnectOnClose(bool reconnectOnClose)
    {
        if (m_reconnectOnClose == reconnectOnClose)
            return;

        m_reconnectOnClose = reconnectOnClose;
        emit reconnectOnCloseChanged(m_reconnectOnClose);
    }

public:
    virtual void Serialize(QJsonObject &json) override;
    virtual void DeSerialize(QJsonObject &json) override;

    void connect();

    QString host() const
    {
        return m_host;
    }

    uint port() const
    {
        return m_port;
    }

    bool connectOnInit() const
    {
        return m_connectOnInit;
    }

    QAbstractSocket::SocketState state() const
    {
        return m_state;
    }

    void setState(const QAbstractSocket::SocketState &state);

    bool reconnectOnClose() const
    {
        return m_reconnectOnClose;
    }

private:

    QString m_host="";
    uint m_port=9601;
    QTimer m_connectTimer;
    QTcpSocket *m_socket = nullptr;

    bool m_connectOnInit=true;
    QAbstractSocket::SocketState m_state = QAbstractSocket::UnconnectedState;
    bool m_reconnectOnClose=false;
};


#endif // TCPCLIENT_H
