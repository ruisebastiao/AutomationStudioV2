#include "barcodereadernode.h"
#include "cutelogger/Logger.h"


BarcodeReaderNode::BarcodeReaderNode(QObject *parent): FlowNode(parent) {

    m_type=Type::BarcodeReaderNode;



    m_serialPort= new QSerialPort(this);
    m_serialPort->setBaudRate(9600);
    m_serialPort->setStopBits(QSerialPort::OneStop);
    m_serialPort->setParity(QSerialPort::NoParity);



    connect(m_serialPort, &QSerialPort::readyRead, this, &BarcodeReaderNode::handleReadyRead);
    connect(m_serialPort, &QSerialPort::errorOccurred, this, &BarcodeReaderNode::handleError);
    //    connect(&m_timer, &QTimer::timeout, this, &BarcodeReaderNode::handleTimeout);





}
BarcodeReaderNode::~BarcodeReaderNode(){
    m_serialPort->close();
}

void BarcodeReaderNode::handleReadyRead()
{

    if(m_serialPort->isOpen()){
        m_readData.append(m_serialPort->readAll());
        QString temp(m_readData);
        temp=temp.replace('\n',"");
        m_rawdata=QVariant::fromValue(temp);


        if(m_readData.contains('\n')){

            m_readData=m_readData.replace('\n',"");
            m_readData=m_readData.replace('\r',"");

            QString temp(m_readData);
            temp=temp.replace('\n',"");

            temp=temp.replace(prefix(),"");
            temp=temp.replace(suffix(),"");

            m_dataout=QVariant::fromValue(temp);




            setDataout(m_dataout);
            m_readData="";
            m_rawdata="";
        }

        setRawdata(m_rawdata);
    }
    //    if (!m_timer.isActive())
    //        m_timer.start(5000);
}

void BarcodeReaderNode::handleTimeout()
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

void BarcodeReaderNode::handleError(QSerialPort::SerialPortError serialPortError)
{
    if (serialPortError == QSerialPort::ReadError) {
        QString errorOutput(QObject::tr("An I/O error occurred while reading "
                                        "the data from port %1, error: %2")
                            .arg(m_serialPort->portName())
                            .arg(m_serialPort->errorString())
                            );

        LOG_ERROR(errorOutput);
        m_serialPort->close();
        setOpened(false);

    }
}



void BarcodeReaderNode::inNodeOutputChanged()
{
    FlowNode::inNodeOutputChanged();

}




QQmlComponent*  BarcodeReaderNode::delegate(QQmlEngine& engine) noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/BarcodeReaderNodeItem.qml"));
    return delegate.get();
}

void BarcodeReaderNode::checkPorts()
{

    m_portsAvailable.clear();
    foreach (QSerialPortInfo serialinfo, QSerialPortInfo::availablePorts()) {
        QString desc=serialinfo.description();
        QString portinfo=serialinfo.portName();


        m_portsAvailable.append(portinfo);


    }

    if(m_portsAvailable.contains(port())==false){
        m_serialPort->close();
        setOpened(false);
    }

    if(openOnConnect()){
        if(m_portsAvailable.contains(port())){
            setPort(m_port);
        }
    }

    emit portsAvailableChanged(m_portsAvailable);
}


void BarcodeReaderNode::DeSerialize(QJsonObject &json)
{


    FlowNode::DeSerialize(json);

    emit triggerEnabledChanged(m_triggerEnabled);

    setConfigsLoaded(true);

    checkPorts();

}

void BarcodeReaderNode::initializeNode(int id)
{
    FlowNode::initializeNode(id);
    checkPorts();


}
