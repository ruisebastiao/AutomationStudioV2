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

    FlowNode* flownode=SceneGraph::createNode(nodetype);

    if(!flownode){
        qan::Node* newnode=nullptr;

        if(nodetype=="BSValidationNode"){
            newnode=insertNode<BSValidationNode>(nullptr);
        }
        else{
            LOG_WARNING(QString("Unknown node type:%1").arg(nodetype));
        }
        flownode=dynamic_cast<FlowNode*>(newnode);

        if(flownode){
            emit flowNodeAdded(flownode);

        }

    }



    return flownode;

}
