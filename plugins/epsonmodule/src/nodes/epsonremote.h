#ifndef EPSONREMOTE_H
#define EPSONREMOTE_H

#include <flownode.h>
#include <tcpclient.h>



class EpsonRemote:public FlowNode
{
    Q_OBJECT

    Q_PROPERTY(TCPClient* tcpClient READ tcpClient WRITE setTcpClient NOTIFY tcpClientChanged USER("serializable"))
    Q_PROPERTY(QVariant connected READ connected WRITE setConnected NOTIFY connectedChanged REVISION 31)

    Q_PROPERTY(QVariant paused READ paused WRITE setPaused NOTIFY pausedChanged  REVISION 31)

    Q_PROPERTY(QVariant running READ running WRITE setRunning NOTIFY runningChanged  REVISION 31)

    Q_PROPERTY(QVariant robotReady READ robotReady WRITE setRobotReady NOTIFY robotReadyChanged  REVISION 31)

    Q_PROPERTY(QVariant robotAuto READ robotAuto WRITE setRobotAuto NOTIFY robotAutoChanged  REVISION 31)

    Q_PROPERTY(QVariant safeGuard READ safeGuard WRITE setSafeGuard NOTIFY safeGuardChanged  REVISION 31)

    Q_PROPERTY(QVariant emrgStop READ emrgStop WRITE setEmrgStop NOTIFY emrgStopChanged  REVISION 31)




public:
    EpsonRemote();
    ~EpsonRemote() override;

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

    void setConnected(QVariant connected)
    {

        if(connected.value<bool>()!=m_connected.value<bool>()){
            if(connected.value<bool>()){
                m_epsonRemoteTimer->start(500);
            }
            else{
                setPaused(false);
                setRunning(false);
                setRobotAuto(false);
                setSafeGuard(false);
                setEmrgStop(false);
            }
        }

        m_connected = connected;
        emit connectedChanged(m_connected);
    }





    void setRobotAuto(QVariant robotAuto)
    {
        if (m_robotAuto == robotAuto)
            return;

        m_robotAuto = robotAuto;

        LOG_INFO()<<*this<<"Auto changed:"<<robotAuto;

        if(m_robotAuto.value<bool>()){
             m_tcpClient->write("$Start,0");
        }
        emit robotAutoChanged(m_robotAuto);
    }

    void setPaused(QVariant paused)
    {
        if (m_paused == paused)
            return;

        m_paused = paused;

        emit pausedChanged(m_paused);
    }

    void setRunning(QVariant running)
    {
        if (m_running == running)
            return;

        m_running = running;
        LOG_INFO()<<*this<<"Running changed:"<<running;
        emit runningChanged(m_running);
    }

    void setRobotReady(QVariant robotReady)
    {
        if (m_robotReady == robotReady)
            return;

        if(m_robotReady.value<bool>()){
             m_tcpClient->write("$Reset,0");
        }
        m_robotReady = robotReady;
        LOG_INFO()<<*this<<"Ready changed:"<<robotReady;
        emit robotReadyChanged(m_robotReady);
    }

    void setSafeGuard(QVariant safeGuard)
    {
        if (m_safeGuard == safeGuard)
            return;

        m_safeGuard = safeGuard;
        if(this->safeGuard()==false){
            Utilities::NonBlockingWait(1500);
            m_tcpClient->write("$Continue,0");
        }
        emit safeGuardChanged(m_safeGuard);
    }

    void setEmrgStop(QVariant emrgStop)
    {
        if (m_emrgStop == emrgStop)
            return;

        m_emrgStop = emrgStop;


        emit emrgStopChanged(m_emrgStop);
    }

signals:
    void tcpClientChanged(TCPClient* tcpClient);

    void connectedChanged(QVariant connected);

    void pausedChanged(QVariant paused);

    void runningChanged(QVariant running);

    void robotReadyChanged(QVariant robotReady);

    void robotAutoChanged(QVariant robotAuto);

    void safeGuardChanged(QVariant safeGuard);

    void emrgStopChanged(QVariant emrgStop);

public:
    void DeSerialize(QJsonObject &json) override;
    Q_INVOKABLE void toogleConnection();
    QVariant connected() const
    {
        return m_connected;
    }
    QVariant paused() const
    {
        return m_paused;
    }

    QVariant running() const
    {
        return m_running;
    }

    QVariant robotReady() const
    {
        return m_robotReady;
    }

    QVariant robotAuto() const
    {
        return m_robotAuto;
    }

    QVariant safeGuard() const
    {
        return m_safeGuard;
    }

    QVariant emrgStop() const
    {
        return m_emrgStop;
    }

private:

    TCPClient* m_tcpClient=new TCPClient();

    // JsonSerializable interface
    QVariant m_connected=false;

    bool m_authenticated=false;

    QVariant m_paused=false;
    QVariant m_running=false;
    QVariant m_robotReady=false;
    QTimer *m_epsonRemoteTimer= new QTimer();

    QVariant m_robotAuto=false;
    QVariant m_safeGuard=false;
    QVariant m_emrgStop=false;
};

#endif // EPSONREMOTE_H
