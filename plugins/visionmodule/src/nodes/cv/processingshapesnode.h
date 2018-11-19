#ifndef PROCESSINGSHAPESNODE_H
#define PROCESSINGSHAPESNODE_H

#include "processingnode.h"



class ProcessingShapesNode : public ProcessingNode
{
public:
    ProcessingShapesNode();

    // JsonSerializable interface
public:

    static  QQmlComponent*      delegate(QQmlEngine& engine) noexcept;

    virtual void DeSerialize(QJsonObject &json) override;

    // ProcessingNode interface
public slots:
    virtual void setInput(QMat *input) override;

protected:
    virtual void doProcess() override;
};

#endif // PROCESSINGSHAPESNODE_H
