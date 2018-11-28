#include "flownodeport.h"

#include "../nodes/flownodemanager.h"
#include "../qautomationmodule.h"

#include "src/nodes/flownode.h"


FlowNodePort::FlowNodePort(FlowNode *node, qan::PortItem::Type type, QString portID)
{

    m_node=node;

    if(node->getGraph()==nullptr){
        LOG_INFO("Node graph node set");
        return;
    }

    switch (type) {
    case qan::PortItem::Type::In:{

        m_port= m_node->getGraph()->insertPort(m_node,qan::NodeItem::Dock::Left, qan::PortItem::Type::In);

        m_port->setMultiplicity(qan::PortItem::Multiplicity::Single);
        break;
    }
    case qan::PortItem::Type::Out:
        m_port= m_node->getGraph()->insertPort(m_node,qan::NodeItem::Dock::Right, qan::PortItem::Type::Out);


        break;

    }


    m_port->setId(portID);
    m_port->setLabel(portID);

    setPortLabel(portID);
    m_port->setDraggable(true);
    m_scenegraph= qobject_cast<SceneGraph*>(m_port->getNode()->getGraph());


    QObject::connect(m_port, &qan::PortItem::inEdgeAdded, this, [this](qan::EdgeItem& inEdgeItem){

        QObject::connect(&inEdgeItem, &qan::EdgeItem::destroyed, this, [this](QObject* edgeObject){
            LOG_INFO("In edge destroyed");
            qan::EdgeItem* edgeItem=qobject_cast<qan::EdgeItem*>(edgeObject);
            if(edgeItem!=nullptr){

                m_port->getInEdgeItems().removeAll(edgeItem);

            }
        });
    });

    QObject::connect(m_port, &qan::PortItem::outEdgeAdded, this, [this](qan::EdgeItem& outEdgeItem){

        if(!m_deserialized){
            return;
        }

        QObject::connect(&outEdgeItem, &qan::EdgeItem::destroyed, this, [this](QObject* edgeObject){
            LOG_INFO("Out edge destroyed");
            qan::EdgeItem* edgeItem=qobject_cast<qan::EdgeItem*>(edgeObject);
            if(edgeItem!=nullptr){
                FlowNode* targetNode=getNodeFromEdge(edgeItem);

                if(targetNode){

                    qan::PortItem* targetPortItem=qobject_cast<qan::PortItem*>(edgeItem->getDestinationItem());

                    ////TODO
//                    ConnectionInfo* connectioninfo=as::Utilities::find<ConnectionInfo>(m_connections,"nodeID",QVariant::fromValue(targetNode->id()));

                    ConnectionInfo ci(targetNode->id(),targetPortItem->getId());
                    auto connection_finded=std::find_if(m_connections.begin(), m_connections.end(),
                                     [&](ConnectionInfo* e) { return (e->nodeID() == targetNode->id() && e->portID()==targetPortItem->getId()); });


                    if(connection_finded == m_connections.end()){
                        // finded
                        return;
                    }

                    ConnectionInfo* connectioninfo=*(connection_finded);


                    if(connectioninfo){
                        m_connections.removeOne(connectioninfo);

                        FlowNode* destination=qobject_cast<FlowNode*>(edgeItem->getDestinationItem()->getNode());

//                        destination->unbindSourceProperty(connectioninfo->portID());

                    }

                }


                m_port->getOutEdgeItems().removeAll(edgeItem);

            }
        });


        FlowNode* targetNode=getNodeFromEdge(&outEdgeItem);
        qan::PortItem* targetPortItem=qobject_cast<qan::PortItem*>(outEdgeItem.getDestinationItem());

        if(targetNode!=nullptr){

//            targetNode->bindSourceProperty(m_node,m_port->getId(),targetPortItem->getId());

            int targetid=targetNode->id();



            ConnectionInfo ci(targetid,targetPortItem->getId());
            auto connection_finded=std::find_if(m_connections.begin(), m_connections.end(),
                             [&](ConnectionInfo* e) { return (e->nodeID() == targetid && e->portID()==targetPortItem->getId()); });


            if(connection_finded != m_connections.end()){
                // finded
                return;
            }

            ConnectionInfo* connectioninfo= new ConnectionInfo();


            connectioninfo->setNodeID(targetNode->id());
            connectioninfo->setPortID(targetPortItem->getId());

            m_connections.append(connectioninfo);



        }


    });



}

void FlowNodePort::setShowinlabel(bool showinlabel)
{
    if (m_showinlabel == showinlabel)
        return;

    m_showinlabel = showinlabel;
    if(m_showinlabel){
//        m_node->bindPortLabelToProperty(m_port,m_port->getId());
    }
    emit showinlabelChanged(m_showinlabel);

}

void FlowNodePort::setHidden(bool hidden)
{
    if (m_hidden == hidden)
        return;

    m_hidden = hidden;

    emit hiddenChanged(m_hidden);
    bool visible=m_hidden==false;
    m_port->setVisible(visible);

}

QList<ConnectionInfo *> FlowNodePort::getConnections() const
{
    return m_connections;
}



FlowNode* FlowNodePort::getNodeFromEdge(qan::EdgeItem* edgeitem){
    qan::PortItem* targetPort=qobject_cast<qan::PortItem*>(edgeitem->getDestinationItem());

    if(targetPort!=nullptr && targetPort->getNode()!=nullptr){


        return qobject_cast<FlowNode*>(targetPort->getNode());

    }

    return nullptr;

}



void FlowNodePort::Serialize(QJsonObject &json)
{
    JsonSerializable::Serialize(json,this);

    if(m_port->getType()==qan::PortItem::Type::Out){
        QJsonArray connectedToArrayObject;
        foreach (ConnectionInfo* connection, m_connections) {
            QJsonObject connectedToObject;
            connection->Serialize(connectedToObject);
            connectedToArrayObject.append(connectedToObject);
        }

        json["connectedTo"]=connectedToArrayObject;
    }

    QJsonObject portItemObject;
    portItemObject["x"]=m_port->x();
    portItemObject["y"]=m_port->y();

    json["portItem"]=portItemObject;

}

void FlowNodePort::DeSerialize(QJsonObject &json)
{
    JsonSerializable::DeSerialize(json,this);

    if(!m_port){
        LOG_INFO("Port invalid check configs");
        return;
    }


    QJsonArray connectedToArray = json["connectedTo"].toArray();

    for (int i = 0; i < connectedToArray.count(); ++i) {

        QJsonObject connectedToObject=connectedToArray[i].toObject();
        ConnectionInfo* connection= new ConnectionInfo();
        connection->DeSerialize(connectedToObject);
        m_connections.append(connection);
    }

    m_deserialized=true;

    QJsonObject portItemObject=json["portItem"].toObject();

    //    qDebug()<<"YYYY:"<<portItemObject["y"].toDouble();

    this->m_port->setProperty("x",QVariant::fromValue(portItemObject["x"].toDouble()));
    this->m_port->setProperty("yPosition",QVariant::fromValue(portItemObject["y"].toDouble()));


    //    QTimer* teste = new QTimer();

    //    teste->setInterval(10000);

    //    teste->setSingleShot(true);
    //    connect(teste,&QTimer::timeout,this,[this,portItemObject](){
    //        this->m_port->setProperty("x",QVariant::fromValue(portItemObject["x"].toDouble()));
    //        this->m_port->setProperty("y",QVariant::fromValue(portItemObject["y"].toDouble()));

    //    });

    //    teste->start();

}



qan::PortItem *FlowNodePort::getPortItem()
{
    return m_port;
}

