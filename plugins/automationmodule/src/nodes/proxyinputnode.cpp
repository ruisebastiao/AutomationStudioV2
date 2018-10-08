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

void ProxyInputNode::DeSerialize(QJsonObject &json)
{
    m_inputPort=new FlowNodePort(this,qan::PortItem::Type::In,"input");

    m_inPorts.append(m_inputPort);

    m_outputPort=new FlowNodePort(this,qan::PortItem::Type::Out,"output");
    m_outPorts.append(m_outputPort);


    FlowNode::DeSerialize(json);


    foreach (FlowNode* node, QAutomationModule::flownodemanager->flownodes()) {
        if(node->getType()==FlowNode::Type::ProxyInputNode){

            if(node->id()!=this->id()){
                m_proxyNodes->addNode(node);
            }

        }
    }


    QObject::connect(m_outputPort->getPortItem(), &qan::PortItem::outEdgeAdded, this, [this](qan::EdgeItem& outEdgeItem){



        auto proxynode=qobject_cast<ProxyInputNode*>(outEdgeItem.getEdge()->getDestination());
        if(proxynode){

            proxynode->setSelectedBindedNode(this);
        }




    });



    setConfigsLoaded(true);
    // updatePorts();


}

void ProxyInputNodeListModel::onNodeAdded(FlowNode *nodeloaded)
{
    if(m_filterType==nodeloaded->getType()){
        addNode(nodeloaded);

    }
}
