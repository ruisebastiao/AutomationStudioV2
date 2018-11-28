#ifndef WEBSERVICENODE_H
#define WEBSERVICENODE_H

#include "flownode.h"

class WebServiceNode : public FlowNode
{
    Q_OBJECT

public:

    WebServiceNode(  QObject* parent = nullptr );

    Q_PROPERTY(QString serviceUrl READ serviceUrl WRITE setServiceUrl NOTIFY serviceUrlChanged USER("serialize"))

    Q_PROPERTY(QVariant  param1 READ param1 WRITE setParam1 NOTIFY param1Changed REVISION 30)

    Q_PROPERTY(QVariant  param1Name READ param1Name WRITE setParam1Name NOTIFY param1NameChanged REVISION 30)


    Q_PROPERTY(QVariant  param2 READ param2 WRITE setParam2 NOTIFY param2Changed REVISION 30)

    Q_PROPERTY(QVariant  param2Name READ param2Name WRITE setParam2Name NOTIFY param2NameChanged REVISION 30)


    Q_PROPERTY(QString formattedUrl READ formattedUrl NOTIFY formattedUrlChanged )

    Q_PROPERTY(QVariant  response READ response WRITE setResponse NOTIFY responseChanged REVISION 31)



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

    QVariant  param1() const
    {
        return m_param1;
    }

    QVariant  param2() const
    {
        return m_param2;
    }

    QVariant  response() const
    {
        return m_response;
    }

    QVariant  param1Name() const
    {
        return m_param1Name;
    }

    QVariant  param2Name() const
    {
        return m_param2Name;
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




    void setParam1(QVariant  param1)
    {
        if (param1.value<QString>()=="")
            return;

        m_param1 = param1;
        setFormattedUrl();
        emit param1Changed(m_param1);
        makeRequest();
    }

    void setParam2(QVariant param2)
    {
        if (m_param2 == param2)
            return;

        m_param2 = param2;
        setFormattedUrl();
        emit param2Changed(m_param2);
    }

    void setResponse(QVariant response)
    {

        m_response = response;
        emit responseChanged(m_response);
    }

    void setParam1Name(QVariant param1Name)
    {
        if (m_param1Name == param1Name)
            return;

        m_param1Name = param1Name;
        setFormattedUrl();
        emit param1NameChanged(m_param1Name);
    }

    void setParam2Name(QVariant param2Name)
    {
        if (m_param2Name == param2Name)
            return;

        m_param2Name = param2Name;
        setFormattedUrl();
        emit param2NameChanged(m_param2Name);
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

private:

    void setFormattedUrl()
    {


        m_formattedUrl = "?"+m_param1Name.value<QString>()+"="+m_param1.value<QString>()+"&"+m_param2Name.value<QString>()+"="+m_param2.value<QString>();
        emit formattedUrlChanged(m_formattedUrl);
        //        makeRequest();
    }


    QString m_serviceUrl="";
    QString m_formattedUrl="";

    QVariant m_param1=QVariant::fromValue(QString());
    QVariant m_param2=QVariant::fromValue(QString());
    QVariant m_response=QVariant::fromValue(QString());
    QVariant m_param1Name=QVariant::fromValue(QString());
    QVariant m_param2Name=QVariant::fromValue(QString());
    QTimer* m_replytimer;

    QNetworkAccessManager *m_manager=nullptr;

    QVariant m_executing=QVariant::fromValue(false);



    QVariant m_error=QVariant::fromValue(QString());

    FlowNodePort* m_errorPort=nullptr;

public:
    void Serialize(QJsonObject &json) override;
    void DeSerialize(QJsonObject &json) override;


    // FlowNode interface
public:

    QVariant  error() const
    {
        return m_error;
    }
};

#endif // WEBSERVICENODE_H
