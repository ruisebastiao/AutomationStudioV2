#ifndef PROCESSINGLOGICALNODE_H
#define PROCESSINGLOGICALNODE_H

#include "processingnode.h"




class ProcessingLogicalNode : public ProcessingNode
{

    Q_OBJECT

    Q_PROPERTY(LogicalType logicalType READ logicalType WRITE setLogicalType NOTIFY logicalTypeChanged USER("serialize"))

    Q_PROPERTY(bool logicalInput1 READ logicalInput1 WRITE setLogicalInput1 NOTIFY logicalInput1Changed)
    Q_PROPERTY(FlowNodePort* logicalInput1Port READ logicalInput1Port WRITE setLogicalInput1Port NOTIFY logicalInput1PortChanged USER("serialize"))

    Q_PROPERTY(bool logicalInput2 READ logicalInput2 WRITE setLogicalInput2 NOTIFY logicalInput2Changed)
    Q_PROPERTY(FlowNodePort* logicalInput2Port READ logicalInput2Port WRITE setLogicalInput2Port NOTIFY logicalInput2PortChanged USER("serialize"))


    Q_PROPERTY(bool logicalOutput READ logicalOutput WRITE setLogicalOutput NOTIFY logicalOutputChanged)
    Q_PROPERTY(FlowNodePort* logicalOutputPort READ logicalOutputPort WRITE setLogicalOutputPort NOTIFY logicalOutputPortChanged USER("serialize"))




public:
    enum LogicalType {

        OR=0,
        AND

    };
    Q_ENUM(LogicalType )

    ProcessingLogicalNode();

    // ProcessingNode interface
    LogicalType logicalType() const
    {
        return m_logicalType;
    }

    bool logicalInput1() const
    {
        return m_logicalInput1;
    }

    FlowNodePort* logicalInput1Port() const
    {
        return m_logicalInput1Port;
    }

    bool logicalInput2() const
    {
        return m_logicalInput2;
    }

    FlowNodePort* logicalInput2Port() const
    {
        return m_logicalInput2Port;
    }

    bool logicalOutput() const
    {
        return m_logicalOutput;
    }

    FlowNodePort* logicalOutputPort() const
    {
        return m_logicalOutputPort;
    }

public slots:
    void setInput(QMat *input) override;

    void setLogicalType(LogicalType logicalType)
    {
        if (m_logicalType == logicalType)
            return;

        m_logicalType = logicalType;
        emit logicalTypeChanged(m_logicalType);
    }

    void setLogicalInput1(bool logicalInput1)
    {

        m_logicalInput1 = logicalInput1;
        emit logicalInput1Changed(m_logicalInput1);
        doProcess();
    }

    void setLogicalInput1Port(FlowNodePort* logicalInput1Port)
    {
        if (m_logicalInput1Port == logicalInput1Port)
            return;

        m_logicalInput1Port = logicalInput1Port;
        emit logicalInput1PortChanged(m_logicalInput1Port);
    }

    void setLogicalInput2(bool logicalInput2)
    {

        m_logicalInput2 = logicalInput2;
        emit logicalInput2Changed(m_logicalInput2);

        doProcess();        
    }

    void setLogicalInput2Port(FlowNodePort* logicalInput2Port)
    {
        if (m_logicalInput2Port == logicalInput2Port)
            return;

        m_logicalInput2Port = logicalInput2Port;
        emit logicalInput2PortChanged(m_logicalInput2Port);
    }

    void setLogicalOutputPort(FlowNodePort* logicalOutputPort)
    {
        if (m_logicalOutputPort == logicalOutputPort)
            return;

        m_logicalOutputPort = logicalOutputPort;
        emit logicalOutputPortChanged(m_logicalOutputPort);
    }

    void setLogicalOutput(bool logicalOutput)
    {


        m_logicalOutput = logicalOutput;
        if(m_logicalOutput){
            emit logicalOutputChanged(m_logicalOutput);
            m_logicalOutput=false;
            m_logicalInput1=false;
            m_logicalInput2=false;
        }

    }

signals:
    void logicalTypeChanged(LogicalType logicalType);

    void logicalInput1Changed(bool logicalInput1);

    void logicalInput1PortChanged(FlowNodePort* logicalInput1Port);

    void logicalInput2Changed(bool logicalInput2);

    void logicalInput2PortChanged(FlowNodePort* logicalInput2Port);

    void logicalOutputChanged(bool logicalOutput);

    void logicalOutputPortChanged(FlowNodePort* logicalOutputPort);

private:
    LogicalType m_logicalType=AND;

    bool m_logicalInput1=false;

    FlowNodePort* m_logicalInput1Port;

    bool m_logicalInput2=false;

    FlowNodePort* m_logicalInput2Port;

    bool m_logicalOutput=false;

    FlowNodePort* m_logicalOutputPort;

protected:
    void doProcess() override;

    // JsonSerializable interface
public:
    void DeSerialize(QJsonObject &json) override;
    static QQmlComponent *delegate(QQmlEngine &engine) noexcept;

    // FlowNode interface
public:
    void initializePorts() override;
};

#endif // PROCESSINGLOGICALNODE_H
