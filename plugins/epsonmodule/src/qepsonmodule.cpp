#include "qepsonmodule.h"
#include "flownode.h"

#include <nodes/commandparsernode.h>
#include <nodes/commandsendernode.h>
#include <nodes/epsonnode.h>


QEpsonModule::QEpsonModule(QQuickItem *parent)
{

    m_type=EpsonModule;
    m_moduleNodeTypes.append(getModuleNodeTypes());
    m_moduleName="Epson";
}


QVariantList QEpsonModule::getModuleNodeTypes() const
{
    QVariantList ret;

    QVariantMap map;

    map.insert(QVariant::fromValue(FlowNode::Type::EpsonNode).value<QString>(),"Epson");
    ret.append(map);
    map.clear();

    map.insert(QVariant::fromValue(FlowNode::Type::CommandSenderNode).value<QString>(),"Command Sender");
    ret.append(map);
    map.clear();

    map.insert(QVariant::fromValue(FlowNode::Type::CommandParserNode).value<QString>(),"Command Parser");
    ret.append(map);
    map.clear();

    return ret;
}


