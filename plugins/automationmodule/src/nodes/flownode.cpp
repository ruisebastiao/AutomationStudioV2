#include "flownode.h"
#include "src/graphs/scenegraph.h"
#include "qautomationmodule.h"

FlowNode::FlowNode(QObject *parent):qan::Node(parent)
{


//    QObject::connect(QAutomationModule::flownodemanager, &FlowNodeManager::onFlowNodeLoaded,[this](FlowNode* nodeLoaded){

//        if(nodeLoaded==this){
//            return;
//        }

//        qDebug()<<"On node added";

//        foreach (FlowNodePort* flownodeport, m_outPorts) {
//            if(flownodeport->getType()==qan::PortItem::Type::Out){




//                for (int index1 = 0; index1 < flownodeport->getConnections().length(); ++index1) {
//                    ConnectionInfo* connectinfo=flownodeport->getConnections().at(index1);
//                    if(connectinfo->nodeID()==nodeLoaded->id()){

//                        qan::Edge* newedge= m_scenegraph->insertNewEdge(false,this,nodeLoaded);

//                        for (int index2 = 0; index2 < nodeLoaded->getInPorts()->getConnections().length(); ++index2) {
//                            ConnectionInfo* connectinfo=flownodeport->getConnections().at(index1);
//                            if(connectinfo->nodeID()==nodeLoaded->id()){

//                                qan::Edge* newedge= m_scenegraph->insertNewEdge(false,this,nodeLoaded);


//                            }
//                        }

//                    }
//                }

//            }
//        }

//    });





}


QQmlComponent*  FlowNode::delegate(QQmlEngine& engine) noexcept
{
    static std::unique_ptr<QQmlComponent>   qan_FlowNode_delegate;
    if ( !qan_FlowNode_delegate )
        qan_FlowNode_delegate = std::make_unique<QQmlComponent>(&engine, "qrc:///Nodes/FlowNode.qml");
    return qan_FlowNode_delegate.get();
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

//FlowNodePort* FlowNode::getPortByName(QString portname)
//{
//    portname+="Port";
//    for (int i = 0; i < this->metaObject()->propertyCount(); i++)
//    {


//        QMetaProperty property=this->metaObject()->property(i);
//        if(property.name()==portname){
//            property=this->metaObject()->property(i);
//            QVariant value = this->property(property.name());
//            return value.value<FlowNodePort*>();
//            break;
//        }


//    }

//}

void FlowNode::installBehaviour(std::unique_ptr<qan::NodeBehaviour> behaviour)
{

}


