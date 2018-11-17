#ifndef PROCESSINGENDNODE_H
#define PROCESSINGENDNODE_H

#include "processingnode.h"



class ProcessingEndNode : public ProcessingNode
{
public:
    ProcessingEndNode();

    // ProcessingNode interface
    static QQmlComponent *delegate(QQmlEngine &engine) noexcept;
public slots:
    virtual void setInput(QMat *input) override;

protected:
    virtual void doProcess() override;

    // JsonSerializable interface
public:
    virtual void DeSerialize(QJsonObject &json) override;
};

#endif // PROCESSINGENDNODE_H
