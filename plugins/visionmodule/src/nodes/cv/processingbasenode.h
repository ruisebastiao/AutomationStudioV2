#ifndef PROCESSINGBASENODE_H
#define PROCESSINGBASENODE_H

#include "processingnode.h"



class ProcessingBaseNode : public ProcessingNode
{
    Q_OBJECT
public:
    ProcessingBaseNode();


    static  QQmlComponent*      delegate(QQmlEngine& engine) noexcept;


    // ProcessingNode interface
protected:
    virtual void doProcess() override;

    // JsonSerializable interface
public:
    virtual void DeSerialize(QJsonObject &json) override;

    // ProcessingNode interface
public slots:
    virtual void setInput(QMat *input) override;
};

#endif // PROCESSINGBASENODE_H
