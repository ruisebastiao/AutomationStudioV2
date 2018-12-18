#ifndef WEBSERVICENODE_H
#define WEBSERVICENODE_H

#include "flownode.h"

class WebServiceNode : public FlowNode
{
    Q_OBJECT

public:

    WebServiceNode(  QObject* parent = nullptr );

    Q_PROPERTY(QString serviceUrl READ serviceUrl WRITE setServiceUrl NOTIFY serviceUrlChanged USER("serialize"))



    Q_PROPERTY(QString formattedUrl READ formattedUrl NOTIFY formattedUrlChanged )

    Q_PROPERTY(QVariant query READ query WRITE setQuery NOTIFY queryChanged REVISION 30)

    Q_PROPERTY(QVariant response READ response WRITE setResponse NOTIFY responseChanged REVISION 31)

    Q_PROPERTY(QVariant executing READ executing WRITE setExecuting NOTIFY executingChanged REVISION 31)


    Q_PROPERTY(QVariant error READ error WRITE setError NOTIFY errorChanged REVISION 31)



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


    QVariant  response() const
    {
        return m_response;
    }



    QVariant  executing() const
    {
        return m_executing;
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





    void setResponse(QVariant response)
    {

        m_response = response;
        emit responseChanged(m_response);
    }

    void setExecuting(QVariant executing)
    {


        m_executing = executing;
        emit executingChanged(m_executing);
    }



    void setError(QVariant error)
    {

        m_error = error;
        emit errorChanged(m_error);
    }



    void setQuery(QVariant query)
    {
        m_query = query;
        setFormattedUrl();
        emit queryChanged(m_query);
    }

signals:


    void serviceUrlChanged(QString serviceUrl);



    void formattedUrlChanged(QString formattedUrl);

    void param1Changed(QVariant  param1);

    void param2Changed(QVariant  param2);

    void responseChanged(QVariant  response);

    void param1NameChanged(QVariant  param1Name);

    void param2NameChanged(QVariant  param2Name);

    void executingChanged(QVariant  executing);



    void errorChanged(QVariant  error);

    void queryChanged(QVariant query);

private:

    void setFormattedUrl()
    {


        m_formattedUrl = m_serviceUrl+"?"+m_query.value<QString>();
        emit formattedUrlChanged(m_formattedUrl);
        if(configsLoaded()){
            makeRequest();
        }
    }


    QString m_serviceUrl="";
    QString m_formattedUrl="";
    QVariant m_response=QVariant::fromValue(QString());

    QTimer* m_replytimer;

    QNetworkAccessManager *m_manager=nullptr;

    QVariant m_executing=QVariant::fromValue(false);



    QVariant m_error=QVariant::fromValue(QString());

    FlowNodePort* m_errorPort=nullptr;

    QVariant m_query=QVariant::fromValue(QString());

public:
    void Serialize(QJsonObject &json) override;
    void DeSerialize(QJsonObject &json) override;


    // FlowNode interface
public:

    QVariant  error() const
    {
        return m_error;
    }
    QVariant query() const
    {
        return m_query;
    }
};

#endif // WEBSERVICENODE_H
