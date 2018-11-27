#include "processingscenegraph.h"

ProcessingSceneGraph::ProcessingSceneGraph()
{

}

qan::Edge *ProcessingSceneGraph::insertNewEdge(bool hidden, qan::Node *source, qan::Node *destination)
{
    return SceneGraph::insertNewEdge(hidden,source,destination);
}
