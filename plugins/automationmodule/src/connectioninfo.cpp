#include "connectioninfo.h"

ConnectionInfo::ConnectionInfo()
{

}

void ConnectionInfo::Serialize(QJsonObject &json)
{
    JsonSerializable::Serialize(json,this);
}

void ConnectionInfo::DeSerialize(QJsonObject &json)
{
     JsonSerializable::DeSerialize(json,this);
}
