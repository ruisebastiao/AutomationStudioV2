#ifndef EPSONGRAPH_H
#define EPSONGRAPH_H

#include <scenegraph.h>



class EpsonGraph : public SceneGraph
{
public:
    EpsonGraph();

    // SceneGraph interface
public:
    virtual FlowNode *createNode(QString nodetype) override;
};

#endif // EPSONGRAPH_H
