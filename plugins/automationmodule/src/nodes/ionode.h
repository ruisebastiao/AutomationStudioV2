#ifndef IONODE_H
#define IONODE_H

#include "flownode.h"



class AUTOMATIONMODULE_EXPORT IONode: public FlowNode
{
    Q_OBJECT

    Q_PROPERTY(QVariant sendData READ sendData WRITE setSendData NOTIFY sendDataChanged REVISION 30)
    Q_PROPERTY(bool autoConnect READ autoConnect WRITE setAutoConnect NOTIFY autoConnectChanged USER("serialize"))

    Q_PROPERTY(bool send READ send WRITE setSend NOTIFY sendChanged REVISION 30)

    Q_PROPERTY(QVariant dataReceived READ dataReceived WRITE setDataReceived NOTIFY dataReceivedChanged REVISION 31)
    Q_PROPERTY(QVariant connected READ connected WRITE setConnected NOTIFY connectedChanged REVISION 31)


public:
    IONode();

    QVariant sendData() const
    {
        return m_sendData;
    }

    QVariant dataReceived() const
    {
        return m_dataReceived;
    }

public slots:

    virtual void doConnect(){

    }

    virtual void doDisconnect(){

    }

    virtual void doSend(){

    }


    void setSendData(QVariant sendData)
    {


        m_sendData = sendData;
        emit sendDataChanged(m_sendData);
    }

    void setDataReceived(QVariant dataReceived)
    {

        m_dataReceived = dataReceived;
        QString datareceived=m_dataReceived.value<QString>();
        datareceived=datareceived.replace("\n","");
        datareceived=datareceived.replace("\r","");
        m_dataReceived=QVariant::fromValue(datareceived);
        emit dataReceivedChanged(m_dataReceived);
    }

    void setSend(bool send)
    {


        m_send = send;
        if(m_send){
            doSend();
        }
        emit sendChanged(m_send);
    }

    void setConnected(QVariant connected)
    {

        m_connected = connected;
        emit connectedChanged(m_connected);
    }

    void setAutoConnect(bool autoConnect)
    {
        if (m_autoConnect == autoConnect)
            return;

        m_autoConnect = autoConnect;
        emit autoConnectChanged(m_autoConnect);
    }

signals:
    void sendDataChanged(QVariant sendData);

    void dataReceivedChanged(QVariant dataReceived);

    void sendChanged(bool send);

    void connectedChanged(QVariant connected);

    void autoConnectChanged(bool autoConnect);

protected:
    QVariant m_sendData=QVariant::fromValue(QString(""));
    QVariant m_dataReceived=QVariant::fromValue(QString(""));

private:


    // JsonSerializable interface
    bool m_send=false;

    QVariant m_connected=QVariant::fromValue(false);

    bool m_autoConnect=false;

public:
    void Serialize(QJsonObject &json) override;
    void DeSerialize(QJsonObject &json) override;
    bool send() const
    {
        return m_send;
    }
    QVariant connected() const
    {
        return m_connected;
    }
    bool autoConnect() const
    {
        return m_autoConnect;
    }
};

#endif // IONODE_H
