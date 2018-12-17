#ifndef PROCESSINGSCENEGRAPH_H
#define PROCESSINGSCENEGRAPH_H

#include <scenegraph.h>



class ProcessingSceneGraph : public SceneGraph
{
public:
    ProcessingSceneGraph();

    // SceneGraph interface
public:
    virtual qan::Edge *insertNewEdge(bool hidden, qan::Node *source, qan::Node *destination) override;

    // SceneGraph interface
public:

    // SceneGraph interface
public:
    virtual FlowNode *createNode(QString nodetype) override;
};

#endif // PROCESSINGSCENEGRAPH_H
