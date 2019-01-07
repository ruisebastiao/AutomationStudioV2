#ifndef SUBPROJECT_H
#define SUBPROJECT_H

#include <jsonserializable.h>
#include <qobject.h>



class SubProject: public QObject, public JsonSerializable
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged  USER("serialize"))
    Q_PROPERTY(bool isDefault READ isDefault WRITE setIsDefault NOTIFY isDefaultChanged  USER("serialize"))
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged   USER("serialize"))



public:
    SubProject();

    QString name() const
    {
        return m_name;
    }

    bool isDefault() const
    {
        return m_isDefault;
    }

    int id() const
    {
        return m_id;
    }

public slots:
    void setName(QString name)
    {
        if (m_name == name)
            return;

        m_name = name;
        emit nameChanged(m_name);
    }

    void setIsDefault(bool isDefault)
    {
        if (m_isDefault == isDefault)
            return;

        m_isDefault = isDefault;
        emit isDefaultChanged(m_isDefault);
    }

    void setId(int id)
    {
        if (m_id == id)
            return;

        m_id = id;
        emit idChanged(m_id);
    }

signals:
    void nameChanged(QString name);

    void isDefaultChanged(bool isDefault);

    void idChanged(int id);

private:
    QString m_name="New Subproject";
    bool m_isDefault=false;
    int m_id=-1;

    // JsonSerializable interface
public:
    void Serialize(QJsonObject &json) override;
    void DeSerialize(QJsonObject &json) override;
};

#endif // SUBPROJECT_H
