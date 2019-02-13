#include "proxynode.h"

void ProxyNode::setBindedFlowNode(FlowNode *node)
{

    if(node==m_bindedFlowNode){
        return;
    }



    if(node){
        setSelectedBindedNodeID(node->id());
    }


    if(configsLoaded()==false){

        return;
    }

    m_bindedFlowNode=node;

    if(!node){
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
           this->doBindNode();
        });
    }
    else{
       this->doBindNode();
    }
}

void ProxyNode::doBindNode(){
    FlowNodePort* outputport=getPortFromKey("output");
    FlowNodePort* inputport=getPortFromKey("input");

    if(!outputport || !inputport){
        return;
    }

    FlowNode* node=m_bindedFlowNode;
    if(node){
        SceneGraph* graph=qobject_cast<SceneGraph*>(this->getGraph());
        qan::Edge* newedge=graph->insertNewEdge(false,node,this);
        FlowNodePort* outPort=node->getPortByID("output");

        if(outPort){
            graph->bindEdge(newedge,outPort->getPortItem(),inputport->getPortItem());
        }
    }
}


ProxyNode::ProxyNode()
{

    m_type=Type::ProxyNode;



    m_flowNodes= new FlowNodeManager(this);


}

ProxyNode::~ProxyNode()
{
    qDebug()<<"Deleting proxy node";
//    setProxyType("Output");
//    setFlowNodes(nullptr);
//    setParentModule(nullptr);
}

QQmlComponent *ProxyNode::delegate(QQmlEngine &engine)
{
    static UniqueQQmlComponentPtr  delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/ProxyNodeItem.qml"));
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

