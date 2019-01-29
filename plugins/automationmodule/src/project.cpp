#include "project.h"
#include "automationmodule_plugin.h"

#include <nodes/modulepropertybind.h>



Project::Project(QObject *parent):QObject(parent)
{

    m_modules= new ModuleListModel();

}

Project::~Project()
{
    qDebug()<<"Deleting project";
    unload();
}

void Project::moduleLockedChanged(QVariant locked)
{

    for (int var = 0; var < this->modules()->length(); ++var) {
        QAutomationModule* module=modules()->at(var);
        if(module->locked().value<bool>()){
            setProjectLocked(true);
            return;
        }
    }
    setProjectLocked(false);
}



QAutomationModule* Project::createModule(QString moduleName,bool setID)
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
        module->setParentProject(this);

        connect(module,&QAutomationModule::lockedChanged,this,&Project::moduleLockedChanged);

        m_modules->addItem(module);
    }

    if(setID){
        module->setId(m_modules->getAvailableID());
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
    m_modulesArray= json["modules"].toArray();

}

void Project::load(){


    for (int projectIndex = 0; projectIndex < m_modulesArray.size(); ++projectIndex) {
        QJsonObject moduleObject = m_modulesArray[projectIndex].toObject();

        QString moduleType=moduleObject["type"].toString();
        QAutomationModule *module=createModule(moduleType,false);

        if(module){
            module->DeSerialize(moduleObject);
        }

    }

    for (int moduleIndex = 0; moduleIndex < m_modules->length(); ++moduleIndex) {
        QAutomationModule *module=m_modules->at(moduleIndex);

        module->initializeModuleProxyNodes();
        module->initializeProjectNodes();

    }


    for (int var = 0; var < subProjects()->length(); ++var) {
        SubProject* subproject=subProjects()->at(var);

        if(m_selectedSubproject && m_selectedSubproject->id()==subproject->id()){
            setSelectedSubproject(subproject);
            break;
        }
        else if(subproject->isDefault()){
            setSelectedSubproject(subproject);
            break;
        }
    }


    this->setProjectLoaded(true);
}

void Project::unload()
{

    qDebug()<<"Deleting project";
    m_modules->clear();
}

void Project::DeSerialize(QJsonObject &json)
{
    JsonSerializable::DeSerialize(json,this);
    m_modulesArray= json["modules"].toArray();

}


