#ifndef BARCODEREADERNODE_H
#define BARCODEREADERNODE_H

#include "flownode.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include "cutelogger/Logger.h"


class BarcodeReaderNode : public FlowNode
{
    Q_OBJECT

    Q_PROPERTY(bool triggerEnabled READ triggerEnabled WRITE setTriggerEnabled NOTIFY triggerEnabledChanged USER("serialize"))
    Q_PROPERTY(QString port READ port WRITE setPort NOTIFY portChanged USER("serialize"))

    Q_PROPERTY(bool openOnConnect READ openOnConnect WRITE setOpenOnConnect NOTIFY openOnConnectChanged USER("serialize"))

    Q_PROPERTY(QString prefix READ prefix WRITE setPrefix NOTIFY prefixChanged USER("serialize"))
    Q_PROPERTY(QString suffix READ suffix WRITE setSuffix NOTIFY suffixChanged USER("serialize"))


    Q_PROPERTY(bool opened READ opened WRITE setOpened NOTIFY openedChanged REVISION 31)



    Q_PROPERTY(QString dataout READ dataout WRITE setDataout NOTIFY dataoutChanged REVISION 31)


    Q_PROPERTY(QString rawdata READ rawdata WRITE setRawdata NOTIFY rawdataChanged REVISION 31)



    Q_PROPERTY(QStringList portsAvailable READ portsAvailable NOTIFY portsAvailableChanged)


    Q_PROPERTY(bool trigger READ trigger WRITE setTrigger NOTIFY triggerChanged)


public:



    BarcodeReaderNode(QObject* parent=nullptr);


    ~BarcodeReaderNode();

    static  QQmlComponent*      delegate(QQmlEngine& engine) noexcept;


private:
    QSerialPort *m_serialPort = nullptr;
    QByteArray m_readData;
    QTextStream m_standardOutput;
    QTimer m_timer;

public slots:

    int indexOfPort(QString portname){
        return m_portsAvailable.indexOf(portname);
    }

    void checkPorts();

    bool triggerEnabled() const
    {
        return m_triggerEnabled;
    }

    QString port() const
    {
        return m_port;
    }



    void setTriggerEnabled(bool triggerEnabled)
    {
        if (m_triggerEnabled == triggerEnabled)
            return;


        m_triggerEnabled = triggerEnabled;
        emit triggerEnabledChanged(m_triggerEnabled);
    }

    void setPort(QString port)
    {

        if(port=="")
            return;

        if(m_serialPort->isOpen()){
            m_serialPort->close();
        }

        m_port = port;
        m_serialPort->setPortName(m_port);
        if (!m_serialPort->open(QIODevice::ReadWrite)) {
            auto error=m_serialPort->error();
            LOG_INFO(QMetaEnum::fromType<QSerialPort::SerialPortError>().valueToKey(error));
            setOpened(false);
            return;
        }else{
            setOpened(true);
        }


        emit portChanged(m_port);
    }






    void setOpened(bool opened)
    {
        if (m_opened == opened)
            return;

        m_opened = opened;
        emit openedChanged(m_opened);
    }

    void setTrigger(bool trigger)
    {
        if (m_trigger == trigger)
            return;

        m_trigger = trigger;
        emit triggerChanged(m_trigger);
    }

    void setDataout(QString dataout)
    {

        m_dataout = dataout;
        emit dataoutChanged(m_dataout);
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



    void setOpenOnConnect(bool openOnConnect)
    {
        if (m_openOnConnect == openOnConnect)
            return;

        m_openOnConnect = openOnConnect;
        emit openOnConnectChanged(m_openOnConnect);
    }

    void setRawdata(QString rawdata)
    {


        m_rawdata = rawdata;
        emit rawdataChanged(m_rawdata);
    }

protected slots:
    void                inNodeOutputChanged();

signals:


    void triggerEnabledChanged(bool triggerEnabled);

    void portChanged(QString port);


    void openedChanged(bool opened);

    void triggerChanged(bool trigger);

    void portsAvailableChanged(QStringList portsAvailable);

    void dataoutChanged(QString dataout);

    void prefixChanged(QString prefix);

    void suffixChanged(QString suffix);



    void openOnConnectChanged(bool openOnConnect);

    void rawdataChanged(QString rawdata);



private:


    bool m_triggerEnabled=false;
    QString m_port="";


    bool m_opened=false;

    bool m_trigger=false;

    QStringList m_portsAvailable;

    QString m_dataout;

    QString m_prefix="";

    QString m_suffix="";

    bool m_openOnConnect=false;

    QString m_rawdata="";


private slots:
    void handleReadyRead();
    void handleTimeout();
    void handleError(QSerialPort::SerialPortError error);



    // FlowNode interface
public:

    bool opened() const
    {
        return m_opened;
    }
    bool trigger() const
    {
        return m_trigger;
    }
    QStringList portsAvailable() const
    {
        return m_portsAvailable;
    }
    QString dataout() const
    {
        return m_dataout;
    }
    QString prefix() const
    {
        return m_prefix;
    }
    QString suffix() const
    {
        return m_suffix;
    }

    void DeSerialize(QJsonObject &json);

    // FlowNode interface
public:

    bool openOnConnect() const
    {
        return m_openOnConnect;
    }
    QString rawdata() const
    {
        return m_rawdata;
    }
};



#endif // BARCODEREADERNODE_H
