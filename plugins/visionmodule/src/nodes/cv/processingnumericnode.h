#ifndef PROCESSINGNUMERICNODE_H
#define PROCESSINGNUMERICNODE_H

#include "processingnode.h"



class ProcessingNumericNode : public ProcessingNode
{
    Q_OBJECT

    Q_PROPERTY(double value READ value WRITE setValue NOTIFY valueChanged USER("serialize") REVISION 31)


public:
    ProcessingNumericNode();

      static  QQmlComponent*      delegate(QQmlEngine& engine) noexcept;

      // ProcessingNode interface
      double value() const
      {
          return m_value;
      }



public slots:
    void setInput(QMat *input) override;

    void setValue(double value)
    {
      if (qFuzzyCompare(m_value, value))
            return;

        m_value = value;
        emit valueChanged(m_value);
    }



signals:
    void valueChanged(double value);


protected:
    void doProcess() override;


private:
    double m_value=0;


    // JsonSerializable interface
public:
    void DeSerialize(QJsonObject &json) override;

    // FlowNode interface
public:
    
};

#endif // PROCESSINGNUMERICNODE_H
