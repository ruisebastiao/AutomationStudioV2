#include "logicnode.h"

LogicNode::LogicNode()
{
    m_type=Type::LogicNode;


}


QQmlComponent *LogicNode::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/LogicalNodeItem.qml"));
    return delegate.get();

}


void LogicNode::updateport(QString portname,bool enabled){

    FlowNodePort* inport=getPortFromKey(portname);
    if(!inport){
        return;
    }
    if(enabled==false){


        SceneGraph* graph=qobject_cast<SceneGraph*>(this->getGraph());

        if(inport->getPortItem()->getInEdgeItems().size()>0){

            qan::EdgeItem* edgeitem=inport->getPortItem()->getInEdgeItems().at(0);
            graph->deleteEdge(edgeitem->getEdge());
        }

        inport->setHidden(true);
    }
    else{
        inport->setHidden(false);
    }

}


void LogicNode::updateports(){


    updateport("logicalInput1",in1Enabled());
    updateport("logicalInput2",in2Enabled());
    updateport("logicalInput3",in3Enabled());
    updateport("logicalInput4",in4Enabled());




}





void LogicNode::DeSerialize(QJsonObject &json)
{

    FlowNode::DeSerialize(json);

    updateports();

}
