#ifndef MODULEPROPERTYBIND_H
#define MODULEPROPERTYBIND_H

#include "flownode.h"

#include <QObject>
#include <qautomationmodule.h>

class ModulePropertyBind : public FlowNode
{
    Q_OBJECT

    Q_PROPERTY(QVariant input READ input WRITE setInput NOTIFY inputChanged REVISION 30)
    Q_PROPERTY(QVariant output READ output WRITE setOutput NOTIFY outputChanged REVISION 31)


    Q_PROPERTY(QStringList moduleProperties READ moduleProperties WRITE setModuleProperties NOTIFY modulePropertiesChanged)
    Q_PROPERTY(QString moduleProperty READ moduleProperty WRITE setModuleProperty NOTIFY modulePropertyChanged USER("serialize"))



public:
    ModulePropertyBind();

    static  QQmlComponent*      delegate(QQmlEngine& engine) noexcept;

    QVariant input() const
    {
        return m_input;
    }



public slots:
    void setInput(QVariant input)
    {

        m_input = input;
        emit inputChanged(m_input);
    }


    void setModuleProperties(QStringList moduleProperties)
    {
        if (m_moduleProperties == moduleProperties)
            return;

        m_moduleProperties = moduleProperties;
        emit modulePropertiesChanged(m_moduleProperties);
    }

    void setModuleProperty(QString moduleProperty)
    {
        if (m_moduleProperty == moduleProperty)
            return;

        m_moduleProperty = moduleProperty;

        emit modulePropertyChanged(m_moduleProperty);

        emit bindModuleProperty(m_module,m_moduleProperty);
    }

    void setOutput(QVariant output)
    {

        m_output = output;
        emit outputChanged(m_output);
    }

signals:
    void inputChanged(QVariant input);



    void modulePropertiesChanged(QStringList moduleProperties);

    void modulePropertyChanged(QString moduleProperty);

    void bindModuleProperty(QAutomationModule* moduleObject,QString moduleProperty);

    void outputChanged(QVariant output);

private:

    QVariant m_input=QVariant::fromValue(false);

    QAutomationModule* m_module=nullptr;

    // JsonSerializable interface
    QStringList m_moduleProperties;

    QString m_moduleProperty="";

    QVariant m_output;

public:
    virtual void Serialize(QJsonObject &json) override;
    virtual void DeSerialize(QJsonObject &json) override;
    QAutomationModule *module() const;
    void setModule(QAutomationModule *module);
    QStringList moduleProperties() const
    {
        return m_moduleProperties;
    }
    QString moduleProperty()
    {
        return m_moduleProperty;
    }

    // FlowNode interface
public:
    
    QVariant output() const
    {
        return m_output;
    }
};

#endif // MODULEPROPERTYBIND_H
