#ifndef PROCESSINGNUMERICNODE_H
#define PROCESSINGNUMERICNODE_H

#include "processingnode.h"



class ProcessingNumericNode : public ProcessingNode
{
    Q_OBJECT

    Q_PROPERTY(double value READ value WRITE setValue NOTIFY valueChanged USER("serialize"))
    Q_PROPERTY(FlowNodePort* valuePort READ valuePort WRITE setValuePort NOTIFY valuePortChanged USER("serialize"))


public:
    ProcessingNumericNode();

      static  QQmlComponent*      delegate(QQmlEngine& engine) noexcept;

      // ProcessingNode interface
      double value() const
      {
          return m_value;
      }

      FlowNodePort* valuePort() const
      {
          return m_valuePort;
      }

public slots:
    void setInput(QMat *input) override;

    void setValue(double value)
    {
        qWarning("Floating point comparison needs context sanity check");
        if (qFuzzyCompare(m_value, value))
            return;

        m_value = value;
        emit valueChanged(m_value);
    }

    void setValuePort(FlowNodePort* valuePort)
    {
        if (m_valuePort == valuePort)
            return;

        m_valuePort = valuePort;
        emit valuePortChanged(m_valuePort);
    }

signals:
    void valueChanged(double value);

    void valuePortChanged(FlowNodePort* valuePort);

protected:
    void doProcess() override;

private:
    double m_value=0;
    FlowNodePort* m_valuePort=nullptr;

    // JsonSerializable interface
public:
    void DeSerialize(QJsonObject &json) override;

    // FlowNode interface
public:
    void initializePorts() override;
};

#endif // PROCESSINGNUMERICNODE_H
