#ifndef PROPERTYINFO_H
#define PROPERTYINFO_H

#include <QObject>
#include <jsonserializable.h>



class ProperyInfo:public QObject, public JsonSerializable
{
    Q_OBJECT
    Q_INTERFACES(JsonSerializable)


    Q_PROPERTY(QString propertyName READ propertyName WRITE setPropertyName NOTIFY propertyNameChanged USER("serialize"))
    Q_PROPERTY(QString propertyValue READ propertyValue WRITE setPropertyValue NOTIFY propertyValueChanged USER("serialize"))

public:
    ProperyInfo();
    ProperyInfo(QString propertyName,QString propertyValue);

    QString propertyName() const
    {
        return m_propertyName;
    }

    QString propertyValue() const
    {
        return m_propertyValue;
    }

public slots:
    void setPropertyName(QString propertyName)
    {
        if (m_propertyName == propertyName)
            return;

        m_propertyName = propertyName;
        emit propertyNameChanged(m_propertyName);
    }

    void setPropertyValue(QString propertyValue)
    {
        if (m_propertyValue == propertyValue)
            return;

        m_propertyValue = propertyValue;
        emit propertyValueChanged(m_propertyValue);
    }

signals:
    void propertyNameChanged(QString propertyName);

    void propertyValueChanged(QString propertyValue);

private:

    QString m_propertyName="";
    QString m_propertyValue="";

    // JsonSerializable interface
public:
    void Serialize(QJsonObject &json) override;
    void DeSerialize(QJsonObject &json) override;
};

#endif // PROPERTYINFO_H
