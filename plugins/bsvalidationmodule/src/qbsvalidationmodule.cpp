#include "qbsvalidationmodule.h"

#include <nodes/bsvalidationnode.h>
#include <nodes/bsvalidationvisualnode.h>

QBSValidationModule::QBSValidationModule(QQuickItem* parent)
{

}

void QBSValidationModule::load(QString path)
{
    QAutomationModule::load(path);
}

FlowNode *QBSValidationModule::readNode(qan::GraphView *graphView, QJsonObject nodeobject)
{
    FlowNode* node=nullptr;

    node=QAutomationModule::readNode(graphView,nodeobject);

    if(node==nullptr){
        qan::Node* newnode=nullptr;

        if(nodeobject["type"]=="BSValidationNode"){
            newnode=graphView->getGraph()->insertNode<BSValidationNode>(nullptr);
        }
        if(nodeobject["type"]=="BSValidationVisualNode"){
            newnode=graphView->getGraph()->insertNode<BSValidationVisualNode>(nullptr);
        }

        FlowNode* modulenode=dynamic_cast<FlowNode*>(newnode);
        if(modulenode){
            modulenode->DeSerialize(nodeobject);

        }
        node=modulenode;
    }


    return  node;
}

void QBSValidationModule::save()
{
      QAutomationModule::save();
}
