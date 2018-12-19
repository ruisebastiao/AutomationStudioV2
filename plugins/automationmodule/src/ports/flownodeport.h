#ifndef FLOWNODEPORT_H
#define FLOWNODEPORT_H

#include <cutelogger/Logger.h>

#include <connectioninfo.h>
#include <QObject>
#include <flownode.h>
#include <jsonserializable.h>
#include <utilities.h>

#include <qanGraph.h>

class AUTOMATIONMODULE_EXPORT FlowNode;

class SceneGraph;

class AUTOMATIONMODULE_EXPORT FlowNodePort:public QObject,public JsonSerializable
{
    Q_OBJECT

    Q_INTERFACES(JsonSerializable)

public:

    FlowNodePort(FlowNode* node, qan::PortItem::Type type,QString portID,bool initialize=false);

    Q_PROPERTY(QString portLabel READ portLabel WRITE setPortLabel NOTIFY portLabelChanged USER("serialize"))

    Q_PROPERTY(bool showinlabel READ showinlabel WRITE setShowinlabel NOTIFY showinlabelChanged USER("serialize"))
    Q_PROPERTY(bool hidden READ hidden WRITE setHidden NOTIFY hiddenChanged USER("serialize"))

    Q_PROPERTY(qan::PortItem::Type type READ getType CONSTANT FINAL USER("serialize"))


private:

    QMetaObject::Connection m_edgeConnection;
    QMetaMethod m_edgeSlot;

public slots:






    void setPortLabel(QString portLabel)
    {
        if (m_portLabel == portLabel)
            return;

        m_portLabel = portLabel;
        m_port->setLabel(m_portLabel);


        emit portLabelChanged(m_portLabel);
    }



    void setShowinlabel(bool showinlabel);

    void setHidden(bool hidden);

signals:

    void portIDChanged(QString portID);

    void portLabelChanged(QString portLabel);


    void showinlabelChanged(bool showinlabel);

    void hiddenChanged(bool hidden);

private:

    SceneGraph* m_scenegraph= nullptr;

    FlowNode* m_node=nullptr;

    qan::PortItem* m_port=nullptr;

    QList<ConnectionInfo*> m_connections;


    QString m_portLabel="";

    bool m_showinlabel=false;

    bool m_hidden=false;

    FlowNode *getNodeFromEdge(qan::EdgeItem *edgeitem);

public:

    void Serialize(QJsonObject &json) override;
    void DeSerialize(QJsonObject &json) override;

    qan::PortItem* getPortItem();



    // JsonSerializable interface
public:



    QString portLabel() const
    {
        return m_portLabel;
    }
    bool showinlabel() const
    {
        return m_showinlabel;
    }
    bool hidden() const
    {
        return m_hidden;
    }
    qan::PortItem::Type  getType() const
    {
        if(!m_port){
            return  qan::PortItem::Type::In;
        }

        return  m_port->getType();
    }
    QList<ConnectionInfo *> getConnections() const;
};




#endif // INPUTPORT_H
