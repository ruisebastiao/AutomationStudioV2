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
    if(!m_inputPort){
        return;
    }

    if(!m_outputPort){
        return;
    }


    SceneGraph* graph=qobject_cast<SceneGraph*>(this->getGraph());

    if(m_proxyType=="Output"){
        m_outputPort->setHidden(false);

        m_inputPort->setHidden(true);

    }
    else{
        m_outputPort->setHidden(true);

        m_inputPort->setHidden(false);

    }

    if(m_inputPort->getPortItem()->getInEdgeItems().size()>0){
        graph->deleteEdge(m_inputPort->getPortItem()->getInEdgeItems().at(0)->getEdge());
    }
    if(m_outputPort->getPortItem()->getOutEdgeItems().size()>0){
        graph->deleteEdge(m_outputPort->getPortItem()->getOutEdgeItems().at(0)->getEdge());
    }
}

void ProxyInputNode::initProxyNode()
{
    if(!m_outputPort){
        return;
    }

    QObject::connect(m_outputPort->getPortItem(), &qan::PortItem::outEdgeAdded, this, [this](qan::EdgeItem& outEdgeItem){

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
    m_outputPort=getPortFromKey("output");
    m_inputPort=getPortFromKey("input");

    updateProxyType();
}

void ProxyInputNodeListModel::onNodeAdded(FlowNode *nodeloaded)
{
    if(m_filterType==nodeloaded->getType()){
        addNode(nodeloaded);

    }
}
