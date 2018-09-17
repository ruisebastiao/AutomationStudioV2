#include "user.h"


User::User(QObject *parent) : QObject(parent)
{

}


void User::write(QJsonObject &json) const
{
}

void User::read(QJsonObject &json)
{
    if(json.contains("name")){
        setName(json["name"].toString());
    }

    if(json.contains("role")){
        setRole(json["role"].toString());
    }

    m_pin=json["pin"].toString();
    m_isDefault=json["default"].toBool();
}

