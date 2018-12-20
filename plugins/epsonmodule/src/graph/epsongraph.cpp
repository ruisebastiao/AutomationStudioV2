#include "epsongraph.h"

#include <nodes/commandparsernode.h>
#include <nodes/commandsendernode.h>
#include <nodes/epsonnode.h>

EpsonGraph::EpsonGraph()
{

}

void EpsonGraph::getModuleNodeTypes()
{
    QVariantList ret;

    QVariantMap map;

    map.insert(QVariant::fromValue(FlowNode::Type::EpsonNode).value<QString>(),"Epson");
    ret.append(map);
    map.clear();

    map.insert(QVariant::fromValue(FlowNode::Type::CommandSenderNode).value<QString>(),"Command Sender");
    ret.append(map);
    map.clear();

    map.insert(QVariant::fromValue(FlowNode::Type::CommandParserNode).value<QString>(),"Command Parser");
    ret.append(map);
    map.clear();

    m_moduleNodeTypes.append(ret);

    emit moduleNodeTypesChanged(m_moduleNodeTypes);
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


    FlowNode* flownode=dynamic_cast<FlowNode*>(node);

    if(flownode){
        emit flowNodeAdded(flownode);

    }

    return  flownode;

}
