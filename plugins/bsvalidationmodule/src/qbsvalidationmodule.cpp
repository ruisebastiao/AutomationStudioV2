#include "qbsvalidationmodule.h"

#include <nodes/bsvalidationnode.h>


QBSValidationModule::QBSValidationModule(QQuickItem* parent)
{
    m_type=ModuleType::BSValidationModule;
    m_moduleName="BSValidation";
    m_moduleNodeTypes.append(getModuleNodeTypes());

}


QVariantList QBSValidationModule::getModuleNodeTypes() const
{
    QVariantList ret;

    QVariantMap map;

    map.insert(QVariant::fromValue(FlowNode::Type::BSValidationNode).value<QString>(),"BS Validation");
    ret.append(map);
    map.clear();



    return ret;
}

