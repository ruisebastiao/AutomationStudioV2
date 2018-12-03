#include "proxyinputnode.h"

ProxyInputNode::ProxyInputNode()
{

    m_type=Type::ProxyInputNode;






    m_proxyNodes= new ProxyInputNodeListModel();
}

QQmlComponent *ProxyInputNode::delegate(QQmlEngine &engine)
{
    static std::unique_ptr<QQmlComponent>   delegate;
    if ( !delegate )
        delegate = std::make_unique<QQmlComponent>(&engine, "qrc:///Nodes/ProxyInputNodeItem.qml");
    return delegate.get();
}



void ProxyInputNode::updateProxyType()
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

void ProxyInputNode::initProxyNode()
{
    FlowNodePort* outputport=getPortFromKey("output");
    FlowNodePort* inputport=getPortFromKey("input");


    if(!outputport || !inputport){
        return;
    }


    QObject::connect(outputport->getPortItem(), &qan::PortItem::outEdgeAdded, this, [this](qan::EdgeItem& outEdgeItem){

        auto proxynode=qobject_cast<ProxyInputNode*>(outEdgeItem.getEdge()->getDestination());
        if(proxynode){

            proxynode->setSelectedBindedNode(this);
        }

    });

}

void ProxyInputNode::DeSerialize(QJsonObject &json)
{

    FlowNode::DeSerialize(json);


    foreach (FlowNode* node, QAutomationModule::flownodemanager->flownodes()) {
        if(node->getType()==FlowNode::Type::ProxyInputNode){

            if(node->id()!=this->id()){
                m_proxyNodes->addNode(node);
            }

        }
    }




    initProxyNode();



    //    setConfigsLoaded(true);
    // updatePorts();


}

void ProxyInputNode::initializePorts(QJsonObject &json)
{
    FlowNode::initializePorts(json);


    updateProxyType();
}

void ProxyInputNode::initializeNode()
{
    initProxyNode();
    QJsonObject jo;
    initializePorts(jo);
    foreach (FlowNode* node, QAutomationModule::flownodemanager->flownodes()) {
        if(node->getType()==FlowNode::Type::ProxyInputNode){

            if(node->id()!=this->id()){
                m_proxyNodes->addNode(node);
            }

        }
    }

}

void ProxyInputNodeListModel::onNodeAdded(FlowNode *nodeloaded)
{
    if(m_filterType==nodeloaded->getType()){
        addNode(nodeloaded);

    }
}
