#include "qvisionmodule.h"

#include <nodes/filecapturenode.h>
#include <nodes/idscapturenode.h>
#include <nodes/visionsystemnode.h>


QVisionModule::QVisionModule(QQuickItem *parent)
{
    m_type=ModuleType::VisionModule;
}

void QVisionModule::loadModuleSettings(QString path)
{
    qDebug()<<"Loading Vision module";
    QAutomationModule::loadModuleSettings(path);
}

void QVisionModule::save()
{
    QAutomationModule::save();
}


FlowNode *QVisionModule::readNode(qan::GraphView *graphView, QJsonObject nodeobject)
{
    FlowNode* node=nullptr;

    node=QAutomationModule::readNode(graphView,nodeobject);

    if(node==nullptr){
        qan::Node* newnode=nullptr;

        if(nodeobject["type"]=="IDSCaptureNode"){
            newnode=graphView->getGraph()->insertNode<IDSCaptureNode>(nullptr);
        }
        else if(nodeobject["type"]=="FileCaptureNode"){
            newnode=graphView->getGraph()->insertNode<FileCaptureNode>(nullptr);
        }
        else if(nodeobject["type"]=="VisionSystemNode"){
            newnode=graphView->getGraph()->insertNode<VisionSystemNode>(nullptr);
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
