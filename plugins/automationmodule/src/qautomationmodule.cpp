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


QAutomationModule::QAutomationModule(QQuickItem *parent) : QQuickItem(parent)
{

    m_commonNodeTypes.append(FlowNode::getCommonTypes());

}


void QAutomationModule::addModuleNode(QPoint loc, QVariantMap nodeinfo)
{

    qDebug()<<"Adding module node:"<<nodeinfo<<" @ "<<loc;

    QString nodeType;
    QMapIterator<QString, QVariant> i(nodeinfo);
    while (i.hasNext()) {
        i.next();
        nodeType=i.key();

    }

    FlowNode* node=createModuleNode(nodeType);

    if(node){

        int nodeid=m_flowNodes->getAvailableID();
        if(nodeid==-1){
            LOG_ERROR("Invalid node ID");
        }

        node->initializeNode(nodeid);

        m_flowNodes->AddItem(node);
    }

}

//void QAutomationModule::loadModuleSettings(QString pathstr){

//    QDir appdir=QDir(QCoreApplication::applicationDirPath());

//    appdir.makeAbsolute();

//    m_moduleConfigPath=appdir.cleanPath(pathstr);

//    LOG_INFO()<<"Module Settings:"<<m_moduleConfigPath;

//    //teste.relativeFilePath("")

//    if(m_moduleConfigPath.isEmpty()) {
//        LOG_WARNING() << "Empty path";
//        return ;
//    }



//    QFile modulesettingsFile(m_moduleConfigPath);
//    QDir::setCurrent(QCoreApplication::applicationDirPath());
//    if(!modulesettingsFile.exists()) {
//        LOG_WARNING() << "Does not exits: " <<m_moduleConfigPath;


//    }

//    if (!modulesettingsFile.open(QIODevice::ReadWrite)) {
//        LOG_WARNING("Couldn't open save file.");
//        return;
//    }



//    QByteArray modulesettingsData = modulesettingsFile.readAll();

//    QJsonDocument modulesettings(QJsonDocument::fromJson(modulesettingsData ));

//    m_configurationsObject=modulesettings.object();

//    DeSerialize(m_configurationsObject);


//    QJsonObject graphViewObject=m_configurationsObject["graphview"].toObject();

//    if(m_graphView==nullptr){

//        LOG_ERROR("Graphview is null");
//        return;

//    }

//    m_graphView->setZoom(graphViewObject["zoom"].toDouble());

//    m_graphView->getContainerItem()->setX(graphViewObject["x"].toDouble());
//    m_graphView->getContainerItem()->setY(graphViewObject["y"].toDouble());





//    qDebug()<<"Reading nodes";


//    QJsonArray nodesArray = m_configurationsObject["nodes"].toArray();

//    int count=nodesArray.count();
//    for (int i = 0; i < count; ++i) {
//        QJsonObject nodeObject=nodesArray[i].toObject();
//        FlowNode* node=nullptr;

//        node=readNode(m_graphView,nodeObject);

//        if(node){

//            m_flowNodes->AddItem(node);

//            connect(node,&FlowNode::destroyed,[&](QObject* node){
//                FlowNode* nodetoremove=dynamic_cast<FlowNode*>(node);

//                if(nodetoremove){
//                    this->m_graphView->getGraph()->removeNode(nodetoremove);
//                    m_flowNodes->RemoveItem(nodetoremove);
//                }

//            });
//        }

//    }






//    qDebug()<<"Module loaded";
//    emit moduleLoadedChanged(true);
//}

void QAutomationModule::loadConnections(){
    qDebug()<<"Setting node connections";


    for (int var = 0; var < m_flowNodes->length(); ++var) {
        FlowNode* node=m_flowNodes->at(var);

        QMapIterator<string, FlowNodePort*> i(node->getOutPorts());
        while (i.hasNext()) {
            i.next();

            FlowNodePort* nodeoutport =i.value();

            if(nodeoutport){
                foreach (ConnectionInfo* connection, nodeoutport->getConnections()) {


                    FlowNode* targetnode=m_flowNodes->getFlownodesTable()[connection->nodeID()];

                    if(targetnode){
                        string portkey=QString::number(connection->nodeID()).toStdString();
                        portkey.append("|");
                        portkey.append(connection->portID().toStdString());
                        QMap<string,FlowNodePort *>  map=targetnode->getInPorts();
                        FlowNodePort* targetport= map.value(portkey,nullptr);
                        if(targetport){

                            qan::PortItem* inport=targetport->getPortItem();
                            if(inport->getInEdgeItems().size()>0){
                                LOG_ERROR()<<"In edge with multiple connection (Source node:"<<*node<<"| target node:"<< *targetnode<<")";
                                continue;
                            }
                            qan::Edge* newedge= node->getScenegraph()->insertNewEdge(false,node,targetnode);
                            if(newedge){
                                node->getScenegraph()->bindEdge(newedge,nodeoutport->getPortItem(),targetport->getPortItem());

                            }


                        }
                    }
                    //std::get
                }
            }
            else{
                LOG_ERROR()<<*node<<"| null value from key:"<<QString::fromStdString(i.key());
            }

        }

    }


}




