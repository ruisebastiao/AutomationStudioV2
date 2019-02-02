#ifndef PROCESSINGCANNYNODE_H
#define PROCESSINGCANNYNODE_H

#include "processingnode.h"



class ProcessingCannyNode:public ProcessingNode
{
    Q_OBJECT

    Q_PROPERTY(int delta READ delta WRITE setDelta NOTIFY deltaChanged USER("serialize"))
public:
    ProcessingCannyNode();


    static  QQmlComponent*      delegate(QQmlEngine& engine) noexcept;

    int delta() const
    {
        return m_delta;
    }

private:

    // ProcessingNode interface
    int m_delta=10;

public slots:
    virtual void setInput(QVariant input) override;

void setDelta(int delta)
{
    if (m_delta == delta)
        return;

    m_delta = delta;
    emit deltaChanged(m_delta);
}

signals:
void deltaChanged(int delta);

protected:
    virtual void doProcess() override;
};

#endif // PROCESSINGCANNYNODE_H
