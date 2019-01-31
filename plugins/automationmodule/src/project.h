#ifndef PROJECT_H
#define PROJECT_H

#include <QObject>
#include "automationmoduleglobal.h"
#include "jsonserializable.h"
#include "modulelistmodel.h"

#include <moduleproxynode.h>

class AUTOMATIONMODULE_EXPORT Project : public QObject, public JsonSerializable
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged  USER("serialize"))
    Q_PROPERTY(bool isDefault READ isDefault WRITE setIsDefault NOTIFY isDefaultChanged  USER("serialize"))
    Q_PROPERTY(ModuleListModel* modules READ modules NOTIFY modulesChanged)
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged   USER("serialize"))

    Q_PROPERTY(bool projectLocked READ projectLocked WRITE setProjectLocked NOTIFY projectLockedChanged)
    Q_PROPERTY(bool projectLoaded READ projectLoaded WRITE setProjectLoaded NOTIFY projectLoadedChanged)

    Q_PROPERTY(QVariantList subProjects READ subProjects WRITE setSubProjects NOTIFY subProjectsChanged USER("serialize"))
    Q_PROPERTY(QString subProjectName READ subProjectName WRITE setSubProjectName NOTIFY subProjectNameChanged)




public:
    explicit Project(QObject *parent = nullptr);
    Project(const Project& other){ }

//    Q_INVOKABLE void addSubProject(){
//        SubProject* subproject=new SubProject();
//        subproject->setId(m_subProjects->getAvailableID());
//        m_subProjects->addItem(subproject);
//    }

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

    void moduleLockedChanged(QVariant locked);



    void setProjectLocked(bool projectLocked)
    {
        if (m_projectLocked == projectLocked)
            return;

        m_projectLocked = projectLocked;
        emit projectLockedChanged(m_projectLocked);
    }

    void setProjectLoaded(bool projectLoaded)
    {
        if (m_projectLoaded == projectLoaded)
            return;

        m_projectLoaded = projectLoaded;
        emit projectLoadedChanged(m_projectLoaded);
    }

    void setSubProjects(QVariantList subProjects)
    {
        if (m_subProjects == subProjects)
            return;

        m_subProjects = subProjects;
        emit subProjectsChanged(m_subProjects);
    }

    void setSubProjectName(QString subProjectName)
    {
        if (m_subProjectName == subProjectName)
            return;

        m_subProjectName = subProjectName;
        emit subProjectNameChanged(m_subProjectName);
    }

signals:
    void nameChanged(QString name);

    void isDefaultChanged(bool isDefault);

    void modulesChanged(ModuleListModel* modules);

    void idChanged(int id);

    void deserialized();

    void extendedProjectNameChange(QString extendedProjectName);

    void projectLockedChanged(bool projectLocked);

    void projectLoadedChanged(bool projectLoaded);

    void subProjectsChanged(QVariantList subProjects);

    void subProjectNameChanged(QString subProjectName);

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
//    subProjectsListModel* subProjects() const
//    {
//        return m_subProjects;
//    }



    bool projectLocked() const
    {
        return m_projectLocked;
    }

    bool projectLoaded() const
    {
        return m_projectLoaded;
    }

    Q_INVOKABLE void load();
    Q_INVOKABLE void unload();
    QVariantList subProjects() const
    {
        return m_subProjects;
    }

    QString subProjectName() const
    {
        return m_subProjectName;
    }

    bool save() const;
    void setSave(bool save);

private:


    QString m_name="New Project";
    bool m_isDefault=false;
    ModuleListModel* m_modules=new ModuleListModel();
    int m_id=-1;
    QList<ModuleProxyNode*> moduleproxynodes;
    bool m_projectLocked=false;
    bool m_projectLoaded=false;

    QJsonArray m_modulesArray;
    QVariantList m_subProjects;
    QString m_subProjectName="";

    bool m_save=false;
};



#endif // PROJECT_H