FlowNode *QAutomationModule::readNode(QJsonObject nodeobject)
{
    qan::Node* newnode=nullptr;


    newnode=createCommonNode(nodeobject["type"].toString());

    if(!newnode){
        newnode=createModuleNode(nodeobject["type"].toString());
    }


    FlowNode* flownode=dynamic_cast<FlowNode*>(newnode);
    if(flownode){

        flownode->DeSerialize(nodeobject);


    }

    return flownode;

}


FlowNode *QAutomationModule::addCommonNode(QPoint loc, QVariantMap nodeinfo)
{
    qDebug()<<"Adding common node:"<<nodeinfo<<" @ "<<loc;

    QString nodeType;
    QMapIterator<QString, QVariant> i(nodeinfo);
    while (i.hasNext()) {
        i.next();
        nodeType=i.key();

    }

    FlowNode *commonnode=createCommonNode(nodeType);

    if(commonnode){
        commonnode->getItem()->setProperty("x",QVariant::fromValue(loc.x()));
        commonnode->getItem()->setProperty("y",QVariant::fromValue(loc.y()));




        int nodeid=m_flowNodes->getAvailableID();
        if(nodeid==-1){
            LOG_ERROR("Invalid node ID");
        }

        commonnode->initializeNode(nodeid);

        m_flowNodes->AddItem(commonnode);

        return commonnode;


    }

}


FlowNode *QAutomationModule::createCommonNode(QString nodetype)
{
    qan::Node* newnode=nullptr;



    if(nodetype=="BarcodeReaderNode"){
        newnode=m_graphView->getGraph()->insertNode<BarcodeReaderNode>(nullptr);
    }
    if(nodetype=="ModulePropertyBind"){
        newnode=m_graphView->getGraph()->insertNode<ModulePropertyBind>(nullptr);
        ModulePropertyBind* modulePropertyBindNode=dynamic_cast<ModulePropertyBind*>(newnode);
        /* ??? */ if(modulePropertyBindNode){
            modulePropertyBindNode->setModule(this);
        }
    }
    else if(nodetype=="WebServiceNode"){
        newnode=m_graphView->getGraph()->insertNode<WebServiceNode>(nullptr);
    }
    else if(nodetype=="StringNode"){
        newnode=m_graphView->getGraph()->insertNode<StringNode>(nullptr);
    }
    else if(nodetype=="ProxyInputNode"){
        newnode=m_graphView->getGraph()->insertNode<ProxyInputNode>(nullptr);
    }
    else if(nodetype=="NumericNode"){
        newnode=m_graphView->getGraph()->insertNode<NumericNode>(nullptr);
    }
    else if(nodetype=="MultiplexedInputNode"){
        newnode=m_graphView->getGraph()->insertNode<MultiplexedInputNode>(nullptr);
    }
    else if(nodetype=="StringBuilderNode"){
        newnode=m_graphView->getGraph()->insertNode<StringBuilderNode>(nullptr);
    }
    FlowNode* newflownode= dynamic_cast<FlowNode*>(newnode);

    return newflownode;
}



//void QAutomationModule::save()
//{




//    Serialize(m_configurationsObject);


//    QJsonArray nodesArrayList;// = m_configurationsObject["nodes"].toArray();


//    for (int nodeIndex = 0; nodeIndex < m_flowNodes->length(); ++nodeIndex) {
//        FlowNode* node=m_flowNodes->at(nodeIndex);

//        QJsonObject nodeoject;


//        node->Serialize(nodeoject);
//        nodesArrayList.append(nodeoject);



//    }

//    m_configurationsObject["nodes"]=nodesArrayList;
//    QJsonDocument saveDoc(m_configurationsObject);


//    QByteArray json = saveDoc.toJson();
//    QJsonParseError *error = Q_NULLPTR;
//    QJsonDocument parsedDoc=QJsonDocument::fromJson(json,error);

//    if(error){
//        //  LOG_ERROR() << "Error serializing:"<<error->errorString();
//        return;
//    }


//    if(m_moduleConfigPath.isEmpty()) {
//        //  LOG_INFO() << "Empty path";
//        return ;
//    }


//    QUrl path(QUrl::fromLocalFile(m_moduleConfigPath));

//    QFile modulesettingsFile(path.toLocalFile());
//    if(!modulesettingsFile.exists()) {
//        //  LOG_INFO() << "Does not exits: " <<m_moduleConfigPath;

//        return;
//    }

//    if (!modulesettingsFile.open(QIODevice::WriteOnly)) {
//        //  LOG_INFO("Couldn't open save file.");
//        return ;
//    }

//    modulesettingsFile.write(json);




//}

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


    m_graphView->setZoom(json["zoom"].toDouble());

    m_graphView->getContainerItem()->setX(json["x"].toDouble());
    m_graphView->getContainerItem()->setY(json["y"].toDouble());




}



//FlowNode *FlowNode::getFlowNodeById(int id, QList<FlowNode *> nodeList)
//{
//    for (int var = 0; var < nodeList.length(); ++var) {
//        if(nodeList.at(var)->id()==id){
//            return  nodeList.at(var);
//        }
//    }

//    return nullptr;
//}

//int FlowNode::getAvailableID(QList<FlowNode *> list)
//{
//}


