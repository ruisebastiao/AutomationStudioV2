#ifndef PROJECT_H
#define PROJECT_H

#include <QObject>
#include "automationstudiocoreglobal.h"
#include "jsonserializable.h"
#include "modulelistmodel.h"


class AUTOMATIONSTUDIO_CORE_EXPORT Project : public QObject, public JsonSerializable
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged  USER("serialize"))
    Q_PROPERTY(bool isDefault READ isDefault WRITE setIsDefault NOTIFY isDefaultChanged  USER("serialize"))
    Q_PROPERTY(ModuleListModel* modules READ modules WRITE setModules NOTIFY modulesChanged)



public:
    explicit Project(QObject *parent = nullptr);
    Project(const Project& other){ }
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

signals:
    void nameChanged(QString name);

    void isDefaultChanged(bool isDefault);

    void modulesChanged(ModuleListModel* modules);

public:
    void Serialize(QJsonObject &json) override;
    void DeSerialize(QJsonObject &json) override;

    ModuleListModel* modules() const
    {
        return m_modules;
    }

private:

    QString m_name="";
    bool m_isDefault=false;
    ModuleListModel* m_modules=nullptr;
};



#endif // PROJECT_H
