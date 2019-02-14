#include "propertyinfo.h"

#include <QQmlEngine>

ProperyInfo::ProperyInfo()
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership );
}

ProperyInfo::~ProperyInfo()
{

    LOG_INFO()<<"Property info deleted";
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
