#include "visionmodulegraph.h"

#include <nodes/filecapturenode.h>
#include <nodes/idscapturenode.h>
#include <nodes/visionsystemnode.h>

VisionModuleGraph::VisionModuleGraph()
{

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
