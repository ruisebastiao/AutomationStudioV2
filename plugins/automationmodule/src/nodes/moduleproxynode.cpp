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

    m_selectedBindedModuleID = selectedBindedModuleID;

    if(parentModule()){
        QAutomationModule* parentmodule=parentModule();
        if(parentmodule->parentProject()){
            Project* project=parentmodule->parentProject();
            for (int var = 0; var < project->modules()->length(); ++var) {
                QAutomationModule* currentmodule=project->modules()->at(var);
                if(currentmodule->id()==m_selectedBindedModuleID && currentmodule->id()!=parentmodule->id()){
                    this->setFlowNodes(nullptr);

                    this->setFlowNodes(currentmodule->flowNodes());
                    break;
                }
            }
        }
    }

    emit selectedBindedModuleIDChanged(m_selectedBindedModuleID);
}

void ModuleProxyNode::setBindedFlowNode(FlowNode *node)
{

    if(node){

    }
}
