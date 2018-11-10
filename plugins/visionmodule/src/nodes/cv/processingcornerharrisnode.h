#ifndef PROCESSINGCORNERHARRISNODE_H
#define PROCESSINGCORNERHARRISNODE_H

#include "processingnode.h"

#include <QObject>

class ProcessingCornerHarrisNode : public ProcessingNode
{
public:
    ProcessingCornerHarrisNode();
    static QQmlComponent *delegate(QQmlEngine &engine) noexcept;

    // ProcessingNode interface
public slots:
    virtual void setInput(QMat *input) override;

protected:
    virtual void doProcess() override;
};

#endif // PROCESSINGCORNERHARRISNODE_H
