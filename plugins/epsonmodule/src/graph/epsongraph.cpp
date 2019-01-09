#include "epsongraph.h"


#include <nodes/epsonnode.h>

EpsonGraph::EpsonGraph()
{
    getModuleNodeTypes();
}

void EpsonGraph::getModuleNodeTypes()
{
    QVariantList ret;

    QVariantMap map;

    map.insert(QVariant::fromValue(FlowNode::Type::EpsonNode).value<QString>(),"Epson");
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
