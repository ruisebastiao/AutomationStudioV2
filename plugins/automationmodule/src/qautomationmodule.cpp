#include "qautomationmodule.h"

#include <nodes/barcodereadernode.h>
#include <nodes/webservicenode.h>
#include <nodes/stringnode.h>

#include <Logger.h>

FlowNodeManager* QAutomationModule::flownodemanager=nullptr;

QAutomationModule::QAutomationModule(QQuickItem *parent) : QQuickItem(parent)
{
    QAutomationModule::flownodemanager=new FlowNodeManager();
}

void QAutomationModule::load(QString pathstr){

    m_moduleConfigPath=pathstr;


    if(m_moduleConfigPath.isEmpty()) {
        //   LOG_INFO() << "Empty path";
        return ;
    }



    QFile modulesettingsFile(m_moduleConfigPath);
    if(!modulesettingsFile.exists()) {
        //   LOG_INFO() << "Does not exits: " <<m_moduleConfigPath;

        return;
    }

    if (!modulesettingsFile.open(QIODevice::ReadOnly)) {
        // LOG_INFO("Couldn't open save file.");
        return;
    }



    QByteArray modulesettingsData = modulesettingsFile.readAll();

    QJsonDocument modulesettings(QJsonDocument::fromJson(modulesettingsData ));

    m_configurationsObject=modulesettings.object();

    DeSerialize(m_configurationsObject,this);


    QJsonObject graphViewObject=m_configurationsObject["graphview"].toObject();

    if(m_graphView==nullptr){

        LOG_ERROR("Graphview is null");
        return;

    }

    m_graphView->setZoom(graphViewObject["zoom"].toDouble());

    m_graphView->getContainerItem()->setX(graphViewObject["x"].toDouble());
    m_graphView->getContainerItem()->setY(graphViewObject["y"].toDouble());


    QJsonArray nodesArray = m_configurationsObject["nodes"].toArray();

    for (int i = 0; i < nodesArray.count(); ++i) {
        QJsonObject nodeObject=nodesArray[i].toObject();
        FlowNode* node=nullptr;

        node=readNode(m_graphView,nodeObject);

        if(node){

            emit nodeAdded(node);
            m_FlowNodes.append(node);
        }
    }

    emit moduleLoadedChanged(true);
}

FlowNode *QAutomationModule::readNode(qan::GraphView *graphView, QJsonObject nodeobject)
{
    qan::Node* newnode=nullptr;

    if(nodeobject["type"]=="BarcodeReaderNode"){
        newnode=graphView->getGraph()->insertNode<BarcodeReaderNode>(nullptr);
    }
    else if(nodeobject["type"]=="WebServiceNode"){
        newnode=graphView->getGraph()->insertNode<WebServiceNode>(nullptr);
    }
    else if(nodeobject["type"]=="StringNode"){
        newnode=graphView->getGraph()->insertNode<StringNode>(nullptr);
    }

    FlowNode* node=dynamic_cast<FlowNode*>(newnode);
    if(node){
        node->DeSerialize(nodeobject);

    }



    return node;

}

void QAutomationModule::save()
{




    Serialize(m_configurationsObject,this);


    QJsonArray nodesArrayList = m_configurationsObject["nodes"].toArray();


    for (int nodeIndex = 0; nodeIndex < m_FlowNodes.count(); ++nodeIndex) {
        FlowNode* node=m_FlowNodes.at(nodeIndex);


        for (int nodeObjectIndex = 0; nodeObjectIndex < nodesArrayList.count(); ++nodeObjectIndex) {
            QJsonObject nodeobject=nodesArrayList[nodeObjectIndex].toObject();
            if(nodeobject["id"]==node->id()){
                node->Serialize(nodeobject);
                nodesArrayList[nodeIndex]=nodeobject;
                break;
            }
        }


    }

    //graphView()->getZoom()


    m_configurationsObject["nodes"]=nodesArrayList;
    QJsonDocument saveDoc(m_configurationsObject);


    QByteArray json = saveDoc.toJson();
    QJsonParseError *error = Q_NULLPTR;
    QJsonDocument parsedDoc=QJsonDocument::fromJson(json,error);

    if(error){
        //  LOG_ERROR() << "Error serializing:"<<error->errorString();
        return;
    }


    if(m_moduleConfigPath.isEmpty()) {
        //  LOG_INFO() << "Empty path";
        return ;
    }


    QUrl path(QUrl::fromLocalFile(m_moduleConfigPath));

    QFile modulesettingsFile(path.toLocalFile());
    if(!modulesettingsFile.exists()) {
        //  LOG_INFO() << "Does not exits: " <<m_moduleConfigPath;

        return;
    }

    if (!modulesettingsFile.open(QIODevice::WriteOnly)) {
        //  LOG_INFO("Couldn't open save file.");
        return ;
    }

    modulesettingsFile.write(json);




}

void QAutomationModule::setGraphView(qan::GraphView* graphView)
{


    m_graphView = graphView;

    if(m_graphView==nullptr)
        return;

    qan::Graph* scene=graphView->getGraph();
    if (scene==nullptr)
        return;


    if(scene==nullptr)
        return;



    emit graphViewChanged(m_graphView);
}


QAutomationModule::ModuleType QAutomationModule::type() const
{
    return ModuleType::AutomationModule;
}




void QAutomationModule::Serialize(QJsonObject &json, QObject *target)
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




    JsonSerializable::Serialize(json,target);
}

void QAutomationModule::DeSerialize(QJsonObject &json, QObject *target)
{

    JsonSerializable::DeSerialize(json,target);
}

void QAutomationModule::Serialize(QJsonObject &json)
{
    Serialize(json,this);
}

void QAutomationModule::DeSerialize(QJsonObject &json)
{
    DeSerialize(json,this);
}
