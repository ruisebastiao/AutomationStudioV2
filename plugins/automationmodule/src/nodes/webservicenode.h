#ifndef WEBSERVICENODE_H
#define WEBSERVICENODE_H

#include "flownode.h"

class WebServiceNode : public FlowNode
{
    Q_OBJECT

public:

    WebServiceNode(  QObject* parent = nullptr );

    Q_PROPERTY(QString serviceUrl READ serviceUrl WRITE setServiceUrl NOTIFY serviceUrlChanged USER("serialize"))

    Q_PROPERTY(QString param1 READ param1 WRITE setParam1 NOTIFY param1Changed)
    Q_PROPERTY(FlowNodePort* param1Port READ param1Port WRITE setParam1Port NOTIFY param1PortChanged USER("serialize"))
    Q_PROPERTY(QString param1Name READ param1Name WRITE setParam1Name NOTIFY param1NameChanged)
    Q_PROPERTY(FlowNodePort* param1NamePort READ param1NamePort WRITE setParam1NamePort NOTIFY param1NamePortChanged USER("serialize"))

    Q_PROPERTY(QString param2 READ param2 WRITE setParam2 NOTIFY param2Changed )
    Q_PROPERTY(FlowNodePort* param2Port READ param2Port WRITE setParam2Port NOTIFY param2PortChanged USER("serialize"))
    Q_PROPERTY(QString param2Name READ param2Name WRITE setParam2Name NOTIFY param2NameChanged)
    Q_PROPERTY(FlowNodePort* param2NamePort READ param2NamePort WRITE setParam2NamePort NOTIFY param2NamePortChanged USER("serialize"))

    Q_PROPERTY(QString formattedUrl READ formattedUrl NOTIFY formattedUrlChanged )

    Q_PROPERTY(QString response READ response WRITE setResponse NOTIFY responseChanged)
    Q_PROPERTY(FlowNodePort* responsePort READ responsePort WRITE setResponsePort NOTIFY responsePortChanged USER("serialize"))


    Q_PROPERTY(bool executing READ executing WRITE setExecuting NOTIFY executingChanged)
    Q_PROPERTY(FlowNodePort* executingPort READ executingPort WRITE setExecutingPort NOTIFY executingPortChanged USER("serialize"))


    // FlowNode interface
public:
    static QQmlComponent *delegate(QQmlEngine &engine);

    void makeRequest();

    QString serviceUrl() const
    {
        return m_serviceUrl;
    }


    QString formattedUrl() const
    {
        return m_formattedUrl;
    }

    QString param1() const
    {
        return m_param1;
    }

    QString param2() const
    {
        return m_param2;
    }

    QString response() const
    {
        return m_response;
    }

    QString param1Name() const
    {
        return m_param1Name;
    }

    QString param2Name() const
    {
        return m_param2Name;
    }

    bool executing() const
    {
        return m_executing;
    }

    FlowNodePort* param1Port() const
    {
        return m_param1Port;
    }

    FlowNodePort* param1NamePort() const
    {
        return m_param1NamePort;
    }

    FlowNodePort* param2Port() const
    {
        return m_param2Port;
    }

    FlowNodePort* param2NamePort() const
    {
        return m_param2NamePort;
    }

public slots:

    void setServiceUrl(QString serviceUrl)
    {
        if (m_serviceUrl == serviceUrl)
            return;

        m_serviceUrl = serviceUrl;
        setFormattedUrl();
        emit serviceUrlChanged(m_serviceUrl);
    }




    void setParam1(QString param1)
    {
        if (param1=="")
            return;

        m_param1 = param1;
        setFormattedUrl();
        emit param1Changed(m_param1);
        makeRequest();
    }

    void setParam2(QString param2)
    {
        if (m_param2 == param2)
            return;

        m_param2 = param2;
        setFormattedUrl();
        emit param2Changed(m_param2);
    }

