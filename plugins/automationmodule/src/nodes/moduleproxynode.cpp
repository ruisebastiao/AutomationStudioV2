#include "moduleproxynode.h"

#include <project.h>

ModuleProxyNode::ModuleProxyNode()
{
    m_type=Type::ModuleProxyNode;
}

void ModuleProxyNode::setSelectedBindedModuleID(int selectedBindedModuleID)
{

//    if (m_selectedBindedModuleID == selectedBindedModuleID)
//        return;

    setNodesFromModule(nullptr);

    m_selectedBindedModuleID = selectedBindedModuleID;

    if(m_selectedBindedModuleID==-1){
        return;
    }
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

void ModuleProxyNode::DeSerialize(QJsonObject &json)
{
    ProxyNode::DeSerialize(json);

    if(m_flowNodes){
        setBindedFlowNode(m_flowNodes->getByID(selectedBindedNodeID()));
    }

}
