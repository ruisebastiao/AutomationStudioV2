#include "epsongraph.h"

#include <nodes/commandparsernode.h>
#include <nodes/commandsendernode.h>
#include <nodes/epsonnode.h>

EpsonGraph::EpsonGraph()
{

}

FlowNode *EpsonGraph::createNode(QString nodetype)
{

    qan::Node* node=nullptr;


    node=SceneGraph::createNode(nodetype);

    if(!node){
        if(nodetype=="EpsonNode"){
            node=insertNode<EpsonNode>(nullptr);
        }
        else if(nodetype=="CommandSenderNode"){
            node=insertNode<CommandSenderNode>(nullptr);


        }
        else if(nodetype=="CommandParserNode"){
            node=insertNode<CommandParserNode>(nullptr);


        }

        if(node==nullptr){

            LOG_WARNING(QString("Unknown node type:%1").arg(nodetype));

        }
    }
    return  dynamic_cast<FlowNode*>(node);

}
