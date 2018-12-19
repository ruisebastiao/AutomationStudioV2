#ifndef VISIONMODULEGRAPH_H
#define VISIONMODULEGRAPH_H

#include <scenegraph.h>

class VisionModuleGraph : public SceneGraph
{
public:
    VisionModuleGraph();

    // SceneGraph interface
public:
    virtual FlowNode *createNode(QString nodetype) override;
};

#endif // VISIONMODULEGRAPH_H
