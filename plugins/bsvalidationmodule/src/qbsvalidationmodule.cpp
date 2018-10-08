#include "qbsvalidationmodule.h"

#include <nodes/bsvalidationnode.h>


QBSValidationModule::QBSValidationModule(QQuickItem* parent)
{
    m_type=ModuleType::BSValidationModule;
}

void QBSValidationModule::load(QString path)
{
    qDebug()<<"Loading BSValidation module";
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
        else{
            LOG_WARNING(QString("Unknown nodeobject type:%1").arg(nodeobject["type"].toString()));
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
