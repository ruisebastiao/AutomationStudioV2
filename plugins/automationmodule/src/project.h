#ifndef PROJECT_H
#define PROJECT_H

#include <QObject>
#include "automationmoduleglobal.h"
#include "jsonserializable.h"
#include "modulelistmodel.h"
#include "subprojectslistmodel.h"
#include <moduleproxynode.h>

class AUTOMATIONMODULE_EXPORT Project : public QObject, public JsonSerializable
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged  USER("serialize"))
    Q_PROPERTY(bool isDefault READ isDefault WRITE setIsDefault NOTIFY isDefaultChanged  USER("serialize"))
    Q_PROPERTY(ModuleListModel* modules READ modules NOTIFY modulesChanged)
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged   USER("serialize"))
    Q_PROPERTY(subProjectsListModel* subProjects READ subProjects WRITE setSubProjects NOTIFY subProjectsChanged  USER("serialize"))
    Q_PROPERTY(SubProject* selectedSubproject READ selectedSubproject WRITE setSelectedSubproject NOTIFY selectedSubprojectChanged)

    Q_PROPERTY(QString extendedProjectName READ extendedProjectName WRITE setExtendedProjectName NOTIFY extendedProjectNameChange REVISION 2)





public:
    explicit Project(QObject *parent = nullptr);
    Project(const Project& other){ }

    Q_INVOKABLE void addSubProject(){
        SubProject* subproject=new SubProject();
        subproject->setId(m_subProjects->getAvailableID());
        m_subProjects->addItem(subproject);
    }

    virtual ~Project() override;

    QString name() const
    {
        return m_name;
    }

    bool isDefault() const
    {
        return m_isDefault;
    }

public slots:

    // JsonSerializable interface
    void setName(QString name)
    {
        if (m_name == name)
            return;

        m_name = name;
        emit nameChanged(m_name);
        if(!m_selectedSubproject){
            setExtendedProjectName(m_name);
        }

    }

    void setIsDefault(bool isDefault)
    {
        if (m_isDefault == isDefault)
            return;

        m_isDefault = isDefault;
        emit isDefaultChanged(m_isDefault);
    }

    void setModules(ModuleListModel* modules)
    {
        if (m_modules == modules)
            return;

        m_modules = modules;
        emit modulesChanged(m_modules);
    }

    void setId(int id)
    {
        if (m_id == id)
            return;

        m_id = id;
        emit idChanged(m_id);
    }

    void setSubProjects(subProjectsListModel* subProjects)
    {
        if (m_subProjects == subProjects)
            return;

        m_subProjects = subProjects;
        emit subProjectsChanged(m_subProjects);
    }

    void setSelectedSubproject(SubProject* selectedSubproject)
    {
        if (m_selectedSubproject == selectedSubproject)
            return;

        m_selectedSubproject = selectedSubproject;


        emit selectedSubprojectChanged(m_selectedSubproject);
        if(m_selectedSubproject){
                setExtendedProjectName(m_selectedSubproject->name());
        }
        else{
            setExtendedProjectName(name());
        }
    }




signals:
    void nameChanged(QString name);

    void isDefaultChanged(bool isDefault);

    void modulesChanged(ModuleListModel* modules);

    void idChanged(int id);

    void subProjectsChanged(subProjectsListModel* subProjects);

    void selectedSubprojectChanged(SubProject* selectedSubproject);

    void deserialized();

    void extendedProjectNameChange(QString extendedProjectName);

public:
    void Serialize(QJsonObject &json) override;
    void DeSerialize(QJsonObject &json) override;

    ModuleListModel* modules() const
    {
        return m_modules;
    }

    int id() const
    {
        return m_id;
    }

    Q_INVOKABLE QAutomationModule *createModule(QString moduleName, bool setID=true);
    subProjectsListModel* subProjects() const
    {
        return m_subProjects;
    }

    SubProject* selectedSubproject() const
    {
        return m_selectedSubproject;
    }

    QString extendedProjectName() const
    {
        return m_extendedProjectName;
    }

private:


    void setExtendedProjectName(QString extendedProjectName)
    {
        if (m_extendedProjectName == extendedProjectName)
            return;

        m_extendedProjectName = extendedProjectName;


        emit extendedProjectNameChange(m_extendedProjectName);
    }

    QString m_name="New Project";
    bool m_isDefault=false;
    ModuleListModel* m_modules=new ModuleListModel();
    int m_id=-1;
    QList<ModuleProxyNode*> moduleproxynodes;
    subProjectsListModel* m_subProjects = new subProjectsListModel();
    SubProject* m_selectedSubproject=nullptr;
    QString m_extendedProjectName;
};



#endif // PROJECT_H
