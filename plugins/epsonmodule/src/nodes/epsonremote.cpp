#include "epsonremote.h"

EpsonRemote::EpsonRemote()
{
    m_type=Type::EpsonRemote;


    m_tcpClient=new TCPClient(this);


    m_tcpClient->setConnectOnInit(true);



    connect(m_tcpClient,&TCPClient::stateChanged,[&](QAbstractSocket::SocketState state){
        switch (state) {
        case QAbstractSocket::SocketState::ConnectedState:
            this->setConnected(true);
            break;
        default:
            this->setConnected(false);
            break;
        }
    });


    connect(m_tcpClient,&TCPClient::serverMessage,[&](const QString &message){
        QString messagereceived=message;
        QStringList fullmessage_splitted = messagereceived.split("\r\n");

        for (int var = 0; var < fullmessage_splitted.length(); ++var) {
            QString msg=fullmessage_splitted.at(var);
            if(msg.length()<=0)
                continue;

            QStringList message_splitted=msg.split(",");
            if(message_splitted.length()<2)
                return;
            if (message_splitted[1].indexOf("11") > -1) {
                m_authenticated= false;
                m_tcpClient->write("$Login,auto123");
                continue;

            }

            if (message_splitted[0].indexOf("Login") > -1 && message_splitted[1].indexOf('0') > -1) {
                m_authenticated= true;
                m_tcpClient->write("$Reset,0");
                Utilities::NonBlockingWait(1000);
                m_tcpClient->write("$Start,0");
            }

            if (message_splitted[0].indexOf("GetStatus") > -1) {

                QString binaryString=message_splitted[1];
                if (binaryString.length()==11) {
                    setRobotAuto(binaryString[2]== '1');
                    setSafeGuard(binaryString[5]== '1');
                    setEmrgStop(binaryString[6]== '1');
                    setPaused(binaryString[8]== '1');
                    setRunning(binaryString[9]== '1');
                    setRobotReady(binaryString[10]== '1');

                }

                if(robotAuto()==true && emrgStop()==true){
                    m_tcpClient->write("$Reset,0");
                    Utilities::NonBlockingWait(1000);
                    m_tcpClient->write("$Start,0");
                }


            }
            else  if (message_splitted[0].indexOf("GetIO") > -1) {

                QString io_hex="00"+message_splitted[1];

                bool ok;
                int iVal = io_hex.toInt(&ok,16);
                QString binnumber = io_hex.setNum(iVal, 2);
                binnumber=binnumber.rightJustified(8,'0');



                // LOG_DEBUG(binnumber);
            }


        }

        if(m_epsonRemoteTimer){
            m_epsonRemoteTimer->start(500);
        }


    });




    QObject::connect(m_epsonRemoteTimer, &QTimer::timeout,
                     [=]() {

        if(m_tcpClient->state()==QAbstractSocket::SocketState::ConnectedState){
            m_tcpClient->write("$GetStatus");
        }

        //        m_epsonRemoteTimer->start(1000);

    });

    m_epsonRemoteTimer->setSingleShot(true);





}

EpsonRemote::~EpsonRemote()
{    
    m_epsonRemoteTimer->stop();
    m_epsonRemoteTimer->deleteLater();
    m_epsonRemoteTimer=nullptr;
    m_tcpClient->disconnect();
    m_tcpClient->deleteLater();
    m_tcpClient=nullptr;
    //this->disconnect(m_tcpClient);

}


void EpsonRemote::toogleConnection()
{
    if(m_tcpClient->state()==QAbstractSocket::ConnectedState){
        m_tcpClient->closeConnection();
    }
    else{
        m_tcpClient->connect();
    }
}


QQmlComponent *EpsonRemote::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/EpsonRemoteItem.qml"));
    return delegate.get();

}

void EpsonRemote::DeSerialize(QJsonObject &json)
{
    FlowNode::DeSerialize(json);


}

