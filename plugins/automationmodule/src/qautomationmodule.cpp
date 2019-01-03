#include "qautomationmodule.h"


#include <QtConcurrent>
#include <moduleproxynode.h>


#include <cutelogger/Logger.h>

#include <nodes/modulepropertybind.h>


QAutomationModule::QAutomationModule(QQuickItem *parent) : QQuickItem(parent)
{    

}

QAutomationModule::~QAutomationModule()
{
    LOG_INFO()<<"Deleting module"<<this->moduleName()<<"|ID:"<<this->id();
}




void QAutomationModule::setGraphView(qan::GraphView* graphView)
{


    m_graphView = graphView;

    if(m_graphView==nullptr)
        return;

    qan::Graph* scene=graphView->getGraph();
    if (scene==nullptr)
        return;

    SceneGraph* scenegraph=dynamic_cast<SceneGraph*>(scene);

    if(scenegraph){
        scenegraph->connect(scenegraph,&SceneGraph::flowNodeAdded,[this](FlowNode* node){
            ModulePropertyBind* modulenode=dynamic_cast<ModulePropertyBind*>(node);
            if(modulenode){
                modulenode->setModule(this);
            }           

            node->setParentModule(this);
        });
    }
    m_flowNodes->setScenegraph(scenegraph);


    emit graphViewChanged(m_graphView);
}


QAutomationModule::ModuleType QAutomationModule::type() const
{
    return m_type;
}






void QAutomationModule::Serialize(QJsonObject &json)
{
    QJsonObject graphViewObject;

    //    FlowNode* selectednode=static_cast<FlowNode*>(m_graphView->getGraph()->selectedNode());
    //    if(selectednode && selectednode->editMode()==true){

    //    }
    //    else{
    graphViewObject["zoom"]=m_graphView->getZoom();
    graphViewObject["x"]=m_graphView->getContainerItem()->x();
    graphViewObject["y"]=m_graphView->getContainerItem()->y();
    json["graphview"]=graphViewObject;
    //    }




    JsonSerializable::Serialize(json,this);
}

void QAutomationModule::DeSerialize(QJsonObject &json)
{
    JsonSerializable::DeSerialize(json,this);

    QJsonObject graphview=json["graphview"].toObject();

    m_graphView->setZoom(graphview["zoom"].toDouble());

    m_graphView->getContainerItem()->setX(graphview["x"].toDouble());
    m_graphView->getContainerItem()->setY(graphview["y"].toDouble());


//    m_flowNodes->loadConnections();


    for (int var = 0; var < m_flowNodes->length(); ++var) {
        FlowNode* node=m_flowNodes->at(var);
        node->setParentModule(this);
    }

    setModuleLoaded(true);

}




