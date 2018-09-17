#ifndef USER_H
#define USER_H

#include "automationstudiocoreglobal.h"

#include "QMetaEnum"
#include <QObject>
#include <QJsonObject>



class AUTOMATIONSTUDIO_CORE_EXPORT User : public QObject
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

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(UserRole role READ role WRITE setRole NOTIFY roleChanged)
    Q_PROPERTY(QString pin READ pin WRITE setPin NOTIFY pinChanged)
    Q_PROPERTY(bool isDefault READ isDefault WRITE setIsDefault NOTIFY isDefaultChanged)

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


    void write(QJsonObject &json) const;
    void read(QJsonObject &json);


    QString pin() const
    {
        return m_pin;
    }

signals:

    void nameChanged(QString name);

    void roleChanged(UserRole role);

    void isDefaultChanged(bool isDefault);

    void pinChanged(QString pin);

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

        if (m_role == userrole)
            return;

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

private:
    QString m_name="";
    UserRole m_role=UserRole::ProductionRole;

    // Serialized interface
    bool m_isDefault=false;



    QString m_pin="0000";
};


#endif // USER_H
