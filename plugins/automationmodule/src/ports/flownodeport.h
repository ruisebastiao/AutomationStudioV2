#ifndef FLOWNODEPORT_H
#define FLOWNODEPORT_H

#include <Logger.h>

#include <connectioninfo.h>
#include <scenegraph.h>

#include <QObject>
#include <automationstudiocore/jsonserializable.h>
#include <automationstudiocore/utilities.h>

class FlowNode;

class AUTOMATIONMODULE_EXPORT FlowNodePort:public QObject,public JsonSerializable
{
    Q_OBJECT

    Q_INTERFACES(JsonSerializable)

public:

    FlowNodePort(FlowNode* node, qan::PortItem::Type type,QString portID);

    Q_PROPERTY(QString portLabel READ portLabel WRITE setPortLabel NOTIFY portLabelChanged USER("serialize"))

    Q_PROPERTY(bool showinlabel READ showinlabel WRITE setShowinlabel NOTIFY showinlabelChanged USER("serialize"))
    Q_PROPERTY(bool hidden READ hidden WRITE setHidden NOTIFY hiddenChanged USER("serialize"))

    Q_PROPERTY(qan::PortItem::Type type READ getType CONSTANT FINAL USER("serialize"))


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


    FlowNode* m_node=nullptr;

    qan::PortItem* m_port=nullptr;

    QList<ConnectionInfo*> m_connections;


    QString m_portLabel="No label";

    bool m_showinlabel=false;

    bool m_hidden=false;

    FlowNode *getNodeFromEdge(qan::EdgeItem *edgeitem);
    void CheckForNodeConnections(ConnectionInfo *connection);
public:

    void Serialize(QJsonObject &json) override;
    void DeSerialize(QJsonObject &json) override;

    qan::PortItem* getPortItem();


    void createConnections(QList<FlowNode *> &nodes);


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
};




#endif // INPUTPORT_H
