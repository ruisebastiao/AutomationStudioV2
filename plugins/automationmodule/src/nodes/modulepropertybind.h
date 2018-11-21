#ifndef MODULEPROPERTYBIND_H
#define MODULEPROPERTYBIND_H

#include "flownode.h"

#include <QObject>
#include <qautomationmodule.h>

class ModulePropertyBind : public FlowNode
{
    Q_OBJECT

    Q_PROPERTY(QVariant input READ input WRITE setInput NOTIFY inputChanged)
    Q_PROPERTY(FlowNodePort* inputPort READ inputPort WRITE setInputPort NOTIFY inputPortChanged)

    Q_PROPERTY(QStringList moduleProperties READ moduleProperties WRITE setModuleProperties NOTIFY modulePropertiesChanged)
    Q_PROPERTY(QString moduleProperty READ moduleProperty WRITE setModuleProperty NOTIFY modulePropertyChanged USER("serialize"))



public:
    ModulePropertyBind();

    static  QQmlComponent*      delegate(QQmlEngine& engine) noexcept;

    QVariant input() const
    {
        return m_input;
    }

    FlowNodePort* inputPort() const
    {
        return m_inputPort;
    }



public slots:
    void setInput(QVariant input)
    {

        m_input = input;
        emit inputChanged(m_input);
    }

    void setInputPort(FlowNodePort* inputPort)
    {
        if (m_inputPort == inputPort)
            return;

        m_inputPort = inputPort;
        emit inputPortChanged(m_inputPort);
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
    }

signals:
    void inputChanged(QVariant input);

    void inputPortChanged(FlowNodePort* inputPort);

    void modulePropertiesChanged(QStringList moduleProperties);

    void modulePropertyChanged(QString moduleProperty);

    void bindModuleProperty(QAutomationModule* moduleObject,QString moduleProperty);

private:

    QVariant m_input=QVariant::fromValue(false);
    FlowNodePort* m_inputPort=nullptr;
    QAutomationModule* m_module=nullptr;

    // JsonSerializable interface
    QStringList m_moduleProperties;

    QString m_moduleProperty="";

public:
    virtual void Serialize(QJsonObject &json) override;
    virtual void DeSerialize(QJsonObject &json) override;
    QAutomationModule *module() const;
    void setModule(QAutomationModule *module);
    QStringList moduleProperties() const
    {
        return m_moduleProperties;
    }
    QString moduleProperty() const
    {
        return m_moduleProperty;
    }

    // FlowNode interface
public:
    void initializePorts() override;
};

#endif // MODULEPROPERTYBIND_H
