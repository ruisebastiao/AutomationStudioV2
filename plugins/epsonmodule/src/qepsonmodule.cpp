#include "qepsonmodule.h"
#include "flownode.h"

#include <nodes/commandparsernode.h>
#include <nodes/commandsendernode.h>
#include <nodes/epsonnode.h>


QEpsonModule::QEpsonModule(QQuickItem *parent)
{

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



void QEpsonModule::loadModuleSettings(QString path)
{
    qDebug()<<"Loading Epson module";
    QAutomationModule::loadModuleSettings(path);
}

void QEpsonModule::save()
{
    QAutomationModule::save();
}


FlowNode *QEpsonModule::createModuleNode(qan::GraphView *graphView, QString nodetype)
{

    qan::Node* node=nullptr;


    if(nodetype=="EpsonNode"){
        node=graphView->getGraph()->insertNode<EpsonNode>(nullptr);
    }
    else if(nodetype=="CommandSenderNode"){
        node=graphView->getGraph()->insertNode<CommandSenderNode>(nullptr);


    }
    else if(nodetype=="CommandParserNode"){
        node=graphView->getGraph()->insertNode<CommandParserNode>(nullptr);


    }

    FlowNode* modulenode=dynamic_cast<FlowNode*>(node);
    if(modulenode==nullptr){

        LOG_WARNING(QString("Unknown EpsonModule node type:%1").arg(nodetype));

    }


    return  modulenode;
}
