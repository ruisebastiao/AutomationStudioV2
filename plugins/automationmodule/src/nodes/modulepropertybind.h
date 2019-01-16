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
    ~ModulePropertyBind() override;

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

        disconnect(out_connection);
        disconnect(in_connection);


        QString signalname=m_moduleProperty+"Changed(QVariant)";
        int index =m_module->metaObject()->indexOfSignal(QMetaObject::normalizedSignature(qPrintable(signalname)));


        if (index == -1) {
            LOG_WARNING()<<"Wrong signal name:"+signalname + " in node:"<<m_module;

        }

        QMetaMethod signal = m_module->metaObject()->method(index);


        QString propname="output";
        propname.replace(0,1,propname.at(0).toUpper());
        QString slotname="set"+propname+"(QVariant)";

        index = this->metaObject()->indexOfSlot(QMetaObject::normalizedSignature(qPrintable(slotname)));
        if (index == -1) {
            LOG_WARNING()<<"Wrong slot name:"+slotname+ " in node:"<<this;

        }

        QMetaMethod targetmethod=this->metaObject()->method(index);
        out_connection=connect(m_module, signal, this,targetmethod);




        signalname=QString("input")+QString("Changed(QVariant)");

        index =this->metaObject()->indexOfSignal(QMetaObject::normalizedSignature(qPrintable(signalname)));


        if (index == -1) {
            LOG_WARNING()<<"Wrong signal name:"+signalname + " in node:"<<this;

        }

        signal = this->metaObject()->method(index);


        propname=m_moduleProperty;
        propname.replace(0,1,propname.at(0).toUpper());
        slotname="set"+propname+"(QVariant)";

        index = m_module->metaObject()->indexOfSlot(QMetaObject::normalizedSignature(qPrintable(slotname)));
        if (index == -1) {
            LOG_WARNING()<<"Wrong slot name:"+slotname+ " in node:"<<this;

        }

        targetmethod=m_module->metaObject()->method(index);
        out_connection=connect(this, signal, m_module,targetmethod);






        //emit bindModuleProperty(m_module,m_moduleProperty);
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

//    void bindModuleProperty(QAutomationModule* moduleObject,QString moduleProperty);

    void outputChanged(QVariant output);

private:

    QMetaObject::Connection in_connection,out_connection;

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
