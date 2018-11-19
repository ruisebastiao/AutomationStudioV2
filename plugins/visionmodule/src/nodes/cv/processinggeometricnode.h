#ifndef PROCESSINGGEOMETRICNODE_H
#define PROCESSINGGEOMETRICNODE_H

#include "processingnode.h"



class ProcessingGeometricNode : public ProcessingNode
{
    Q_OBJECT


    Q_PROPERTY(QVariant input1 READ input1 WRITE setInput1 NOTIFY input1Changed)
    Q_PROPERTY(FlowNodePort* input1Port READ input1Port WRITE setInput1Port NOTIFY input1PortChanged USER("serialize"))

    Q_PROPERTY(QVariant input2 READ input2 WRITE setInput2 NOTIFY input2Changed)
    Q_PROPERTY(FlowNodePort* input2Port READ input2Port WRITE setInput2Port NOTIFY input2PortChanged USER("serialize"))

private:

    QVariant m_input1;

    FlowNodePort* m_input1Port=nullptr;

    QVariant m_input2;

    FlowNodePort* m_input2Port=nullptr;


public:
    ProcessingGeometricNode();

    // ProcessingNode interface
public slots:
    void setInput(QMat *input) override;

    void setInput1(QVariant input1)
    {
        if (m_input1 == input1)
            return;

        m_input1 = input1;
        emit input1Changed(m_input1);
    }

    void setInput1Port(FlowNodePort* input1Port)
    {
        if (m_input1Port == input1Port)
            return;

        m_input1Port = input1Port;
        emit input1PortChanged(m_input1Port);
    }

    void setInput2(QVariant input2)
    {
        if (m_input2 == input2)
            return;

        m_input2 = input2;
        emit input2Changed(m_input2);
    }

    void setInput2Port(FlowNodePort* input2Port)
    {
        if (m_input2Port == input2Port)
            return;

        m_input2Port = input2Port;
        emit input2PortChanged(m_input2Port);
    }

protected:
    void doProcess() override;

    // JsonSerializable interface
public:
    void DeSerialize(QJsonObject &json) override;
    static  QQmlComponent *delegate(QQmlEngine &engine)noexcept;
    QVariant input1() const
    {
        return m_input1;
    }
    FlowNodePort* input1Port() const
    {
        return m_input1Port;
    }

    QVariant input2() const
    {
        return m_input2;
    }

    FlowNodePort* input2Port() const
    {
        return m_input2Port;
    }

signals:
    void input1Changed(QVariant input1);
    void input1PortChanged(FlowNodePort* input1Port);
    void input2Changed(QVariant input2);
    void input2PortChanged(FlowNodePort* input2Port);
};

#endif // PROCESSINGGEOMETRICNODE_H