    void setResponse(QString response)
    {

        m_response = response;
        emit responseChanged(m_response);
    }

    void setParam1Name(QString param1Name)
    {
        if (m_param1Name == param1Name)
            return;

        m_param1Name = param1Name;
        setFormattedUrl();
        emit param1NameChanged(m_param1Name);
    }

    void setParam2Name(QString param2Name)
    {
        if (m_param2Name == param2Name)
            return;

        m_param2Name = param2Name;
        setFormattedUrl();
        emit param2NameChanged(m_param2Name);
    }

    void setExecuting(bool executing)
    {


        m_executing = executing;
        emit executingChanged(m_executing);
    }

    void setParam1Port(FlowNodePort* param1Port)
    {
        if (m_param1Port == param1Port)
            return;

        m_param1Port = param1Port;
        emit param1PortChanged(m_param1Port);
    }

    void setParam1NamePort(FlowNodePort* param1NamePort)
    {
        if (m_param1NamePort == param1NamePort)
            return;

        m_param1NamePort = param1NamePort;
        emit param1NamePortChanged(m_param1NamePort);
    }

    void setParam2Port(FlowNodePort* param2Port)
    {
        if (m_param2Port == param2Port)
            return;

        m_param2Port = param2Port;
        emit param2PortChanged(m_param2Port);
    }

    void setParam2NamePort(FlowNodePort* param2NamePort)
    {
        if (m_param2NamePort == param2NamePort)
            return;

        m_param2NamePort = param2NamePort;
        emit param2NamePortChanged(m_param2NamePort);
    }

    void setResponsePort(FlowNodePort* responsePort)
    {
        if (m_responsePort == responsePort)
            return;

        m_responsePort = responsePort;
        emit responsePortChanged(m_responsePort);
    }

    void setExecutingPort(FlowNodePort* executingPort)
{
    if (m_executingPort == executingPort)
    return;

m_executingPort = executingPort;
emit executingPortChanged(m_executingPort);
}

signals:


    void serviceUrlChanged(QString serviceUrl);



    void formattedUrlChanged(QString formattedUrl);

    void param1Changed(QString param1);

    void param2Changed(QString param2);

    void responseChanged(QString response);

    void param1NameChanged(QString param1Name);

    void param2NameChanged(QString param2Name);

    void executingChanged(bool executing);

    void param1PortChanged(FlowNodePort* param1Port);

    void param1NamePortChanged(FlowNodePort* param1NamePort);

    void param2PortChanged(FlowNodePort* param2Port);

    void param2NamePortChanged(FlowNodePort* param2NamePort);

    void responsePortChanged(FlowNodePort* responsePort);

    void executingPortChanged(FlowNodePort* executingPort);

private:

    void setFormattedUrl()
    {


        m_formattedUrl = "?"+m_param1Name+"="+m_param1+"&"+m_param2Name+"="+m_param2;
        emit formattedUrlChanged(m_formattedUrl);
//        makeRequest();
    }


    QString m_serviceUrl="";

    QString m_formattedUrl="";
    QString m_param1="";
    QString m_param2="";
    QString m_response="";
    QString m_param1Name="";
    QString m_param2Name="";

    QNetworkAccessManager *m_manager=nullptr;

    bool m_executing=false;

    FlowNodePort* m_param1Port=nullptr;

    FlowNodePort* m_param1NamePort=nullptr;

    FlowNodePort* m_param2Port=nullptr;

    FlowNodePort* m_param2NamePort=nullptr;

    FlowNodePort* m_responsePort=nullptr;

    FlowNodePort* m_executingPort=nullptr;

public:
    void Serialize(QJsonObject &json) override;
    void DeSerialize(QJsonObject &json) override;
    FlowNodePort* responsePort() const
    {
        return m_responsePort;
    }
    FlowNodePort* executingPort() const
    {
        return m_executingPort;
    }
};

#endif // WEBSERVICENODE_H
