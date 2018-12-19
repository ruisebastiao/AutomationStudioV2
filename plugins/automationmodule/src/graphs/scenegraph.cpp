#include "scenegraph.h"


#include <nodes/flownode.h>

#include <nodes/barcodereadernode.h>
#include <nodes/modulepropertybind.h>
#include <nodes/multiplexedinputnode.h>
#include <nodes/numericnode.h>
#include <nodes/proxyinputnode.h>
#include <nodes/stringbuildernode.h>
#include <nodes/stringnode.h>
#include <nodes/webservicenode.h>




SceneGraph::SceneGraph(QQuickItem *parent) noexcept : qan::Graph(parent) {


    QObject::connect(this, &qan::Graph::connectorRequestPortEdgeCreation, this, [this](qan::PortItem* src,qan::PortItem* dst){

        if(isEdgeDestinationBindable(*dst)){
            qan::Edge* newedge= this->insertNewEdge(false,src->getNode(),dst->getNode());

            this->bindEdge(newedge,src,dst);
        }
    });

    getCommonTypes();

}


void SceneGraph::getCommonTypes()
{
    QVariantList ret;

    int enumscount=QMetaEnum::fromType<FlowNode::Type>().keyCount();
    for (int i = 0; i < enumscount; ++i) {
        FlowNode::Type nodetype= static_cast<FlowNode::Type>(QMetaEnum::fromType<FlowNode::Type>().value(i));

        QVariantMap map;


        switch (nodetype) {

        case FlowNode::Type::ObjectPropertyNode:
            map.insert(QVariant::fromValue(nodetype).value<QString>(),"Object Property");

            break;

        case FlowNode::Type::BarcodeReaderNode:
            map.insert(QVariant::fromValue(nodetype).value<QString>(),"Barcode Reader");

            break;
        case FlowNode::Type::ProxyInputNode:
            map.insert(QVariant::fromValue(nodetype).value<QString>(),"In/Out Proxy");

            break;

        case FlowNode::Type::StringNode:
            map.insert(QVariant::fromValue(nodetype).value<QString>(),"String");

            break;

        case FlowNode::Type::WebServiceNode:
            map.insert(QVariant::fromValue(nodetype).value<QString>(),"WebService");

            break;

        case FlowNode::Type::NumericNode:
            map.insert(QVariant::fromValue(nodetype).value<QString>(),"Numeric");

            break;

        case FlowNode::Type::ModulePropertyBind:
            map.insert(QVariant::fromValue(nodetype).value<QString>(),"Module Property Bind");
            break;

        case FlowNode::Type::StringBuilderNode:
            map.insert(QVariant::fromValue(nodetype).value<QString>(),"String Builder");

            break;


        default:
            //                static_assert(true, "");
            break;
        }

        if(map.empty()==false)
            ret.append(map);

    }


    m_commonNodeTypes.append(ret);

    emit commonNodeTypesChanged(m_commonNodeTypes);
}


FlowNode *SceneGraph::createNode(QString nodetype)
{
    qan::Node* newnode=nullptr;



    if(nodetype=="BarcodeReaderNode"){
        newnode=insertNode<BarcodeReaderNode>(nullptr);
    }
    if(nodetype=="ModulePropertyBind"){
        newnode=insertNode<ModulePropertyBind>(nullptr);
    }
    else if(nodetype=="WebServiceNode"){
        newnode=insertNode<WebServiceNode>(nullptr);
    }
    else if(nodetype=="StringNode"){
        newnode=insertNode<StringNode>(nullptr);
    }
    else if(nodetype=="ProxyInputNode"){
        newnode=insertNode<ProxyInputNode>(nullptr);
    }
    else if(nodetype=="NumericNode"){
        newnode=insertNode<NumericNode>(nullptr);
    }
    else if(nodetype=="MultiplexedInputNode"){
        newnode=insertNode<MultiplexedInputNode>(nullptr);
    }
    else if(nodetype=="StringBuilderNode"){
        newnode=insertNode<StringBuilderNode>(nullptr);
    }
    FlowNode* newflownode= dynamic_cast<FlowNode*>(newnode);

    emit flowNodeAdded(newflownode);

    return newflownode;
}

void SceneGraph::addNode(QPoint loc, QVariantMap nodeinfo)
{

    LOG_INFO()<<"Adding node:"<<nodeinfo<<" @ "<<loc;

    QString nodeType;
    QMapIterator<QString, QVariant> i(nodeinfo);
    while (i.hasNext()) {
        i.next();
        nodeType=i.key();

    }

    FlowNode* node=createNode(nodeType);


    if(node){
        node->getItem()->setProperty("x",QVariant::fromValue(loc.x()));
        node->getItem()->setProperty("y",QVariant::fromValue(loc.y()));

    }


}

void SceneGraph::deleteEdge(qan::Edge *edge)
{


    if(!edge){
        return;
    }

    auto edgeitem= edge->getItem();

    edgeitem->deleteLater();
    // TODO

    qan::Graph::removeEdge(edge);


    //    edge->deleteLater();//->setItem(nullptr);
    //    edge=nullptr;


}

QPointer<QQuickItem> SceneGraph::createDock(qan::NodeItem::Dock dock, qan::Node &node) noexcept
{
    return createDockFromDelegate(dock,node);
}

void SceneGraph::onConnectorRequestEdgeCreation(qan::Node *src, QObject *dst)
{
    if(src!=nullptr){

        qan::Node* destnode=static_cast<qan::Node*>(dst);
        if(dst!=nullptr){

            insertNewEdge(false,src,destnode);
        }
    }
}

qan::Edge *SceneGraph::insertNewEdge(bool hidden, qan::Node *source, qan::Node *destination)
{

    // PRECONDITION;
    // source and destination can't be nullptr
    if ( source == nullptr ||
         destination == nullptr )
        return nullptr;
    qan::Edge* edgeinserted=nullptr;
    //    if(hidden){
    //        edgeinserted=Graph::insertNonVisualEdge<SelectableEdge>(*source, destination);

    //    }
    //    else{
    edgeinserted=Graph::insertEdge<SelectableEdge>(*source, destination);

    //    }

    if(hidden){
        //        edgeinserted->h
        SelectableEdge* selectableedge=qobject_cast<SelectableEdge*>(edgeinserted);
        if(selectableedge){
            selectableedge->setIsHidden(hidden);
        }
    }
    return edgeinserted;

}


void SceneGraph::bindEdgeDestination(qan::Edge &edge, qan::PortItem &inPort) noexcept
{
    qan::Graph::bindEdgeDestination(edge,inPort);

}


void SceneGraph::bindEdge(qan::Edge *edge, qan::PortItem *outPort, qan::PortItem *inPort) noexcept
{
    qan::Graph::bindEdge(edge,outPort,inPort);



}
