#include "qvisionmodule.h"

#include <nodes/filecapturenode.h>
#include <nodes/framebuffernode.h>
#include <nodes/idscapturenode.h>
#include <nodes/visionsystemnode.h>


QVisionModule::QVisionModule(QQuickItem *parent)
{
    m_type=ModuleType::VisionModule;
    m_moduleName="Vision";
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

FlowNode *QVisionModule::createModuleNode(qan::GraphView *graphView, QString nodetype)
{

    qan::Node* newnode=nullptr;

    if(nodetype=="IDSCaptureNode"){
        newnode=graphView->getGraph()->insertNode<IDSCaptureNode>(nullptr);
    }
    else if(nodetype=="FileCaptureNode"){
        newnode=graphView->getGraph()->insertNode<FileCaptureNode>(nullptr);
    }
    else if(nodetype=="VisionSystemNode"){
        newnode=graphView->getGraph()->insertNode<VisionSystemNode>(nullptr);
    }
    else if(nodetype=="FrameBufferNode"){
        newnode=graphView->getGraph()->insertNode<FrameBufferNode>(nullptr);
    }
    else{
        LOG_WARNING(QString("Unknown module node type:%1").arg(nodetype));
    }



    return  dynamic_cast<FlowNode*>(newnode);



}
