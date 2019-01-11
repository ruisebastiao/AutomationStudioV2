#ifndef EPSONREMOTE_H
#define EPSONREMOTE_H

#include <flownode.h>
#include <tcpclient.h>



class EpsonRemote:public FlowNode
{
    Q_OBJECT

    Q_PROPERTY(TCPClient* tcpClient READ tcpClient WRITE setTcpClient NOTIFY tcpClientChanged USER("serializable"))



public:
    EpsonRemote();

    static  QQmlComponent*      delegate(QQmlEngine& engine) noexcept;

    TCPClient* tcpClient() const
    {
        return m_tcpClient;
    }

public slots:
    void setTcpClient(TCPClient* tcpClient)
    {
        if (m_tcpClient == tcpClient)
            return;

        m_tcpClient = tcpClient;
        emit tcpClientChanged(m_tcpClient);
    }

signals:
    void tcpClientChanged(TCPClient* tcpClient);

private:

    TCPClient* m_tcpClient=nullptr;
};

#endif // EPSONREMOTE_H
