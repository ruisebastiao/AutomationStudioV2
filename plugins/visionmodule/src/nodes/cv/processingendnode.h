#ifndef PROCESSINGENDNODE_H
#define PROCESSINGENDNODE_H

#include "processingnode.h"

#include <QObject>

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
};

#endif // PROCESSINGENDNODE_H
