#include "subproject.h"

SubProject::SubProject()
{

}

void SubProject::Serialize(QJsonObject &json)
{

    JsonSerializable::Serialize(json,this);
}

void SubProject::DeSerialize(QJsonObject &json)
{
    JsonSerializable::DeSerialize(json,this);
}
