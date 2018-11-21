#ifndef STRINGNODE_H
#define STRINGNODE_H

#include "flownode.h"

#include <QObject>

class StringNode : public FlowNode
{
    Q_OBJECT

    Q_PROPERTY(QString stringValue READ stringValue WRITE setStringValue NOTIFY stringValueChanged USER("serialize") REVISION 31)




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


signals:
    void stringValueChanged(QString stringValue);



private:
      QString m_stringValue="";



public:
      void Serialize(QJsonObject &json) override;
      void DeSerialize(QJsonObject &json) override;


};

#endif // STRINGNODE_H
