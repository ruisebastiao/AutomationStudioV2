#ifndef PROCESSINGFILTERNODE_H
#define PROCESSINGFILTERNODE_H

#include "processingnode.h"



class ProcessingFilterNode : public ProcessingNode
{
public:
    ProcessingFilterNode();

    // ProcessingNode interface
    static QQmlComponent *delegate(QQmlEngine &engine)noexcept;
public slots:
    virtual void setInput(QMat *input) override;

protected:
    virtual void doProcess() override;
};

#endif // PROCESSINGFILTERNODE_H
