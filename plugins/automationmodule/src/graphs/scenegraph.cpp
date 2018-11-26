#include "scenegraph.h"


#include <src/nodes/flownode.h>



void SceneGraph::deleteEdge(qan::Edge *edge)
{
    //FlowNode* sourcenode=qobject_cast<FlowNode*>(edge->getSource());


    if(!edge){
        return;
    }

    edge->getItem()->deleteLater();

    // TODO
    //sourcenode->deletePortConnection(edge);

    qan::Graph::removeEdge(edge);



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
