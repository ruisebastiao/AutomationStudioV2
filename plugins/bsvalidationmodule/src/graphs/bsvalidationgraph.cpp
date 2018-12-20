#include "bsvalidationgraph.h"

#include <nodes/bsvalidationnode.h>

BSValidationGraph::BSValidationGraph()
{
    getModuleNodeTypes();
}


void BSValidationGraph::getModuleNodeTypes()
{
    QVariantList ret;

    QVariantMap map;

    map.insert(QVariant::fromValue(FlowNode::Type::BSValidationNode).value<QString>(),"BS Validation");
    ret.append(map);
    map.clear();



    m_moduleNodeTypes.append(ret);

    emit moduleNodeTypesChanged(m_moduleNodeTypes);
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


    FlowNode* flownode=dynamic_cast<FlowNode*>(newnode);

    if(flownode){
        emit flowNodeAdded(flownode);

    }

    return flownode;

}
