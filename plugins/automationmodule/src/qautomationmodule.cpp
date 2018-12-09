#include "qautomationmodule.h"

#include <nodes/barcodereadernode.h>
#include <nodes/webservicenode.h>
#include <nodes/stringnode.h>
#include <nodes/modulepropertybind.h>
#include <nodes/proxyinputnode.h>
#include <nodes/multiplexedinputnode.h>
#include <nodes/numericnode.h>
#include <nodes/stringbuildernode.h>
#include <QtConcurrent>


#include <cutelogger/Logger.h>

FlowNodeManager* QAutomationModule::flownodemanager=nullptr;

QAutomationModule::QAutomationModule(QQuickItem *parent) : QQuickItem(parent)
{
    //    QAutomationModule::flownodemanager;
    m_commonNodeTypes.append(FlowNode::getCommonTypes());

}

FlowNode *QAutomationModule::addCommonNode(QPoint loc, QVariantMap nodeinfo, qan::GraphView *graphview)
{
    FlowNode* commonnode=FlowNode::addFlowNode(loc,nodeinfo,graphview);
    if(commonnode){
        m_FlowNodes.append(commonnode);
    }
    return commonnode;
}

void QAutomationModule::addModuleNode(QPoint loc, QVariantMap nodeinfo, qan::GraphView *graphview)
{

    qDebug()<<"Adding common node:"<<nodeinfo<<" @ "<<loc;

    QString nodeType;
    QMapIterator<QString, QVariant> i(nodeinfo);
    while (i.hasNext()) {
        i.next();
        nodeType=i.key();

    }

    FlowNode* node=createModuleNode(graphview,nodeType);

    if(node){
        node->initializeNode();
        m_FlowNodes.append(node);
    }

}

void QAutomationModule::loadModuleSettings(QString pathstr){

    QDir appdir=QDir(QCoreApplication::applicationDirPath());

    appdir.makeAbsolute();

    m_moduleConfigPath=appdir.cleanPath(pathstr);

    LOG_INFO()<<"Module Settings:"<<m_moduleConfigPath;

    //teste.relativeFilePath("")

    if(m_moduleConfigPath.isEmpty()) {
        LOG_WARNING() << "Empty path";
        return ;
    }



    QFile modulesettingsFile(m_moduleConfigPath);
    QDir::setCurrent(QCoreApplication::applicationDirPath());
    if(!modulesettingsFile.exists()) {
        LOG_WARNING() << "Does not exits: " <<m_moduleConfigPath;


    }

    if (!modulesettingsFile.open(QIODevice::ReadWrite)) {
        LOG_WARNING("Couldn't open save file.");
        return;
    }



    QByteArray modulesettingsData = modulesettingsFile.readAll();

    QJsonDocument modulesettings(QJsonDocument::fromJson(modulesettingsData ));

    m_configurationsObject=modulesettings.object();

    DeSerialize(m_configurationsObject);


    QJsonObject graphViewObject=m_configurationsObject["graphview"].toObject();

    if(m_graphView==nullptr){

        LOG_ERROR("Graphview is null");
        return;

    }

    m_graphView->setZoom(graphViewObject["zoom"].toDouble());

    m_graphView->getContainerItem()->setX(graphViewObject["x"].toDouble());
    m_graphView->getContainerItem()->setY(graphViewObject["y"].toDouble());





    qDebug()<<"Reading nodes";


    QJsonArray nodesArray = m_configurationsObject["nodes"].toArray();

    for (int i = 0; i < nodesArray.count(); ++i) {
        QJsonObject nodeObject=nodesArray[i].toObject();
        FlowNode* node=nullptr;

        node=readNode(m_graphView,nodeObject);

        if(node){

            m_FlowNodes.append(node);

            connect(node,&FlowNode::removeNode,[&](FlowNode* nodetoremove){
                int nodepos=m_FlowNodes.indexOf(nodetoremove);
                if(nodepos>0){
                    FlowNode* noderemoved=m_FlowNodes.at(nodepos);
                    if(noderemoved){
                        m_FlowNodes.removeAll(noderemoved);
                        //noderemoved->deleteLater();
                        this->m_graphView->getGraph()->removeNode(noderemoved);
                        //this->m_graphView->getGraph()->remove
                    }

                }
            });
        }

    }






    qDebug()<<"Module loaded";
    emit moduleLoadedChanged(true);
}

void QAutomationModule::loadConnections(){
    qDebug()<<"Setting node connections";

    foreach (FlowNode* node, QAutomationModule::flownodemanager->flownodes()) {
        node->loadNodeConnections();
    }



}

FlowNode *QAutomationModule::readNode(qan::GraphView *graphView, QJsonObject nodeobject)
{
    qan::Node* newnode=nullptr;


    newnode=QAutomationModule::createCommonNode(graphView,nodeobject["type"].toString(),this);

    if(!newnode){
        newnode=createModuleNode(graphView,nodeobject["type"].toString());
    }


    FlowNode* flownode=dynamic_cast<FlowNode*>(newnode);
    if(flownode){

        flownode->DeSerialize(nodeobject);


    }

    return flownode;

}


FlowNode *QAutomationModule::createCommonNode(qan::GraphView *graphView, QString nodetype,QAutomationModule* module)
{
    qan::Node* newnode=nullptr;



    if(nodetype=="BarcodeReaderNode"){
        newnode=graphView->getGraph()->insertNode<BarcodeReaderNode>(nullptr);
    }
    if(nodetype=="ModulePropertyBind"){
        newnode=graphView->getGraph()->insertNode<ModulePropertyBind>(nullptr);
        ModulePropertyBind* modulePropertyBindNode=dynamic_cast<ModulePropertyBind*>(newnode);
        /* ??? */ if(modulePropertyBindNode){
            modulePropertyBindNode->setModule(module);
        }
    }
    else if(nodetype=="WebServiceNode"){
        newnode=graphView->getGraph()->insertNode<WebServiceNode>(nullptr);
    }
    else if(nodetype=="StringNode"){
        newnode=graphView->getGraph()->insertNode<StringNode>(nullptr);
    }
    else if(nodetype=="ProxyInputNode"){
        newnode=graphView->getGraph()->insertNode<ProxyInputNode>(nullptr);
    }
    else if(nodetype=="NumericNode"){
        newnode=graphView->getGraph()->insertNode<NumericNode>(nullptr);
    }
    else if(nodetype=="MultiplexedInputNode"){
        newnode=graphView->getGraph()->insertNode<MultiplexedInputNode>(nullptr);
    }
    else if(nodetype=="StringBuilderNode"){
        newnode=graphView->getGraph()->insertNode<StringBuilderNode>(nullptr);
    }
    FlowNode* newflownode= dynamic_cast<FlowNode*>(newnode);

    return newflownode;
}



void QAutomationModule::save()
{




    Serialize(m_configurationsObject);


    QJsonArray nodesArrayList;// = m_configurationsObject["nodes"].toArray();


    for (int nodeIndex = 0; nodeIndex < m_FlowNodes.count(); ++nodeIndex) {
        FlowNode* node=m_FlowNodes.at(nodeIndex);

        QJsonObject nodeoject;


        node->Serialize(nodeoject);
        nodesArrayList.append(nodeoject);



    }

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



}
