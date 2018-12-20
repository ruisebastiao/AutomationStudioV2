#include "visiongraph.h"

#include <nodes/roinode.h>

VisionGraph::VisionGraph()
{
    getVisionNodeTypes();
}


void VisionGraph::getVisionNodeTypes()
{
    QVariantList ret;

    QVariantMap map;

    map.insert(QVariant::fromValue(FlowNode::Type::ROINode).value<QString>(),"ROI");
    ret.append(map);
    map.clear();


    m_visionNodeTypes.append(ret);

    emit visionNodeTypesChanged(m_visionNodeTypes);
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


    FlowNode* flownode=dynamic_cast<FlowNode*>(newnode);

    if(flownode){
        emit flowNodeAdded(flownode);

    }

    return  flownode;



}
