#ifndef BSVALIDATIONGRAPH_H
#define BSVALIDATIONGRAPH_H

#include <scenegraph.h>

class BSValidationGraph : public SceneGraph
{
public:
    BSValidationGraph();

    // SceneGraph interface
public:
    virtual FlowNode *createNode(QString nodetype) override;
private:
    void getModuleNodeTypes();
};

#endif // BSVALIDATIONGRAPH_H
