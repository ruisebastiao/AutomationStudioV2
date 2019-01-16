#include "epsongraph.h"


#include <nodes/epsonnode.h>
#include <nodes/epsonremote.h>
#include <nodes/toolnode.h>

EpsonGraph::EpsonGraph()
{
    getModuleNodeTypes();
}

void EpsonGraph::getModuleNodeTypes()
{
    QVariantList ret;

    QVariantMap map;

    map.insert(QVariant::fromValue(FlowNode::Type::EpsonNode).value<QString>(),"Epson Client");
    ret.append(map);
    map.clear();

    map.insert(QVariant::fromValue(FlowNode::Type::EpsonRemote).value<QString>(),"Epson Remote");
    ret.append(map);
    map.clear();

    map.insert(QVariant::fromValue(FlowNode::Type::ToolNode).value<QString>(),"Tool");
    ret.append(map);
    map.clear();

    m_moduleNodeTypes.append(ret);

    emit moduleNodeTypesChanged(m_moduleNodeTypes);
}


FlowNode *EpsonGraph::createNode(QString nodetype)
{

    FlowNode* flownode=SceneGraph::createNode(nodetype);



    if(!flownode){
        qan::Node* node=nullptr;

        if(nodetype=="EpsonNode"){
            node=insertNode<EpsonNode>(nullptr);
        }
        else if(nodetype=="EpsonRemote"){
            node=insertNode<EpsonRemote>(nullptr);
        }
        else if(nodetype=="ToolNode"){
            node=insertNode<ToolNode>(nullptr);
        }
        else{
            LOG_WARNING(QString("Unknown node type:%1").arg(nodetype));
        }
        flownode=dynamic_cast<FlowNode*>(node);

        if(flownode){
            emit flowNodeAdded(flownode);

        }



    }

    return  flownode;

}
