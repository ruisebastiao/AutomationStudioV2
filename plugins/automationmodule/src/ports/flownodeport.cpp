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

        QObject::connect(&outEdgeItem, &qan::EdgeItem::destroyed, this, [this](QObject* edgeObject){
            LOG_INFO("Out edge destroyed");
            qan::EdgeItem* edgeItem=qobject_cast<qan::EdgeItem*>(edgeObject);
            if(edgeItem!=nullptr){
                FlowNode* targetNode=getNodeFromEdge(edgeItem);

                if(targetNode){
                    ConnectionInfo* connectioninfo=Utilities::find<ConnectionInfo>(m_connections,"nodeID",QVariant::fromValue(targetNode->id()));

                    if(connectioninfo){
                        m_connections.removeOne(connectioninfo);

                        FlowNode* destination=qobject_cast<FlowNode*>(edgeItem->getDestinationItem()->getNode());

                        destination->unbindSourceProperty(connectioninfo->portID());

                    }

                }


                m_port->getOutEdgeItems().removeAll(edgeItem);

            }
        });


        FlowNode* targetNode=getNodeFromEdge(&outEdgeItem);
        qan::PortItem* targetPortItem=qobject_cast<qan::PortItem*>(outEdgeItem.getDestinationItem());

        if(targetNode!=nullptr){
            targetNode->bindSourceProperty(m_node,m_port->getId(),targetPortItem->getId());
            int targetid=targetNode->id();
            ConnectionInfo* connectioninfo=Utilities::find<ConnectionInfo>(m_connections,"nodeID",QVariant::fromValue(targetid));

            if(connectioninfo){
                if(connectioninfo->portID()==targetPortItem->getId()){
                    return;
                }
            }

            connectioninfo= new ConnectionInfo();


            connectioninfo->setNodeID(targetNode->id());
            connectioninfo->setPortID(targetPortItem->getId());

            m_connections.append(connectioninfo);



        }


    });

//    QObject::connect(QAutomationModule::flownodemanager, &FlowNodeManager::onFlowNodeLoaded,[this](FlowNode* nodeLoaded){

//        qDebug()<<"On node added :"<<this->m_node->id();

//        int nodeid=m_node->id();

//        if(nodeLoaded->id()!=nodeid){

//            for (int i = 0; i < m_connections.length(); ++i) {

//                ConnectionInfo* connection=m_connections.at(i);
//                if(nodeLoaded->id()==connection->nodeID()){
//                    SceneGraph* scenegraph= qobject_cast<SceneGraph*>(m_port->getNode()->getGraph());

//                    qan::Edge* newedge= scenegraph->insertNewEdge(false,m_node,nodeLoaded);


//                    FlowNodePort* targetFlowNodePort=nodeLoaded->getPortByName(connection->portID());

//                    if(targetFlowNodePort){
//                        scenegraph->bindEdge(newedge,m_port,targetFlowNodePort->getPortItem());
//                    }
//                }

//            }
//        }
//        else{
//            for (int i = 0; i < m_connections.length(); ++i) {

//                ConnectionInfo* connection=m_connections.at(i);
//                auto findednode=QAutomationModule::flownodemanager->getByID(connection->nodeID());
//                if(findednode){
//                    FlowNodePort* nodeport = findednode->getPortByName(connection->portID());
//                    if(nodeport){
//                        qan::PortItem* portitem=nodeport->getPortItem();
//                        if(portitem){

//                            //if(portitem->getInEdgeItems().size()==0){
//                                SceneGraph* scenegraph= qobject_cast<SceneGraph*>(m_port->getNode()->getGraph());

//                                qan::Edge* newedge= scenegraph->insertNewEdge(false,m_node,findednode);

//                                scenegraph->bindEdge(newedge,m_port,nodeport->getPortItem());

//                            //}
//                        }
//                    }
//                }

//            }
//        }
//    });




}

void FlowNodePort::setShowinlabel(bool showinlabel)
{
    if (m_showinlabel == showinlabel)
        return;

    m_showinlabel = showinlabel;
    if(m_showinlabel){
        m_node->bindPortLabelToProperty(m_port,m_port->getId());
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


}


void FlowNodePort::CheckForNodeConnections(ConnectionInfo* connection){

}

qan::PortItem *FlowNodePort::getPortItem()
{
    return m_port;
}

