#ifndef MODULE_H
#define MODULE_H

#include "automationstudiocoreglobal.h"

#include "jsonserializable.h"

#include <QObject>

class AUTOMATIONSTUDIO_CORE_EXPORT Module : public QObject, public JsonSerializable
{
    Q_OBJECT

    Q_PROPERTY(QString settingFile READ settingFile WRITE setSettingFile NOTIFY settingFileChanged  USER("serialize"))
    Q_PROPERTY(QString moduleInstance READ moduleInstance WRITE setModuleInstanceFile NOTIFY moduleInstanceChanged  USER("serialize"))
    Q_PROPERTY(QString moduleType READ moduleType WRITE setModuleType NOTIFY moduleTypeChanged  USER("serialize"))
    Q_PROPERTY(int moduleID READ moduleID WRITE setModuleID NOTIFY moduleIDChanged  USER("serialize"))



public:
    explicit Module(QObject *parent = nullptr);

    QString settingFile() const
    {
        return m_settingFile;
    }

    QString moduleInstance() const
    {
        return m_moduleInstance;
    }

    QString moduleType() const
    {
        return m_moduleType;
    }

signals:

    void settingFileChanged(QString settingFile);

    void moduleInstanceChanged(QString moduleInstance);

    void moduleTypeChanged(QString moduleType);

    void moduleIDChanged(int moduleID);

public slots:

    void setSettingFile(QString settingFile)
    {
        if (m_settingFile == settingFile)
            return;

        m_settingFile = settingFile;
        emit settingFileChanged(m_settingFile);
    }


    void setModuleID(int moduleID)
    {
        if (m_moduleID == moduleID)
            return;

        m_moduleID = moduleID;
        emit moduleIDChanged(m_moduleID);
    }

private:

    void setModuleInstanceFile(QString moduleInstance)
    {
        if (m_moduleInstance == moduleInstance)
            return;

        m_moduleInstance = moduleInstance;
        emit moduleInstanceChanged(m_moduleInstance);
    }

    void setModuleType(QString moduleType)
    {
        if (m_moduleType == moduleType)
            return;

        m_moduleType = moduleType;
        emit moduleTypeChanged(m_moduleType);
    }

    QString m_settingFile="";
    QString m_moduleInstance="";
    QString m_moduleType="";

    // JsonSerializable interface
    int m_moduleID=-1;

public:
    void Serialize(QJsonObject &json) override;
    void DeSerialize(QJsonObject &json) override;
    int moduleID() const
    {
        return m_moduleID;
    }
};

#endif // MODULE_H
