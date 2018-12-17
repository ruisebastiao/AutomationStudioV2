#include "processingscenegraph.h"

#include <nodes/cv/processingbasenode.h>
#include <nodes/cv/processingcontoursnode.h>
#include <nodes/cv/processingdrawingnode.h>
#include <nodes/cv/processingenclosingnode.h>
#include <nodes/cv/processingendnode.h>
#include <nodes/cv/processingfilternode.h>
#include <nodes/cv/processinggeometricnode.h>
#include <nodes/cv/processinglogicalnode.h>
#include <nodes/cv/processingmasknode.h>
#include <nodes/cv/processingthresholdnode.h>

ProcessingSceneGraph::ProcessingSceneGraph()
{

}

qan::Edge *ProcessingSceneGraph::insertNewEdge(bool hidden, qan::Node *source, qan::Node *destination)
{
    return SceneGraph::insertNewEdge(hidden,source,destination);
}

FlowNode *ProcessingSceneGraph::createNode(QString nodetype)
{
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
    else if(nodetype=="ProcessingLogicalNode"){
        newnode=insertNode<ProcessingLogicalNode>(nullptr);
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
    else{
        LOG_WARNING(QString("Unknown nodeobject processingType:%1").arg(nodetype));
    }



    ProcessingNode* procnode=dynamic_cast<ProcessingNode*>(newnode);


    return procnode;

}
