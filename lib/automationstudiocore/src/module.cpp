#include "module.h"

Module::Module(QObject *parent) : QObject(parent)
{

}

void Module::Serialize(QJsonObject &json)
{
    JsonSerializable::Serialize(json,this);
}

void Module::DeSerialize(QJsonObject &json)
{
    JsonSerializable::DeSerialize(json,this);
}
