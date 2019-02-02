#include "processingscenegraph.h"

#include <nodes/cv/processingbasenode.h>
#include <nodes/cv/processingcannynode.h>
#include <nodes/cv/processingcontoursnode.h>
#include <nodes/cv/processingdrawingnode.h>
#include <nodes/cv/processingenclosingnode.h>
#include <nodes/cv/processingendnode.h>
#include <nodes/cv/processingfilternode.h>
#include <nodes/cv/processinggeometricnode.h>
#include <nodes/cv/processingmasknode.h>
#include <nodes/cv/processingthresholdnode.h>

ProcessingSceneGraph::ProcessingSceneGraph()
{

    getProcessingNodeTypes();




}


void ProcessingSceneGraph::getProcessingNodeTypes()
{
    QVariantList ret;

    QVariantMap map;


    map.insert(QVariant::fromValue(ProcessingNode::ProcessingType::ProcessingBaseNode).value<QString>(),"Base Node");
    ret.append(map);
    map.clear();

    map.insert(QVariant::fromValue(ProcessingNode::ProcessingType::ProcessingThresholdNode).value<QString>(),"Threshold");
    ret.append(map);
    map.clear();



    map.insert(QVariant::fromValue(ProcessingNode::ProcessingType::ProcessingFilterNode).value<QString>(),"Filtering");
    ret.append(map);
    map.clear();



    map.insert(QVariant::fromValue(ProcessingNode::ProcessingType::ProcessingEndNode).value<QString>(),"End Node");
    ret.append(map);
    map.clear();



    map.insert(QVariant::fromValue(ProcessingNode::ProcessingType::ProcessingContoursNode).value<QString>(),"Contours");
    ret.append(map);
    map.clear();



    map.insert(QVariant::fromValue(ProcessingNode::ProcessingType::ProcessingEnclosingNode).value<QString>(),"Enclosing shapes");
    ret.append(map);
    map.clear();


    map.insert(QVariant::fromValue(ProcessingNode::ProcessingType::ProcessingGeometricNode).value<QString>(),"Geometric shapes");
    ret.append(map);
    map.clear();



    map.insert(QVariant::fromValue(ProcessingNode::ProcessingType::ProcessingCannyNode).value<QString>(),"Canny Edge");
    ret.append(map);
    map.clear();



    map.insert(QVariant::fromValue(ProcessingNode::ProcessingType::ProcessingMaskNode).value<QString>(),"Mask");
    ret.append(map);
    map.clear();


    map.insert(QVariant::fromValue(ProcessingNode::ProcessingType::ProcessingDrawingNode).value<QString>(),"Drawing");
    ret.append(map);
    map.clear();


    m_processingNodeTypes.append(ret);

    emit processingNodeTypesChanged(m_processingNodeTypes);
}

FlowNode *ProcessingSceneGraph::readNode(QJsonObject nodeobject)
{


    FlowNode* flownode=createNode(nodeobject["processingType"].toString());


     if(flownode){

        flownode->DeSerialize(nodeobject);


    }
    else {
         qan::Node* newnode=createNode(nodeobject["type"].toString());


        flownode=dynamic_cast<FlowNode*>(newnode);
        if(flownode){

            flownode->DeSerialize(nodeobject);


        }

    }

    return flownode;

}



qan::Edge *ProcessingSceneGraph::insertNewEdge(bool hidden, qan::Node *source, qan::Node *destination)
{
    return SceneGraph::insertNewEdge(hidden,source,destination);
}

FlowNode *ProcessingSceneGraph::createNode(QString nodetype)
{

    FlowNode* flownode=SceneGraph::createNode(nodetype);


    if(!flownode){

        qan::Node* newnode=nullptr;

        if(nodetype=="ProcessingBaseNode"){
            newnode=insertNode<ProcessingBaseNode>(nullptr);
        }
        else if(nodetype=="ProcessingThresholdNode"){
            newnode=insertNode<ProcessingThresholdNode>(nullptr);
        }
        else if(nodetype=="ProcessingFilterNode"){
            newnode=insertNode<ProcessingFilterNode>(nullptr);
        }
        else if(nodetype=="ProcessingEndNode"){
            newnode=insertNode<ProcessingEndNode>(nullptr);
        }
        else if(nodetype=="ProcessingContoursNode"){
            newnode=insertNode<ProcessingContoursNode>(nullptr);
        }
        else if(nodetype=="ProcessingEnclosingNode"){
            newnode=insertNode<ProcessingEnclosingNode>(nullptr);
        }
        else if(nodetype=="ProcessingGeometricNode"){
            newnode=insertNode<ProcessingGeometricNode>(nullptr);
        }
        else if(nodetype=="ProcessingMaskNode"){
            newnode=insertNode<ProcessingMaskNode>(nullptr);
        }
        else if(nodetype=="ProcessingDrawingNode"){
            newnode=insertNode<ProcessingDrawingNode>(nullptr);
        }
        else if(nodetype=="ProcessingCannyNode"){
            newnode=insertNode<ProcessingCannyNode>(nullptr);
        }
        else{
            LOG_WARNING(QString("Unknown nodeobject processingType:%1").arg(nodetype));
        }

        flownode=dynamic_cast<FlowNode*>(newnode);

        if(flownode){
            emit flowNodeAdded(flownode);

        }



    }



    return flownode;

}
