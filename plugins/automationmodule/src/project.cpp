#include "project.h"
#include "automationmodule_plugin.h"



Project::Project(QObject *parent):QObject(parent)
{

    m_modules= new ModuleListModel();

}

Project::~Project()
{
    m_modules->deleteLater();
}



QAutomationModule* Project::createModule(QString moduleName)
{


    UniqueQQmlComponentPtr delegate=UniqueQQmlComponentPtr(new QQmlComponent(AutomationModulePlugin::engine, "qrc:///AutomationModules/"+moduleName+"Item.qml"));
    QQmlComponent* component=delegate.get();



    QObject *component_object = component->create();

    if(component->isError()){
        foreach (QQmlError error, component->errors()) {
            LOG_ERROR()<<error;
        }
    }


    QQuickItem *item = qobject_cast<QQuickItem*>(component_object);

    QAutomationModule *module= qobject_cast<QAutomationModule*>(component_object);
    if(module){
        m_modules->AddItem(module);
    }


    return module;
}


void Project::Serialize(QJsonObject &json)
{
    JsonSerializable::Serialize(json,this);


    QJsonArray modulesArray;

    for (int var = 0; var < m_modules->length(); ++var) {
        QAutomationModule* module=m_modules->at(var);
        QJsonObject moduleObject;
        module->Serialize(moduleObject);
        modulesArray.append(moduleObject);
    }

    json["modules"]=modulesArray;

}

void Project::DeSerialize(QJsonObject &json)
{
    JsonSerializable::DeSerialize(json,this);
    QJsonArray modulesArray = json["modules"].toArray();
    for (int projectIndex = 0; projectIndex < modulesArray.size(); ++projectIndex) {
        QJsonObject moduleObject = modulesArray[projectIndex].toObject();

        QString moduleType=moduleObject["type"].toString();
        QAutomationModule *module=createModule(moduleType);

        if(module){

            module->DeSerialize(moduleObject);


            QJsonArray nodesArray = moduleObject["flowNodes"].toArray();
            for (int nodeIndex = 0; nodeIndex < nodesArray.size(); ++nodeIndex) {
                QJsonObject nodeObject = nodesArray[nodeIndex].toObject();

                        FlowNode* node=nullptr;

                        node=module->readNode(nodeObject);

                        if(node){

                            module->flowNodes()->AddItem(node);

                        }


            }
            module->loadConnections();

        }

    }
}


