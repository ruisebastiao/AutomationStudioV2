#ifndef PROCESSINGDRAWINGNODE_H
#define PROCESSINGDRAWINGNODE_H

#include "processingnode.h"



class ProcessingDrawingNode : public ProcessingNode
{
public:
    ProcessingDrawingNode();

    // ProcessingNode interface
    static QQmlComponent *delegate(QQmlEngine &engine)noexcept;
public slots:
    virtual void setInput(QVariant input) override;

protected:
    virtual void doProcess() override;

    // JsonSerializable interface
public:
    virtual void DeSerialize(QJsonObject &json) override;
};

#endif // PROCESSINGDRAWINGNODE_H
