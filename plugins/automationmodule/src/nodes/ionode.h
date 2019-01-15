#ifndef IONODE_H
#define IONODE_H

#include "flownode.h"



class AUTOMATIONMODULE_EXPORT IONode: public FlowNode
{
    Q_OBJECT

    Q_PROPERTY(QVariant sendData READ sendData WRITE setSendData NOTIFY sendDataChanged REVISION 30)
    Q_PROPERTY(bool autoConnect READ autoConnect WRITE setAutoConnect NOTIFY autoConnectChanged USER("serialize"))
    Q_PROPERTY(QVariant ready READ ready WRITE setReady NOTIFY readyChanged REVISION 31)
    Q_PROPERTY(QString readyCommand READ readyCommand WRITE setReadyCommand NOTIFY readyCommandChanged  USER("serialize"))

    Q_PROPERTY(bool send READ send WRITE setSend NOTIFY sendChanged REVISION 30)

    Q_PROPERTY(QVariant dataReceived READ dataReceived WRITE setDataReceived NOTIFY dataReceivedChanged)

    Q_PROPERTY(QVariant commandReceived READ commandReceived WRITE setCommandReceived NOTIFY commandReceivedChanged REVISION 31)

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

        if(datareceived.contains('\n')){
            QString command="";
            QList<QString> commands= datareceived.split('\n');
            for (int var = 0; var < commands.length(); ++var) {
                command=commands[var];
                command=command.remove('\r');
                if(command==readyCommand() && command.length()>0 && readyCommand().length()>0){
                    setReady(true);
                }
                if(command.length()>0){
                    setCommandReceived(command);
                }

            }
            if(command.length()>0){
                alldatareceived+=command;
            }
            else {
                alldatareceived="";
            }
        }
        else{
            alldatareceived+=datareceived;
        }



        m_dataReceived=QVariant::fromValue(datareceived);
        emit dataReceivedChanged(m_dataReceived);
    }

    void setSend(bool send)
    {


        m_send = send;
        if(m_send && m_ready.value<bool>()){
            doSend();
        }
        emit sendChanged(m_send);
    }

    void setConnected(QVariant connected)
    {
        if(connected.value<bool>()){
            if(m_readyCommand==""){
                setReady(true);
            }
        }
        else if(m_connected.value<bool>() && connected.value<bool>()==false){
            setReady(false);
        }
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

    void setCommandReceived(QVariant commandReceived)
    {


        m_commandReceived = commandReceived;
        emit commandReceivedChanged(m_commandReceived);
    }

    void setReady(QVariant ready)
    {
        if (m_ready == ready)
            return;

        m_ready = ready;
        emit readyChanged(m_ready);
    }

    void setReadyCommand(QString readyCommand)
    {


        if (m_readyCommand == readyCommand)
            return;

        m_readyCommand = readyCommand;
        emit readyCommandChanged(m_readyCommand);
    }

signals:
    void sendDataChanged(QVariant sendData);

    void dataReceivedChanged(QVariant dataReceived);

    void sendChanged(bool send);

    void connectedChanged(QVariant connected);

    void autoConnectChanged(bool autoConnect);

    void commandReceivedChanged(QVariant commandReceived);

    void readyChanged(QVariant ready);

    void readyCommandChanged(QString readyCommand);

protected:
    QVariant m_sendData=QVariant::fromValue(QString(""));
    QVariant m_dataReceived=QVariant::fromValue(QString(""));

private:


    // JsonSerializable interface
    bool m_send=false;

    QString alldatareceived="";

    QVariant m_connected=QVariant::fromValue(false);

    bool m_autoConnect=false;

    QVariant m_commandReceived=QVariant::fromValue(QString(""));

    QVariant m_ready=false;

    QString m_readyCommand="";

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
    QVariant commandReceived() const
    {
        return m_commandReceived;
    }
    QVariant ready() const
    {
        return m_ready;
    }
    QString readyCommand() const
    {
        return m_readyCommand;
    }

    // FlowNode interface
public slots:
    virtual void setProjectLoaded(bool projectLoaded) override;
};

#endif // IONODE_H
