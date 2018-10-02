#ifndef PROCESSINGTHRESHOLDNODE_H
#define PROCESSINGTHRESHOLDNODE_H

#include "processingnode.h"



class ProcessingThresholdNode : public ProcessingNode
{

    Q_OBJECT
    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged USER("serializable"))

public:
    ProcessingThresholdNode();


    static  QQmlComponent*      delegate(QQmlEngine& engine) noexcept;


    int value() const
    {
        return m_value;
    }
public slots:
    void setValue(int value)
    {
        if (m_value == value)
            return;

        m_value = value;

        emit valueChanged(m_value);

       // process();
    }
signals:
    void valueChanged(int value);
private:
    int m_value=128;

    // ProcessingNode interface
public slots:


    // ProcessingNode interface
public:

    // ProcessingNode interface
protected:
    void doProcess() override;

    // ProcessingNode interface
public slots:
    virtual void setInput(QMat *input) override;
};

#endif // PROCESSINGTHRESHOLDNODE_H
