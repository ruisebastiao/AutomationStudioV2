#include "webservicenode.h"

WebServiceNode::WebServiceNode(QObject *parent){

    m_type=Type::WebServiceNode;

    m_manager=new QNetworkAccessManager(this);
    connect(m_manager,&QNetworkAccessManager::finished,[=](QNetworkReply* reply){
        //qDebug()<<"Network error:"<<reply->errorString();
    });
    //    connect(m_manager,&QNetworkAccessManager::error,this,&WebServiceNode::handleFinished);



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
    setExecuting(true);
    QNetworkReply* reply = m_manager->get(QNetworkRequest(url));




    connect(reply, &QNetworkReply::readyRead,[=](){
        /* ... */


        QString data=reply->readAll();


        this->setResponse(data);
        setExecuting(false);
        reply->deleteLater();
    });


    connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error),
            [=](QNetworkReply::NetworkError code){
        /* ... */

        setExecuting(false);

        setError(reply->errorString());
        reply->deleteLater();
    });

}

void WebServiceNode::Serialize(QJsonObject &json)
{
    FlowNode::Serialize(json);

}

void WebServiceNode::DeSerialize(QJsonObject &json)
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


    FlowNode::DeSerialize(json);

}
