#include "proxynode.h"

void ProxyNode::setBindedFlowNode(FlowNode *node)
{
    if(!node){
        return;
    }

    //    if(node->id()!=selectedBindedNodeID()){
    setSelectedBindedNodeID(node->id());


    if(configsLoaded()==false){
        return;
    }

    FlowNodePort* outputport=getPortFromKey("output");
    FlowNodePort* inputport=getPortFromKey("input");

    if(!outputport || !inputport){
        return;
    }

    SceneGraph* graph=qobject_cast<SceneGraph*>(this->getGraph());

    if(inputport->getPortItem()->getInEdgeItems().size()>0){

        qan::EdgeItem* edgeitem=inputport->getPortItem()->getInEdgeItems().at(0);
        graph->deleteEdge(edgeitem->getEdge());

        QObject::connect(edgeitem, &qan::EdgeItem::destroyed,[&](QObject* edgeObject){
            if(node){
                qan::Edge* newedge=graph->insertNewEdge(true,node,this);
                FlowNodePort* outPort=node->getPortByID("output");

                if(outPort){
                    graph->bindEdge(newedge,outPort->getPortItem(),inputport->getPortItem());
                }
            }
        });
    }
    else{
        if(node){
            qan::Edge* newedge=graph->insertNewEdge(true,node,this);
            FlowNodePort* outPort=node->getPortByID("output");

            if(outPort){
                graph->bindEdge(newedge,outPort->getPortItem(),inputport->getPortItem());
            }
        }
    }
    //    }
}

ProxyNode::ProxyNode()
{

    m_type=Type::ProxyNode;



    m_flowNodes= new FlowNodeManager(this);


}

QQmlComponent *ProxyNode::delegate(QQmlEngine &engine)
{
    static std::unique_ptr<QQmlComponent>   delegate;
    if ( !delegate )
        delegate = std::make_unique<QQmlComponent>(&engine, "qrc:///Nodes/ProxyNodeItem.qml");
    return delegate.get();
}



void ProxyNode::updateProxyType()
{
    if(configsLoaded()==false)
        return;

    FlowNodePort* outputport=getPortFromKey("output");
    FlowNodePort* inputport=getPortFromKey("input");


    if(!outputport || !inputport){
        return;
    }


    SceneGraph* graph=qobject_cast<SceneGraph*>(this->getGraph());

    if(m_proxyType=="Output"){
        outputport->setHidden(false);

        inputport->setHidden(true);

    }
    else{
        outputport->setHidden(true);

        inputport->setHidden(false);

    }

    if(inputport->getPortItem()->getInEdgeItems().size()>0){
        graph->deleteEdge(inputport->getPortItem()->getInEdgeItems().at(0)->getEdge());
    }
    if(outputport->getPortItem()->getOutEdgeItems().size()>0){
        graph->deleteEdge(outputport->getPortItem()->getOutEdgeItems().at(0)->getEdge());
    }
}

void ProxyNode::initProxyNode()
{
    FlowNodePort* outputport=getPortFromKey("output");
    FlowNodePort* inputport=getPortFromKey("input");


    if(!outputport || !inputport){
        return;
    }



    updateProxyType();

}

void ProxyNode::DeSerialize(QJsonObject &json)
{

    FlowNode::DeSerialize(json);



    initProxyNode();

}


void ProxyNode::initializeNode(int id)
{
    FlowNode::initializeNode(id);

    initProxyNode();




}

