#include "flownodemanager.h"

#include <nodes/commandparsernode.h>
#include <nodes/commandsendernode.h>
#include <nodes/proxynode.h>

#include <moduleproxynode.h>


FlowNodeManager::FlowNodeManager(QObject *parent):SerializedListModel<FlowNode>(parent){


}

int FlowNodeManager::indexOfID(int nodeID)
{
    int index=-1;
    std::all_of(m_internalList.begin(), m_internalList.end(), [&,nodeID](FlowNode* node) {
        // return false if you want to break, true otherwise
        if(node->id()==nodeID){
            index=node->id();
            return false;
        }

        return true;

    });
    return  index;

}

SceneGraph *FlowNodeManager::getScenegraph() const
{
    return m_scenegraph;
}

void FlowNodeManager::setScenegraph(SceneGraph *scenegraph)
{
    if(m_scenegraph==scenegraph){
        return;
    }
    m_scenegraph = scenegraph;

    scenegraph->connect(scenegraph,&SceneGraph::flowNodeAdded,[&](FlowNode* node){
        if(m_deserializing==false){

            if(node && node->id()==-1){
                int nodeid=getAvailableID();
                if(nodeid==-1){
                    LOG_ERROR("Invalid node ID");
                    return;
                }

                node->initializeNode(nodeid);
                addItem(node);

            }



        }
    });


}

QMap<int, FlowNode *> FlowNodeManager::getFlownodesTable() const
{
    return m_flownodesTable;
}

void FlowNodeManager::addItem(FlowNode *item)
{
    if(!item){
        return;
    }

    SerializedListModel::addItem(item);


    m_flownodesTable[item->id()]=item;

    CommandSenderNode* commandsendernode=dynamic_cast<CommandSenderNode*>(item);

    if(commandsendernode){

        commandsendernode->setFlowNodes(this);
    }

    CommandParserNode* commandparsernode=dynamic_cast<CommandParserNode*>(item);

    if(commandparsernode){
        commandparsernode->setFlowNodes(this);
    }

    ProxyNode* proxynode=dynamic_cast<ProxyNode*>(item);

    if(proxynode){
        m_proxynodes.append(proxynode);
        proxynode->setFlowNodes(this);


        connect(proxynode,&ProxyNode::proxyTypeChanged,[this](QString proxyType){

            layoutAboutToBeChanged();
            layoutChanged();
        });
    }


    QModelIndex topLeft = createIndex(0,0);
    emit dataChanged(topLeft, topLeft);

    connect(item,&FlowNode::nameChanged,[this](){

        layoutAboutToBeChanged();
        layoutChanged();
    });



    connect(item,&FlowNode::destroyed,[this](QObject* object){

        if(object){
            this->removeItem((FlowNode*)object);
        }

    });

//    ModuleProxyNode* moduleproxynode=dynamic_cast<ModuleProxyNode*>(item);


     emit flowNodeAdded(item);


}


