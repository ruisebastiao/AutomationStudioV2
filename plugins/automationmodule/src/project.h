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



public:
    explicit Project(QObject *parent = nullptr);
    Project(const Project& other){ }

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

signals:
    void nameChanged(QString name);

    void isDefaultChanged(bool isDefault);

    void modulesChanged(ModuleListModel* modules);

    void idChanged(int id);

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
private:

    QString m_name="New Project";
    bool m_isDefault=false;
    ModuleListModel* m_modules=new ModuleListModel();
    int m_id=-1;
    QList<ModuleProxyNode*> moduleproxynodes;
};



#endif // PROJECT_H
