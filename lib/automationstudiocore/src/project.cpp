#include "project.h"

#include <QJsonArray>


Project::Project(QObject *parent):QObject(parent)
{

    m_modules= new ModuleListModel();

}

void Project::Serialize(QJsonObject &json)
{
    JsonSerializable::Serialize(json,this);
}

void Project::DeSerialize(QJsonObject &json)
{
    JsonSerializable::DeSerialize(json,this);
    QJsonArray modulesArray = json["modules"].toArray();
    for (int projectIndex = 0; projectIndex < modulesArray.size(); ++projectIndex) {
        QJsonObject moduleObject = modulesArray[projectIndex].toObject();

        Module *module= new Module(this);
        module->DeSerialize(moduleObject);

        m_modules->AddModule(module);

    }

}



