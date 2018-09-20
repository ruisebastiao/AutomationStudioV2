#include "webservicenode.h"

WebServiceNode::WebServiceNode(QObject *parent){

    m_type=Type::WebServiceNode;

    m_manager=new QNetworkAccessManager(this);
    connect(m_manager,&QNetworkAccessManager::finished,[=](QNetworkReply *reply) {
        QString err = reply->errorString();//this err will be reported
        QString strReply = (QString)reply->readAll();
        setResponse(strReply);

        setExecuting(false);
    });


}





QQmlComponent *WebServiceNode::delegate(QQmlEngine &engine)
{
    static std::unique_ptr<QQmlComponent>   delegate;
    if ( !delegate )
        delegate = std::make_unique<QQmlComponent>(&engine, "qrc:///Nodes/WebServiceNodeItem.qml");
    return delegate.get();
}

void WebServiceNode::makeRequest()
{
    QUrl url(m_serviceUrl+m_formattedUrl);
    setExecuting(true);
    QNetworkReply* reply = m_manager->get(QNetworkRequest(url));

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

    m_outPorts.append(m_responsePort);
    m_outPorts.append(m_executingPort);


    FlowNode::DeSerialize(json);

}
