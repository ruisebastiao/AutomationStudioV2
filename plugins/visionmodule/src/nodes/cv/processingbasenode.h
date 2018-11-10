#ifndef PROCESSINGBASENODE_H
#define PROCESSINGBASENODE_H

#include "processingnode.h"

#include <QObject>

class ProcessingBaseNode : public ProcessingNode
{
public:
    ProcessingBaseNode();

    static QQmlComponent *delegate(QQmlEngine &engine) noexcept;


    // ProcessingNode interface
public slots:
    virtual void setInput(QMat *input) override;

protected:
    virtual void doProcess() override;
};

#endif // PROCESSINGBASENODE_H
