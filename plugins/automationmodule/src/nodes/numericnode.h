#ifndef NUMERICNODE_H
#define NUMERICNODE_H

#include "flownode.h"



class NumericNode : public FlowNode
{
    Q_OBJECT

    Q_PROPERTY(double numericValue READ numericValue WRITE setNumericValue NOTIFY numericValueChanged USER("serialize") REVISION 31)


public:
    NumericNode();

      static  QQmlComponent*      delegate(QQmlEngine& engine) noexcept;

      // ProcessingNode interface
      double numericValue() const
      {
          return m_numericValue;
      }



public slots:

    void setNumericValue(double value)
    {


        m_numericValue = value;
        emit numericValueChanged(m_numericValue);
    }



signals:
    void numericValueChanged(double value);



private:
    double m_numericValue=0.0;


    // JsonSerializable interface
public:
    void DeSerialize(QJsonObject &json) override;

    // FlowNode interface
public:
    

    // JsonSerializable interface
public:
    virtual void Serialize(QJsonObject &json) override;
};

#endif // PROCESSINGNUMERICNODE_H
