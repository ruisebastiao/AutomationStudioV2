#include "webservicenode.h"

WebServiceNode::WebServiceNode(QObject *parent){

    m_type=Type::WebServiceNode;

    m_replytimer= new QTimer(this);

    m_replytimer->setSingleShot(true);

    m_manager=new QNetworkAccessManager(this);
    connect(m_manager,&QNetworkAccessManager::finished,[=](QNetworkReply* reply){

        if(reply->error()!=QNetworkReply::NoError){
            LOG_ERROR()<<"Network error:"<<reply->errorString();
            setError(reply->errorString());
        }

        setExecuting(false);

        m_replytimer->stop();

        reply->deleteLater();
        reply=nullptr;


    });




}





QQmlComponent *WebServiceNode::delegate(QQmlEngine &engine)
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/WebServiceNodeItem.qml"));
    return delegate.get();
}

void WebServiceNode::makeRequest()
{
    QUrl url(m_serviceUrl+m_formattedUrl);
    setError("");
    setResponse("");


    if(this->executing()){
        setError("À espera de resposta do servidor");
        return;

    }
    setExecuting(true);

    QNetworkReply* reply = m_manager->get(QNetworkRequest(url));





    connect(m_replytimer, &QTimer::timeout, [&](){
//        if(reply){
//        setExecuting(false);
//        }
        setError("Erro de resposta do servidor");
        setExecuting(false);
    });

    m_replytimer->start(5000);


    connect(reply, &QNetworkReply::readyRead,[=](){
        /* ... */


        QString data=reply->readAll();


        this->setResponse(data);
        setExecuting(false);
        m_replytimer->stop();
        reply->deleteLater();
    });


    connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error),
            [=](QNetworkReply::NetworkError code){
        /* ... */

        setExecuting(false);

        m_replytimer->stop();

        if(code!=QNetworkReply::UnknownNetworkError){
            setError(reply->errorString());
        }


        reply->deleteLater();
    });

}

void WebServiceNode::Serialize(QJsonObject &json)
{
    FlowNode::Serialize(json);

}

void WebServiceNode::DeSerialize(QJsonObject &json)
{



    FlowNode::DeSerialize(json);

}

void WebServiceNode::initializePorts()
{
    m_param1Port=new FlowNodePort(this,qan::PortItem::Type::In,"param1");
    m_param1NamePort=new FlowNodePort(this,qan::PortItem::Type::In,"param1Name");
    m_param2Port=new FlowNodePort(this,qan::PortItem::Type::In,"param2");
    m_param2NamePort=new FlowNodePort(this,qan::PortItem::Type::In,"param2Name");

    m_inPorts.append(m_param1Port);
    m_inPorts.append(m_param1NamePort);
    m_inPorts.append(m_param2Port);
    m_inPorts.append(m_param2NamePort);


    m_responsePort=new FlowNodePort(this,qan::PortItem::Type::Out,"response");
    m_executingPort=new FlowNodePort(this,qan::PortItem::Type::Out,"executing");
    m_errorPort=new FlowNodePort(this,qan::PortItem::Type::Out,"error");

    m_outPorts.append(m_responsePort);
    m_outPorts.append(m_executingPort);
    m_outPorts.append(m_errorPort);

}
