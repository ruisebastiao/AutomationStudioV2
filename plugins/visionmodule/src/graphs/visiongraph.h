#ifndef VISIONGRAPH_H
#define VISIONGRAPH_H

#include <scenegraph.h>

class VisionGraph : public SceneGraph
{
public:
    VisionGraph();

    // SceneGraph interface
public:
    virtual FlowNode *createNode(QString nodetype) override;
};

#endif // VISIONGRAPH_H
