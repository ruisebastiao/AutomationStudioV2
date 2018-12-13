#include "user.h"


User::User(QObject *parent) : QObject(parent)
{

}

void User::Serialize(QJsonObject &json)
{
 JsonSerializable::Serialize(json,this);
}

void User::DeSerialize(QJsonObject &json)
{
    JsonSerializable::DeSerialize(json,this);
}


