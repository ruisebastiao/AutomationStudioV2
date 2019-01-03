#include "moduleproxynode.h"

#include <project.h>

ModuleProxyNode::ModuleProxyNode()
{
    m_type=Type::ModuleProxyNode;
}

void ModuleProxyNode::setSelectedBindedModuleID(int selectedBindedModuleID)
{



    if (m_selectedBindedModuleID == selectedBindedModuleID)
        return;

    setNodesFromModule(nullptr);

    m_selectedBindedModuleID = selectedBindedModuleID;

    if(parentModule()){
        QAutomationModule* parentmodule=parentModule();
        if(parentmodule->parentProject()){
            Project* project=parentmodule->parentProject();
            for (int var = 0; var < project->modules()->length(); ++var) {
                QAutomationModule* currentmodule=project->modules()->at(var);
                if(currentmodule->id()==m_selectedBindedModuleID && currentmodule->id()!=parentmodule->id()){


                    this->setNodesFromModule(currentmodule->flowNodes());


                    break;
                }
            }
        }
    }

    emit selectedBindedModuleIDChanged(m_selectedBindedModuleID);
}

void ModuleProxyNode::setNodesFromModule(FlowNodeManager *modulenodes)
{
    m_flowNodes = modulenodes;
    emit flowNodesChanged(modulenodes);
}

void ModuleProxyNode::setBindedFlowNode(FlowNode *node)
{

    ProxyNode::setBindedFlowNode(node);

//    if(!node){
//        return;
//    }


//    setSelectedBindedNodeID(node->id());


//    if(configsLoaded()==false){
//        return;
//    }

//    FlowNodePort* outputport=getPortFromKey("output");
//    FlowNodePort* inputport=getPortFromKey("input");

//    if(!outputport || !inputport){
//        return;
//    }

//    SceneGraph* graph=qobject_cast<SceneGraph*>(this->getGraph());

//    if(inputport->getPortItem()->getInEdgeItems().size()>0){

//        qan::EdgeItem* edgeitem=inputport->getPortItem()->getInEdgeItems().at(0);
//        graph->deleteEdge(edgeitem->getEdge());

//        QObject::connect(edgeitem, &qan::EdgeItem::destroyed,[&](QObject* edgeObject){
//            if(node){
//                qan::Edge* newedge=graph->insertNewEdge(true,node,this);
//                FlowNodePort* outPort=node->getPortByID("output");

//                if(outPort){
//                    graph->bindEdge(newedge,outPort->getPortItem(),inputport->getPortItem());
//                }
//            }
//        });
//    }
//    else{
//        if(node){
//            qan::Edge* newedge=graph->insertNewEdge(true,node,this);
//            FlowNodePort* outPort=node->getPortByID("output");

//            if(outPort){
//                graph->bindEdge(newedge,outPort->getPortItem(),inputport->getPortItem());
//            }
//        }
//    }

}



void ModuleProxyNode::initProxyNode()
{
    ProxyNode::initProxyNode();
    if(selectedBindedModuleID()==-1){
        setNodesFromModule(nullptr);
    }

}

void ModuleProxyNode::setFlowNodes(FlowNodeManager *flowNodes)
{

}
