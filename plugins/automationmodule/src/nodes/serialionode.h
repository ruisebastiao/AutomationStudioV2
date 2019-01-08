#ifndef SERIALIONODE_H
#define SERIALIONODE_H

#include "ionode.h"

#include <qserialport.h>



class SerialIONode:public IONode
{
    Q_OBJECT
    Q_PROPERTY(QString port READ port WRITE setPort NOTIFY portChanged USER("serialize"))

    Q_PROPERTY(QString prefix READ prefix WRITE setPrefix NOTIFY prefixChanged USER("serialize"))
    Q_PROPERTY(QString suffix READ suffix WRITE setSuffix NOTIFY suffixChanged USER("serialize"))


    Q_PROPERTY(QStringList portsAvailable READ portsAvailable NOTIFY portsAvailableChanged)







public:
    SerialIONode();
    ~SerialIONode() override;

private:

    // JsonSerializable interface
    QString m_port="";


    QString m_prefix="";

    QString m_suffix="";

    QStringList m_portsAvailable;

    QSerialPort *m_serialPort = nullptr;
    QByteArray m_readData;
    QTextStream m_standardOutput;
    QTimer m_timer;

public:
    void Serialize(QJsonObject &json) override;
    void DeSerialize(QJsonObject &json) override;
    static QQmlComponent *delegate(QQmlEngine &engine) noexcept;
    QString port() const
    {
        return m_port;
    }


    QString prefix() const
    {
        return m_prefix;
    }

    QString suffix() const
    {
        return m_suffix;
    }

    QStringList portsAvailable() const
    {
        return m_portsAvailable;
    }

public slots:

    int indexOfPort(QString portname){
        return m_portsAvailable.indexOf(portname);
    }

    void checkPorts();

    void setPort(QString port)
    {
        if(port=="")
            return;



        m_port = port;
        m_serialPort->setPortName(m_port);




        emit portChanged(m_port);
    }


    void setPrefix(QString prefix)
    {
        if (m_prefix == prefix)
            return;

        m_prefix = prefix;
        emit prefixChanged(m_prefix);
    }

    void setSuffix(QString suffix)
    {
        if (m_suffix == suffix)
            return;

        m_suffix = suffix;
        emit suffixChanged(m_suffix);
    }

private slots:
    void handleReadyRead();
    void handleTimeout();
    void handleError(QSerialPort::SerialPortError error);



signals:
    void portChanged(QString port);

    void prefixChanged(QString prefix);
    void suffixChanged(QString suffix);
    void portsAvailableChanged(QStringList portsAvailable);

    // FlowNode interface
public:
    void initializeNode(int id) override;

    // IONode interface
public slots:
    void doConnect() override;

    // IONode interface
public slots:
    void doSend() override;
    void doDisconnect() override;
};

#endif // SERIALIONODE_H
