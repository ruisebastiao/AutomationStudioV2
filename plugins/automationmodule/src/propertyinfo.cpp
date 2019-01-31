#include "propertyinfo.h"

ProperyInfo::ProperyInfo()
{

}

ProperyInfo::ProperyInfo(QString propertyName, QString propertyValue)
{
    setPropertyName(propertyName);
    setPropertyValue(propertyValue);
}

void ProperyInfo::Serialize(QJsonObject &json)
{
    JsonSerializable::Serialize(json,this);
}

void ProperyInfo::DeSerialize(QJsonObject &json)
{
    JsonSerializable::DeSerialize(json,this);
}
