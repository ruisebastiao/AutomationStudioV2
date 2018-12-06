#ifndef EPSONNODE_H
#define EPSONNODE_H

#include <flownode.h>
#include <tcpclient.h>



class EpsonNode : public FlowNode
{
    Q_OBJECT

    Q_PROPERTY(TCPClient* tcpClient READ tcpClient WRITE setTcpClient NOTIFY tcpClientChanged USER("serializable"))
    Q_PROPERTY(ConnectionType connection READ connection WRITE setConnection NOTIFY connectionChanged USER("serializable"))

    Q_PROPERTY(bool connected READ connected WRITE setConnected NOTIFY connectedChanged REVISION 31)

    Q_PROPERTY(QVariant dataReceived READ dataReceived WRITE setDataReceived NOTIFY dataReceivedChanged REVISION 31)

    Q_PROPERTY(QVariant epsonNode READ epsonNode WRITE setEpsonNode NOTIFY epsonNodeChanged REVISION 31)




public:
    enum class ConnectionType {
        TCPCLIENT,
        SERIAL
    };
    Q_ENUM(ConnectionType)

    EpsonNode();
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

    bool connected() const
    {
        return m_connected;
    }

    QVariant epsonNode() const
    {
        return m_epsonNode;
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

    void setConnected(bool connected)
    {
        if (m_connected == connected)
            return;

        m_connected = connected;
        emit connectedChanged(m_connected);
    }


    // JsonSerializable interface
    void setDataReceived(QVariant dataReceived)
    {

        m_dataReceived = dataReceived;
        emit dataReceivedChanged(m_dataReceived);
    }

public:
    void DeSerialize(QJsonObject &json) override;

    QVariant dataReceived() const
    {
        return m_dataReceived;
    }

signals:
    void tcpClientChanged(TCPClient* tcpClient);

    void connectionChanged(ConnectionType connection);

    void connectedChanged(bool connected);

    void epsonNodeChanged(QVariant epsonNode);

    void dataReceivedChanged(QVariant dataReceived);

private:
    void setEpsonNode(QVariant epsonNode)
    {

        m_epsonNode = epsonNode;
        emit epsonNodeChanged(m_epsonNode);
    }

    TCPClient* m_tcpClient=nullptr;
    ConnectionType m_connection=ConnectionType::TCPCLIENT;
    bool m_connected=false;
    QVariant m_epsonNode;
    QVariant m_dataReceived=QVariant::fromValue(QString(""));
};


#endif // EPSONNODE_H
