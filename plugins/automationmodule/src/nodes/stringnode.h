#ifndef STRINGNODE_H
#define STRINGNODE_H

#include "flownode.h"

#include <QObject>

class StringNode : public FlowNode
{
    Q_OBJECT

    Q_PROPERTY(QString stringValue READ stringValue WRITE setStringValue NOTIFY stringValueChanged USER("serialize"))
    Q_PROPERTY(FlowNodePort* stringValuePort READ stringValuePort WRITE setStringValuePort NOTIFY stringValuePortChanged USER("serialize"))



public:
    StringNode();
    static  QQmlComponent*      delegate(QQmlEngine& engine) noexcept;

    QString stringValue() const
    {
        return m_stringValue;
    }
public slots:
    void setStringValue(QString stringValue)
    {

        m_stringValue = stringValue;
        emit stringValueChanged(m_stringValue);
    }
    void setStringValuePort(FlowNodePort* stringValuePort)
    {
        if (m_stringValuePort == stringValuePort)
            return;

        m_stringValuePort = stringValuePort;
        emit stringValuePortChanged(m_stringValuePort);
    }

signals:
    void stringValueChanged(QString stringValue);

    // FlowNode interface
    void stringValuePortChanged(FlowNodePort* stringValuePort);

public:

FlowNodePort* stringValuePort() const
{
    return m_stringValuePort;
}

private:
      QString m_stringValue="";

      // JsonSerializable interface
      FlowNodePort* m_stringValuePort=nullptr;

public:
      void Serialize(QJsonObject &json) override;
      void DeSerialize(QJsonObject &json) override;
};

#endif // STRINGNODE_H
