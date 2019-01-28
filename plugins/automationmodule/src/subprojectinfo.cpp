#include "subprojectinfo.h"

SubProjectInfo::SubProjectInfo()
{

}

SubProjectInfo::SubProjectInfo(QString id, QString projectname)
{
    setId(id);
    setProjectName(projectname);
}

void SubProjectInfo::Serialize(QJsonObject &json)
{
    JsonSerializable::Serialize(json,this);
}

void SubProjectInfo::DeSerialize(QJsonObject &json)
{
    JsonSerializable::DeSerialize(json,this);
}
