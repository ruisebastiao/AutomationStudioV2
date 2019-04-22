#ifndef EPSONNODE_H
#define EPSONNODE_H

#include <flownode.h>
#include <ionode.h>
#include <tcpclient.h>



class EpsonNode : public IONode
{
    Q_OBJECT

    Q_PROPERTY(TCPClient* tcpClient READ tcpClient WRITE setTcpClient NOTIFY tcpClientChanged USER("serializable"))
    Q_PROPERTY(ConnectionType connection READ connection WRITE setConnection NOTIFY connectionChanged USER("serializable"))



public:
    enum class ConnectionType {
        TCPCLIENT,
        SERIAL
    };
    Q_ENUM(ConnectionType)

    EpsonNode();
    ~EpsonNode() override;
    static  QQmlComponent*      delegate(QQmlEngine& engine) noexcept;

    TCPClient* tcpClient() const
    {
        return m_tcpClient;
    }


    Q_INVOKABLE void toogleConnection();
    Q_INVOKABLE void sendCommand(QString command);

    ConnectionType connection() const
    {
        return m_connection;
    }



public slots:
    void setTcpClient(TCPClient* tcpClient)
    {
        if (m_tcpClient == tcpClient)
            return;

        m_tcpClient = tcpClient;
        emit tcpClientChanged(m_tcpClient);
    }

    void setConnection(ConnectionType connection)
    {
        if (m_connection == connection)
            return;

        m_connection = connection;
        emit connectionChanged(m_connection);
    }




    // JsonSerializable interface


public:
    void DeSerialize(QJsonObject &json) override;


signals:
    void tcpClientChanged(TCPClient* tcpClient);

    void connectionChanged(ConnectionType connection);    



private:

    TCPClient* m_tcpClient=nullptr;



    ConnectionType m_connection=ConnectionType::TCPCLIENT;




    // JsonSerializable interface
public:
    void Serialize(QJsonObject &json) override;

    // IONode interface
public slots:
    void doConnect() override;
    void doDisconnect() override;
    void doSend() override;

    // IONode interface
public slots:
    void setCommandReceived(QVariant commandReceived);
};


#endif // EPSONNODE_H
