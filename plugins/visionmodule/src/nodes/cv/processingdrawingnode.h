#ifndef PROCESSINGDRAWINGNODE_H
#define PROCESSINGDRAWINGNODE_H

#include "processingnode.h"



class ProcessingDrawingNode : public ProcessingNode
{
public:
    ProcessingDrawingNode();

    // ProcessingNode interface
public slots:
    virtual void setInput(QMat *input) override;

protected:
    virtual void doProcess() override;
};

#endif // PROCESSINGDRAWINGNODE_H
