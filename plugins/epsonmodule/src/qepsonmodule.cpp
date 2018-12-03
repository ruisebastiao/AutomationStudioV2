#include "qepsonmodule.h"


QEpsonModule::QEpsonModule(QQuickItem *parent)
{
    m_type=ModuleType::EpsonModule;

}

void QEpsonModule::loadModuleSettings(QString path)
{
    qDebug()<<"Loading Epson module";
    QAutomationModule::loadModuleSettings(path);
}

void QEpsonModule::save()
{
    QAutomationModule::save();
}

FlowNode *QEpsonModule::readNode(qan::GraphView *graphView, QJsonObject nodeobject)
{
    FlowNode* node=nullptr;

    node=QAutomationModule::readNode(graphView,nodeobject);

    if(node==nullptr){
        qan::Node* newnode=nullptr;

//        if(nodeobject["type"]=="IDSCaptureNode"){
//            newnode=graphView->getGraph()->insertNode<IDSCaptureNode>(nullptr);
//        }
//        else if(nodeobject["type"]=="FileCaptureNode"){
//            newnode=graphView->getGraph()->insertNode<FileCaptureNode>(nullptr);
//        }
//        else if(nodeobject["type"]=="VisionSystemNode"){
//            newnode=graphView->getGraph()->insertNode<VisionSystemNode>(nullptr);
//        }
//        else if(nodeobject["type"]=="FrameBufferNode"){
//            newnode=graphView->getGraph()->insertNode<FrameBufferNode>(nullptr);
//        }
//        else{
            LOG_WARNING(QString("Unknown nodeobject type:%1").arg(nodeobject["type"].toString()));
//        }



        FlowNode* modulenode=dynamic_cast<FlowNode*>(newnode);
        if(modulenode){
            modulenode->DeSerialize(nodeobject);

        }
        node=modulenode;
    }


    return  node;
}
