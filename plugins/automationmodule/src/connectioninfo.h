#ifndef CONNECTIONINFO_H
#define CONNECTIONINFO_H



#include <QObject>
#include <QtDebug>

#include <jsonserializable.h>



class ConnectionInfo:public QObject,public JsonSerializable
{
    Q_OBJECT


public:
    ConnectionInfo();


    ConnectionInfo(int nodeid,QString portid);

    ~ConnectionInfo();
    Q_PROPERTY(int nodeID READ nodeID WRITE setNodeID NOTIFY nodeIDChanged USER("serialize"))
    Q_PROPERTY(QString portID READ portID WRITE setPortID NOTIFY portIDChanged USER("serialize"))
    Q_PROPERTY(bool hidden READ hidden WRITE setHidden NOTIFY hiddenChanged USER("serialize"))

    operator QString() const {
        QString  ret(metaObject()->className());
        ret.append(" :: Target Node:"+QString::number(nodeID())+" :: Target Port:"+portID());
        return ret;
    }


    bool operator==(const ConnectionInfo &a) const
    {
        bool retval=a.nodeID()==nodeID() && a.portID()==portID();
        qDebug()<<"ret1:"<<retval;
        return retval;
    }


    int nodeID() const
    {
        return m_nodeID;
    }
    QString portID() const
    {
        return m_portID;
    }

public slots:
    void setNodeID(int nodeID)
    {
        if (m_nodeID == nodeID)
            return;

        m_nodeID = nodeID;
        emit nodeIDChanged(m_nodeID);
    }
    void setPortID(QString portID)
    {
        if (m_portID == portID)
            return;

        m_portID = portID;
        emit portIDChanged(m_portID);
    }

    void setHidden(bool hidden)
    {
        if (m_hidden == hidden)
            return;

        m_hidden = hidden;
        emit hiddenChanged(m_hidden);
    }

signals:
    void nodeIDChanged(int nodeID);
    void portIDChanged(QString portID);



    // JsonSerializable interface
    void hiddenChanged(bool hidden);

public:
    void Serialize(QJsonObject &json);
    void DeSerialize(QJsonObject &json);
    bool hidden() const
    {
        return m_hidden;
    }

private:
    int m_nodeID=-1;

    QString m_portID="";

    bool m_hidden=false;
};



#endif // CONNECTIONINFO_H
