#ifndef USER_H
#define USER_H

#include "automationstudiocoreglobal.h"
#include "jsonserializable.h"

#include "QMetaEnum"
#include <QObject>
#include <QJsonObject>



class AUTOMATIONSTUDIO_CORE_EXPORT User : public QObject,public JsonSerializable
{
    Q_OBJECT


public:
    enum UserRole {
        ProductionRole=0,
        AdminRole=1
    };

    Q_ENUM(UserRole)

    explicit User(QObject *parent = nullptr);
    User(const User& other){ }

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged USER("serialize"))
    Q_PROPERTY(UserRole role READ role WRITE setRole NOTIFY roleChanged USER("serialize"))
    Q_PROPERTY(QString pin READ pin WRITE setPin NOTIFY pinChanged USER("serialize"))
    Q_PROPERTY(bool isDefault READ isDefault WRITE setIsDefault NOTIFY isDefaultChanged USER("serialize"))

    Q_PROPERTY(QString language READ language WRITE setLanguage NOTIFY languageChanged USER("serialize"))


    QString name() const
    {
        return m_name;
    }

    UserRole role() const
    {
        return m_role;
    }

    bool isDefault() const
    {
        return m_isDefault;
    }



    QString pin() const
    {
        return m_pin;
    }

signals:

    void nameChanged(QString name);

    void roleChanged(UserRole role);

    void isDefaultChanged(bool isDefault);

    void pinChanged(QString pin);

    void languageChanged(QString language);

public slots:
    void setName(QString name)
    {
        if (m_name == name)
            return;

        m_name = name;
        emit nameChanged(m_name);
    }
    void setRole(QString role)
    {


        auto userrole=QMetaEnum::fromType<UserRole>().keyToValue(role.toLatin1());

//        if (m_role == userrole)
//            return;

        m_role = static_cast<UserRole>(userrole);;
        emit roleChanged(m_role);
    }

    void setRole(UserRole role)
    {
        if (m_role == role)
            return;

        m_role = role;
        emit roleChanged(m_role);
    }

    void setIsDefault(bool isDefault)
    {
        if (m_isDefault == isDefault)
            return;

        m_isDefault = isDefault;
        emit isDefaultChanged(m_isDefault);
    }

    void setPin(QString pin)
    {
        if (m_pin == pin)
            return;

        m_pin = pin;
        emit pinChanged(m_pin);
    }

    void setLanguage(QString language)
    {
        if (m_language == language)
            return;

        m_language = language;
        emit languageChanged(m_language);
    }

private:
    QString m_name="";
    UserRole m_role=UserRole::ProductionRole;

    // Serialized interface
    bool m_isDefault=false;



    QString m_pin="0000";

    // JsonSerializable interface
    QString m_language="pt";

public:
    virtual void Serialize(QJsonObject &json) override;
virtual void DeSerialize(QJsonObject &json) override;
QString language() const
{
    return m_language;
}
};


#endif // USER_H
