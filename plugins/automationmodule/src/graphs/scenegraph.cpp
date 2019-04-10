#include "scenegraph.h"


#include <nodes/flownode.h>

#include <nodes/barcodereadernode.h>
#include <nodes/logicnode.h>
#include <nodes/modulepropertybind.h>
#include <nodes/multiplexedinputnode.h>
#include <nodes/numericnode.h>
#include <nodes/proxynode.h>
#include <nodes/moduleproxynode.h>
#include <nodes/stringbuildernode.h>
#include <nodes/stringnode.h>
#include <nodes/webservicenode.h>
#include <nodes/projectnode.h>
#include <nodes/serialionode.h>
#include <nodes/commandsendernode.h>
#include <nodes/commandparsernode.h>
#include <nodes/setresetnode.h>
#include <nodes/propertiesnode.h>
#include <nodes/arraynode.h>
#include <nodes/processnode.h>




SceneGraph::SceneGraph(QQuickItem *parent) noexcept : qan::Graph(parent) {


    QObject::connect(this, &qan::Graph::connectorRequestPortEdgeCreation, this, [this](qan::PortItem* src,qan::PortItem* dst){

        bool targetIsProxy=false;
        if(dynamic_cast<ProxyNode*>(dst->getNode())){
            targetIsProxy=true;
        }

        bool sourceIsProxy=false;
        if(dynamic_cast<ProxyNode*>(src->getNode())){
            sourceIsProxy=true;
        }

        if(targetIsProxy && sourceIsProxy){
            return ;
        }


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
        case FlowNode::Type::ProxyNode:
            map.insert(QVariant::fromValue(nodetype).value<QString>(),"Node Proxy");

            break;

        case FlowNode::Type::ModuleProxyNode:
            map.insert(QVariant::fromValue(nodetype).value<QString>(),"Module Node Proxy");

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


        case FlowNode::Type::MultiplexedInputNode:
            map.insert(QVariant::fromValue(nodetype).value<QString>(),"Multiplexed input");

            break;

        case FlowNode::Type::LogicNode:
            map.insert(QVariant::fromValue(nodetype).value<QString>(),"Logic");

            break;

        case FlowNode::Type::ProjectNode:
            map.insert(QVariant::fromValue(nodetype).value<QString>(),"Project");

            break;
        case FlowNode::Type::SerialIONode:
            map.insert(QVariant::fromValue(nodetype).value<QString>(),"Serial IO");

            break;

        case FlowNode::Type::CommandSenderNode:
            map.insert(QVariant::fromValue(nodetype).value<QString>(),"Command Sender");

            break;

        case FlowNode::Type::CommandParserNode:
            map.insert(QVariant::fromValue(nodetype).value<QString>(),"Command Parser");

            break;


        case FlowNode::Type::SetResetNode:
            map.insert(QVariant::fromValue(nodetype).value<QString>(),"Set/Reset");

            break;

        case FlowNode::Type::PropertiesNode:
            map.insert(QVariant::fromValue(nodetype).value<QString>(),"Properties");

            break;
        case FlowNode::Type::ArrayNode:
            map.insert(QVariant::fromValue(nodetype).value<QString>(),"Array operations");

            break;
        case FlowNode::Type::ProcessNode:
            map.insert(QVariant::fromValue(nodetype).value<QString>(),"Process");

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
    else if(nodetype=="ProxyNode"){
        newnode=insertNode<ProxyNode>(nullptr);
    }
    else if(nodetype=="ModuleProxyNode"){
        newnode=insertNode<ModuleProxyNode>(nullptr);
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
    else if(nodetype=="LogicNode"){
        newnode=insertNode<LogicNode>(nullptr);
    }
    else if(nodetype=="ProjectNode"){
        newnode=insertNode<ProjectNode>(nullptr);
    }
    else if(nodetype=="SerialIONode"){
        newnode=insertNode<SerialIONode>(nullptr);
    }
    else if(nodetype=="CommandSenderNode"){
        newnode=insertNode<CommandSenderNode>(nullptr);
    }
    else if(nodetype=="CommandParserNode"){
        newnode=insertNode<CommandParserNode>(nullptr);
    }
    else if(nodetype=="SetResetNode"){
        newnode=insertNode<SetResetNode>(nullptr);
    }
    else if(nodetype=="PropertiesNode"){
        newnode=insertNode<PropertiesNode>(nullptr);
    }
    else if(nodetype=="ArrayNode"){
        newnode=insertNode<ArrayNode>(nullptr);
    }
    else if(nodetype=="ProcessNode"){
        newnode=insertNode<ProcessNode>(nullptr);
    }
    FlowNode* newflownode= dynamic_cast<FlowNode*>(newnode);

    if(newnode){
        emit flowNodeAdded(newflownode);

    }
    QCoreApplication::processEvents();
    return newflownode;
}



FlowNode *SceneGraph::readNode(QJsonObject nodeobject)
{
    qan::Node* newnode=nullptr;


    newnode=createNode(nodeobject["type"].toString());


    FlowNode* flownode=dynamic_cast<FlowNode*>(newnode);
    if(flownode){

        flownode->DeSerialize(nodeobject);


    }

    return flownode;

}

void SceneGraph::copyNode(FlowNode* node){

    QJsonObject nodeobj;
    node->Serialize(nodeobj);


    nodeobj.take("id");
    nodeobj.take("inPorts");
    nodeobj.take("outPorts");
    //    QString nodetype=nodeobj["type"].toString();
    //    FlowNode* newnode=createNode(nodetype);
    FlowNode* newnode=readNode(nodeobj);

    if(newnode){
        newnode->getItem()->setProperty("x",QVariant::fromValue(node->getItem()->x()+75));
        newnode->getItem()->setProperty("y",QVariant::fromValue(node->getItem()->y()+75));

        this->selectNode(*newnode,Qt::NoModifier);
        //        int id=newnode->id();
        //        newnode->DeSerialize(nodeobj);
        //        newnode->setId(id);
    }



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



    //    auto mappedloc=mapToItem(this->getContainerItem(),loc);

    auto mappedloc=loc;

    if(node){
        node->getItem()->setProperty("x",QVariant::fromValue(mappedloc.x()));
        node->getItem()->setProperty("y",QVariant::fromValue(mappedloc.y()));

    }


    ////    if(node)
    //    int nodeid=getAvailableID();
    //    if(nodeid==-1){
    //        LOG_ERROR("Invalid node ID");
    //        return;
    //    }

    //    item->initializeNode(nodeid);




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
