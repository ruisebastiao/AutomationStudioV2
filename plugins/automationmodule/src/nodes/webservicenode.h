#ifndef WEBSERVICENODE_H
#define WEBSERVICENODE_H

#include "flownode.h"

class WebServiceNode : public FlowNode
{
    Q_OBJECT

public:

    WebServiceNode(  QObject* parent = nullptr );

    Q_PROPERTY(QString serviceUrl READ serviceUrl WRITE setServiceUrl NOTIFY serviceUrlChanged USER("serialize"))

    Q_PROPERTY(QString param1 READ param1 WRITE setParam1 NOTIFY param1Changed REVISION 30)

    Q_PROPERTY(QString param1Name READ param1Name WRITE setParam1Name NOTIFY param1NameChanged REVISION 30)


    Q_PROPERTY(QString param2 READ param2 WRITE setParam2 NOTIFY param2Changed REVISION 30)

    Q_PROPERTY(QString param2Name READ param2Name WRITE setParam2Name NOTIFY param2NameChanged REVISION 30)


    Q_PROPERTY(QString formattedUrl READ formattedUrl NOTIFY formattedUrlChanged )

    Q_PROPERTY(QString response READ response WRITE setResponse NOTIFY responseChanged REVISION 31)



    Q_PROPERTY(bool executing READ executing WRITE setExecuting NOTIFY executingChanged REVISION 31)



    Q_PROPERTY(QString error READ error WRITE setError NOTIFY errorChanged REVISION 31)



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



    void setError(QString error)
    {

        m_error = error;
        emit errorChanged(m_error);
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



    void errorChanged(QString error);

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
    QTimer* m_replytimer;

    QNetworkAccessManager *m_manager=nullptr;

    bool m_executing=false;



    QString m_error="";

    FlowNodePort* m_errorPort=nullptr;

public:
    void Serialize(QJsonObject &json) override;
    void DeSerialize(QJsonObject &json) override;


    // FlowNode interface
public:

    QString error() const
    {
        return m_error;
    }
};

#endif // WEBSERVICENODE_H
