#include "bsvalidationgraph.h"

#include <nodes/bsvalidationnode.h>

BSValidationGraph::BSValidationGraph()
{

}

FlowNode *BSValidationGraph::createNode(QString nodetype)
{
    qan::Node* newnode=nullptr;

    newnode=SceneGraph::createNode(nodetype);

    if(!newnode){
        if(nodetype=="BSValidationNode"){
            newnode=insertNode<BSValidationNode>(nullptr);
        }
        else{
            LOG_WARNING(QString("Unknown node type:%1").arg(nodetype));
        }
    }



    return  dynamic_cast<FlowNode*>(newnode);

}
