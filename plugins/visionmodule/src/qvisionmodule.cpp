#include "qvisionmodule.h"


QVisionModule::QVisionModule(QQuickItem *parent)
{
    m_type=ModuleType::VisionModule;
}

void QVisionModule::load(QString path)
{
    qDebug()<<"Loading Vision module";
    QAutomationModule::load(path);
}

void QVisionModule::save()
{
    QAutomationModule::save();
}

FlowNode *QVisionModule::readNode(qan::GraphView *graphView, QJsonObject nodeobject)
{
    FlowNode* node=nullptr;

    node=QAutomationModule::readNode(graphView,nodeobject);

//    if(node==nullptr){
//        qan::Node* newnode=nullptr;

//        if(nodeobject["type"]=="BSValidationNode"){
//            newnode=graphView->getGraph()->insertNode<BSValidationNode>(nullptr);
//        }


//        FlowNode* modulenode=dynamic_cast<FlowNode*>(newnode);
//        if(modulenode){
//            modulenode->DeSerialize(nodeobject);

//        }
//        node=modulenode;
//    }


    return  node;
}
