#ifndef VISIONGRAPH_H
#define VISIONGRAPH_H

#include <scenegraph.h>

class VisionGraph : public SceneGraph
{
    Q_OBJECT

    Q_PROPERTY(QVariantList visionNodeTypes READ visionNodeTypes NOTIFY visionNodeTypesChanged)



public:
    VisionGraph();

    // SceneGraph interface
public:
    virtual FlowNode *createNode(QString nodetype) override;
    QVariantList visionNodeTypes() const
    {
        return m_visionNodeTypes;
    }
signals:
    void visionNodeTypesChanged(QVariantList visionNodeTypes);

private:
    QVariantList m_visionNodeTypes;
    void getVisionNodeTypes();
};

#endif // VISIONGRAPH_H
