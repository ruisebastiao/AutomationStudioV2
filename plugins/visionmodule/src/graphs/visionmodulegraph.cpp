#include "visionmodulegraph.h"

#include <nodes/filecapturenode.h>
#include <nodes/idscapturenode.h>
#include <nodes/visionsystemnode.h>

VisionModuleGraph::VisionModuleGraph()
{
    getModuleNodeTypes();
}



void VisionModuleGraph::getModuleNodeTypes()
{
    QVariantList ret;

    QVariantMap map;

    map.insert(QVariant::fromValue(FlowNode::Type::IDSCaptureNode).value<QString>(),"IDS Camera");
    ret.append(map);
    map.clear();

    map.insert(QVariant::fromValue(FlowNode::Type::FileCaptureNode).value<QString>(),"File Capture");
    ret.append(map);
    map.clear();

    map.insert(QVariant::fromValue(FlowNode::Type::FrameBufferNode).value<QString>(),"Frame Buffer");
    ret.append(map);
    map.clear();

    map.insert(QVariant::fromValue(FlowNode::Type::VisionSystemNode).value<QString>(),"Vision Processing");
    ret.append(map);
    map.clear();

    m_moduleNodeTypes.append(ret);

    emit moduleNodeTypesChanged(m_moduleNodeTypes);
}

FlowNode *VisionModuleGraph::createNode(QString nodetype)
{
    qan::Node* newnode=nullptr;

    newnode=SceneGraph::createNode(nodetype);

    if(!newnode){


        if(nodetype=="IDSCaptureNode"){
            newnode=insertNode<IDSCaptureNode>(nullptr);
        }
        else if(nodetype=="FileCaptureNode"){
            newnode=insertNode<FileCaptureNode>(nullptr);
        }
        else if(nodetype=="VisionSystemNode"){
            newnode=insertNode<VisionSystemNode>(nullptr);
        }
        else if(nodetype=="FrameBufferNode"){
            newnode=insertNode<FrameBufferNode>(nullptr);
        }
        else{
            LOG_WARNING(QString("Unknown module node type:%1").arg(nodetype));
        }

    }

    return  dynamic_cast<FlowNode*>(newnode);



}
