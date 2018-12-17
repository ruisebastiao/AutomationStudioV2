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
    emit flowNodeAdded(node);

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
