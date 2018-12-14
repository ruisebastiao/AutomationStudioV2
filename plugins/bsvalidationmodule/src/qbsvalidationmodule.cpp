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




//void QBSValidationModule::loadModuleSettings(QString path)
//{
//    qDebug()<<"Loading BSValidation module";
//    QAutomationModule::loadModuleSettings(path);
//}


//void QBSValidationModule::save()
//{
//    QAutomationModule::save();
//}

FlowNode *QBSValidationModule::createModuleNode(QString nodetype)
{


    qan::Node* newnode=nullptr;

    if(nodetype=="BSValidationNode"){
        newnode=m_graphView->getGraph()->insertNode<BSValidationNode>(nullptr);
    }
    else{
        LOG_WARNING(QString("Unknown module node type:%1").arg(nodetype));
    }



    return  dynamic_cast<FlowNode*>(newnode);

}
