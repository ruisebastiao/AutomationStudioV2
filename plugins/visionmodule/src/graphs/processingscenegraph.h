#ifndef PROCESSINGSCENEGRAPH_H
#define PROCESSINGSCENEGRAPH_H

#include <scenegraph.h>



class ProcessingSceneGraph : public SceneGraph
{
    Q_OBJECT

    Q_PROPERTY(QVariantList processingNodeTypes READ processingNodeTypes NOTIFY processingNodeTypesChanged)

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
    QVariantList processingNodeTypes() const
    {
        return m_processingNodeTypes;
    }
signals:
    void processingNodeTypesChanged(QVariantList processingNodeTypes);

private:
    QVariantList m_processingNodeTypes;

    void getProcessingNodeTypes();

    // SceneGraph interface
public:
    virtual FlowNode *readNode(QJsonObject nodeobject) override;
};

#endif // PROCESSINGSCENEGRAPH_H
