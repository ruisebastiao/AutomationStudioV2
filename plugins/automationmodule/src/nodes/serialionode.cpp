#include "serialionode.h"

#include <qserialportinfo.h>

SerialIONode::SerialIONode()
{
    m_type=FlowNode::Type::SerialIONode;

    m_serialPort= new QSerialPort(this);

    m_serialPort->setStopBits(QSerialPort::OneStop);
    m_serialPort->setParity(QSerialPort::NoParity);



    connect(m_serialPort, &QSerialPort::readyRead, this, &SerialIONode::handleReadyRead);
    connect(m_serialPort, &QSerialPort::errorOccurred, this, &SerialIONode::handleError);



}

SerialIONode::~SerialIONode()
{
   doDisconnect();
}


void SerialIONode::checkPorts()
{

    m_portsAvailable.clear();
    foreach (QSerialPortInfo serialinfo, QSerialPortInfo::availablePorts()) {
        QString desc=serialinfo.description();
        QString portinfo=serialinfo.portName();


        m_portsAvailable.append(portinfo);


    }

    if(m_portsAvailable.contains(port())==false){
        if(m_deserialized){
            doDisconnect();
        }

    }


    emit portsAvailableChanged(m_portsAvailable);
}


QQmlComponent *SerialIONode::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/SerialIONodeItem.qml"));
    return delegate.get();

}



void SerialIONode::handleReadyRead()
{

    if(m_serialPort->isOpen()){
//        m_readData.append(m_serialPort->readAll());
        setDataReceived(QVariant::fromValue(m_serialPort->readAll()));



//        if(m_readData.contains('\n')){

//            m_readData=m_readData.replace('\n',"");
//            m_readData=m_readData.replace('\r',"");

//            QString temp(m_readData);
//            temp=temp.replace('\n',"");

//            temp=temp.replace(prefix(),"");
//            temp=temp.replace(suffix(),"");

//            setDataReceived(QVariant::fromValue(temp));
//            m_readData="";
//        }


    }
    //    if (!m_timer.isActive())
    //        m_timer.start(5000);
}

void SerialIONode::handleTimeout()
{
    //    if (m_readData.isEmpty()) {
    //        m_standardOutput << QObject::tr("No data was currently available "
    //                                        "for reading from port %1")
    //                            .arg(m_serialPort->portName())
    //                         << endl;
    //    } else {
    //        m_standardOutput << QObject::tr("Data successfully received from port %1")
    //                            .arg(m_serialPort->portName())
    //                         << endl;
    //        m_standardOutput << m_readData << endl;
    //    }

    //    QCoreApplication::quit();
}

void SerialIONode::handleError(QSerialPort::SerialPortError serialPortError)
{
    if (serialPortError == QSerialPort::ReadError) {
        QString errorOutput(QObject::tr("An I/O error occurred while reading "
                                        "the data from port %1, error: %2")
                            .arg(m_serialPort->portName())
                            .arg(m_serialPort->errorString())
                            );

        LOG_ERROR(errorOutput);
        doDisconnect();

    }
}

void SerialIONode::initializeNode(int id)
{

    FlowNode::initializeNode(id);
    checkPorts();


}

void SerialIONode::doConnect()
{
    if(connected()==false){
        setPort(m_port);
        if(m_baudrate>9600){
            m_serialPort->setBaudRate(m_baudrate);
        }
        if (!m_serialPort->open(QIODevice::ReadWrite)) {
            auto error=m_serialPort->error();
            LOG_INFO(QMetaEnum::fromType<QSerialPort::SerialPortError>().valueToKey(error));
            setConnected(false);
            return;
        }else{
            setConnected(true);
        }
    }
}

void SerialIONode::doDisconnect()
{

    m_serialPort->close();
    setConnected(false);

}

void SerialIONode::doSend()
{

    if(m_serialPort->isOpen()){
        std::string strtosend=m_sendData.toString().toStdString()+"\n";
        m_serialPort->write(strtosend.c_str());
    }
}



void SerialIONode::Serialize(QJsonObject &json)
{
    IONode::Serialize(json);
}

void SerialIONode::DeSerialize(QJsonObject &json)
{
    IONode::DeSerialize(json);
    checkPorts();
    if(autoConnect()){
        if(m_portsAvailable.contains(port())){
            setPort(m_port);
            doConnect();
        }
    }


}
