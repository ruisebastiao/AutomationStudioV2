#include "visiongraph.h"

#include <nodes/roinode.h>

VisionGraph::VisionGraph()
{

}

FlowNode *VisionGraph::createNode(QString nodetype)
{
    qan::Node* newnode=nullptr;

    newnode=SceneGraph::createNode(nodetype);

    if(!newnode){


        if(nodetype=="ROINode"){
            newnode=insertNode<ROINode>(nullptr);
        }

        else{
            LOG_WARNING(QString("Unknown module node type:%1").arg(nodetype));
        }

    }

    return  dynamic_cast<FlowNode*>(newnode);



}