void FlowNodeManager::loadConnections(){
    qDebug()<<"Setting node connections";


    for (int var = 0; var < m_internalList.length(); ++var) {
        FlowNode* node=m_internalList.at(var);

        QMapIterator<string, FlowNodePort*> i(node->getOutPorts());
        while (i.hasNext()) {
            i.next();

            FlowNodePort* nodeoutport =i.value();

            if(nodeoutport){
                foreach(ConnectionInfo* connection, nodeoutport->getConnections()) {


                    FlowNode* targetnode=getFlownodesTable()[connection->nodeID()];
                    ProxyNode* targetproxynode=dynamic_cast<ProxyNode*>(targetnode);
                    ModuleProxyNode* sourceproxynode=dynamic_cast<ModuleProxyNode*>(node);
                    if(sourceproxynode && sourceproxynode->proxyType()=="Input"){
                        continue;
                    }
                    if(targetnode || (targetproxynode && targetproxynode->proxyType()=="Input")){
                        string portkey=QString::number(connection->nodeID()).toStdString();
                        portkey.append("|");
                        portkey.append(connection->portID().toStdString());
                        QMap<string,FlowNodePort *>  map=targetnode->getInPorts();
                        FlowNodePort* targetport= map.value(portkey,nullptr);
                        if(targetport){

                            qan::PortItem* inport=targetport->getPortItem();
                            if(inport->getInEdgeItems().size()>0){
                                QString error;
                                QTextStream(&error) <<"In edge with multiple connection (node:"<<*targetnode<<"| port:"<<inport->getId()<<")";



                                //exit(-4);

                               throw std::exception(std::runtime_error(error.toStdString().c_str()));

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

        node->setConnectionsLoaded(true);
    }


}


void FlowNodeManager::removeItem(FlowNode *item)
{

    int itemIndex=m_internalList.indexOf(item);

    if(itemIndex>=0){

        ProxyNode* proxynode=dynamic_cast<ProxyNode*>(item);

        if(proxynode){
            m_proxynodes.removeAll(proxynode);
        }


        m_flownodesTable.take(itemIndex);


    }

    SerializedListModel::removeItem(item);
}



void FlowNodeManager::DeSerialize(QJsonArray &jsonarray)
{
    m_deserializing=true;

//    Utilities::NonBlockingExec([&](){
        for (int nodeIndex = 0; nodeIndex < jsonarray.size(); ++nodeIndex) {
            QJsonObject nodeObject = jsonarray[nodeIndex].toObject();
            FlowNode* node= m_scenegraph->readNode(nodeObject);
            if(node){
    //            node->blockSignals(true);
                addItem(node);
            }
        }

        loadConnections();


//    });
//    for (int var = 0; var < m_internalList.count(); ++var) {
//        FlowNode* node=m_internalList.at(var);
//        node->blockSignals(false);
//    }
    m_deserializing=false;
}

FlowNode *FlowNodeManager::getByID(int id)
{

    FlowNode* nodefromid=nullptr;
    std::all_of(m_internalList.begin(), m_internalList.end(), [&,id](FlowNode* node) {
        // return false if you want to break, true otherwise
        if(node->id()==id){
            nodefromid=node;
            return false;
        }
        return true;
    });
    return  nodefromid;

}



QVariant FlowNodeManager::data(const QModelIndex &index, int role) const
{
    if (index.row()<0 || index.row()>=m_internalList.size()){
        return QVariant();
    }

    FlowNode* node= m_internalList.at(index.row());
    if(node==nullptr){
        return QVariant();
    }

    if (role == Qt::DisplayRole){

        return QVariant::fromValue(node->name()+"(ID:)"+QString::number(node->id()));
    }

    if (role == NameRole){

        return QVariant::fromValue(node->name());
    }


    if (role == IDRole){

        return QVariant::fromValue(node->id());
    }


    if (role == NodeRole){

        return QVariant::fromValue(node);
    }

    if (role == NodeTypeRole){

        return QVariant::fromValue(node->getType());
    }


    return QVariant();
}

QHash<int, QByteArray> FlowNodeManager::roleNames() const
{


    return {

        { NameRole, "nodeName" },
        { IDRole, "nodeID" },
        { NodeRole, "node" },

        { NodeTypeRole,"nodeTypeRole"}

    };

}

int FlowNodeManager::getAvailableID()
{

    std::sort(std::begin(m_internalList), std::end(m_internalList), [](FlowNode* a, FlowNode *b) {return a->id() < b->id(); });

    for (int var = 0; var < m_internalList.length()-1; ++var) {
        if(m_internalList.at(var+1)->id()-m_internalList.at(var)->id()>1){
            // check for available ids
            FlowNode *node= m_internalList.at(var);
            return node->id()+1;

        }
    }

    return m_internalList.length();
}



QList<FlowNode *> FlowNodeManager::flownodes()
{
    return m_internalList;
}



