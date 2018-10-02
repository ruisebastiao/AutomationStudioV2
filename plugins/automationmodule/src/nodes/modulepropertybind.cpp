#include "modulepropertybind.h"

ModulePropertyBind::ModulePropertyBind()
{
    m_type=Type::ModulePropertyBind;
}

QQmlComponent *ModulePropertyBind::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/ModulePropertyBindNodeItem.qml"));
    return delegate.get();
}

QAutomationModule *ModulePropertyBind::module() const
{
    return m_module;
}

void ModulePropertyBind::setModule(QAutomationModule *module)
{
    m_module = module;

}

void ModulePropertyBind::Serialize(QJsonObject &json)
{
    FlowNode::Serialize(json);
}

void ModulePropertyBind::DeSerialize(QJsonObject &json)
{

    m_inputPort=new FlowNodePort(this,qan::PortItem::Type::In,"input");

    m_inPorts.append(m_inputPort);

    FlowNode::DeSerialize(json);

    if(m_module){

        m_moduleProperties.clear();
        for (int i = 0; i < m_module->metaObject()->propertyCount(); i++)
        {

            QMetaProperty property = m_module->metaObject()->property(i);
            const char* propName=property.name();


            if(property.isReadable() && property.isWritable() && property.revision()==2){


                m_moduleProperties.append(propName);

            }


        }
        emit modulePropertiesChanged(m_moduleProperties);

        emit bindModuleProperty(m_module,m_moduleProperty);
        //connect(this,)

    }
}
