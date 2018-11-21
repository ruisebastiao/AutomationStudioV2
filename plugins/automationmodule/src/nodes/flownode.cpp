#include "flownode.h"
#include "src/graphs/scenegraph.h"
#include "qautomationmodule.h"

FlowNode::FlowNode(QObject *parent):qan::Node(parent)
{



}

std::ostream& operator <<(std::ostream &out, const FlowNode &c)
{
    out <<c;

    return out;
}

QDataStream& operator <<(QDataStream &stream, FlowNode &c) {

    stream<< c;
    return stream;

}

FlowNode::~FlowNode()
{
    //
    LOG_INFO()<<"Deleting node:"<<this->id()<<"|"<<this->name();


    //    this->getGraph()->re->deleteEdge(m_inputPort->getPortItem()->getInEdgeItems().at(0)->getEdge());

}

void FlowNode::loadNodeConnections( QList<FlowNode *> nodeList)
{

    foreach (FlowNode* flownode, nodeList) {
        foreach (FlowNodePort* flownodeport, flownode->getOutPorts()) {
            QList<ConnectionInfo*> connections=flownodeport->getConnections();
            foreach (ConnectionInfo* connection, connections) {
                FlowNode* targetnode=FlowNode::getFlowNodeById(connection->nodeID(),nodeList);
                if(targetnode){

                    for (int portindex = 0; portindex < targetnode->getInPorts().length(); ++portindex) {
                        FlowNodePort* targetInport=targetnode->getInPorts().at(portindex);
                        qan::PortItem* inport=targetInport->getPortItem();
                        if(inport->getInEdgeItems().size()>0){
                            LOG_ERROR()<<"In edge with multiple connection (Source node:"<<*flownode<<"| target node:"<< *targetnode<<")";
                            continue;
                        }
                        qan::Edge* newedge= flownode->getScenegraph()->insertNewEdge(false,flownode,targetnode);
                        if(newedge){
                            if(targetInport->getPortItem()->getId()==connection->portID()){
                                flownode->getScenegraph()->bindEdge(newedge,flownodeport->getPortItem(),targetInport->getPortItem());

                                break;
                            }
                        }

                    }
                }
            }
            flownode->setConnectionsLoaded(true);
        }
    }
}

FlowNode *FlowNode::getFlowNodeById(int id, QList<FlowNode *> nodeList)
{
    for (int var = 0; var < nodeList.length(); ++var) {
        if(nodeList.at(var)->id()==id){
            return  nodeList.at(var);
        }
    }

    return nullptr;
}


QQmlComponent*  FlowNode::delegate(QQmlEngine& engine) noexcept
{

    static UniqueQQmlComponentPtr   qan_FlowNode_delegate;
    if ( !qan_FlowNode_delegate )
        qan_FlowNode_delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/FlowNode.qml"));
    return qan_FlowNode_delegate.get();
}

void FlowNode::remove()
{
    emit removeNode(this);
}

void FlowNode::initializePorts()
{

}

SceneGraph *FlowNode::getScenegraph() const
{
    return m_scenegraph;
}

void FlowNode::inNodeOutputChanged()
{

}

QList<FlowNodePort *> FlowNode::getOutPorts() const
{
    return m_outPorts;
}

QList<FlowNodePort *> FlowNode::getInPorts() const
{
    return m_inPorts;
}



void FlowNode::inPortState(QString id,bool enabled)
{

}



void FlowNode::Serialize(QJsonObject &json)
{
    JsonSerializable::Serialize(json,this);

    json["nodeX"]=getItem()->x();
    json["nodeY"]=getItem()->y();



    json["editWidth"]=editWidth();
    json["editHeight"]=editHeight();

    json["normalWidth"]= normalWidth();
    json["normalHeight"]=normalHeight();

}


void FlowNode::DeSerialize(QJsonObject &json)
{

    initializePorts();

    JsonSerializable::DeSerialize(json,this);
    getItem()->setProperty("x",QVariant::fromValue(json["nodeX"].toDouble()));
    getItem()->setProperty("y",QVariant::fromValue(json["nodeY"].toDouble()));

    setNormalWidth(json["normalWidth"].toInt());
    setNormalHeight(json["normalHeight"].toInt());

    setEditWidth(json["editWidth"].toInt());

    setEditHeight(json["editHeight"].toInt());

    this->m_scenegraph=qobject_cast<SceneGraph*>(this->getGraph());

    emit QAutomationModule::flownodemanager->onFlowNodeLoaded(this);

}



FlowNodePort* FlowNode::getPortByID(QString id)
{

    foreach (FlowNodePort* port, m_inPorts) {
        if(port->getPortItem()->getId()==id){
            return port;
        }
    }

    foreach (FlowNodePort* port, m_outPorts) {
        if(port->getPortItem()->getId()==id){
            return port;
        }
    }

    return nullptr;
}

void FlowNode::installBehaviour(std::unique_ptr<qan::NodeBehaviour> behaviour)
{

}


