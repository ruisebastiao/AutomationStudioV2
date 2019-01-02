#include "project.h"
#include "automationmodule_plugin.h"

//#include <nodes/modulepropertybind.h>




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

//        this->connect(module->flowNodes(),&FlowNodeManager::flowNodeAdded,this,[&](FlowNode* node){

//            ModuleProxyNode* moduleproxynodeadded=dynamic_cast<ModuleProxyNode*>(node);
//            if(moduleproxynodeadded){


//                for (int moduleIndex = 0; moduleIndex < m_modules->length(); ++moduleIndex) {
//                    QAutomationModule* currentmodule=m_modules->at(moduleIndex);
//                    if(currentmodule){

//                        for (int nodeIndex = 0; nodeIndex < currentmodule->flowNodes()->length(); ++nodeIndex) {
//                            ModuleProxyNode* currentproxynode=dynamic_cast<ModuleProxyNode*>(currentmodule->flowNodes()->at(nodeIndex));

//                            if(currentproxynode && currentproxynode!=moduleproxynodeadded){

//                                 currentproxynode->flowNodes()->addItem(moduleproxynodeadded);


//                            }
//                        }




//                    }
//                }

//            }
//        });

        m_modules->addItem(module);
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
         QAutomationModule* module=createModule(moduleType);
         if(module){
             int moduleID=moduleObject["id"].toInt();
             module->setId(moduleID);
         }


    }

    for (int projectIndex = 0; projectIndex < modulesArray.size(); ++projectIndex) {
        QJsonObject moduleObject = modulesArray[projectIndex].toObject();

        int moduleID=moduleObject["id"].toInt();
//        QAutomationModule *module=createModule(moduleType);

        for (int var = 0; var < m_modules->length(); ++var) {
            QAutomationModule* module=m_modules->at(var);
            if(module && module->id()==moduleID){

                module->DeSerialize(moduleObject);

                break;


            }
        }



    }


}


