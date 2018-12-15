#include "flownodemanager.h"

#include <nodes/proxyinputnode.h>


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

QMap<int, FlowNode *> FlowNodeManager::getFlownodesTable() const
{
    return m_flownodesTable;
}

//void FlowNodeManager::Serialize(QJsonObject &json)
//{

//}

//void FlowNodeManager::DeSerialize(QJsonObject &json)
//{

//}

void FlowNodeManager::AddItem(FlowNode *item)
{
    if(!item){
        return;
    }

    SerializedListModel::AddItem(item);


    m_flownodesTable[item->id()]=item;


    ProxyInputNode* proxynode=dynamic_cast<ProxyInputNode*>(item);

    if(proxynode){
        m_proxynodes.append(proxynode);
        proxynode->setFlowNodes(this);

    }


    QModelIndex topLeft = createIndex(0,0);
    emit dataChanged(topLeft, topLeft);

    connect(item,&FlowNode::nameChanged,[this](){

        layoutAboutToBeChanged();
        layoutChanged();
    });


}



void FlowNodeManager::RemoveItem(FlowNode *item)
{

    int itemIndex=m_internalList.indexOf(item);

    if(itemIndex>=0){

        ProxyInputNode* proxynode=dynamic_cast<ProxyInputNode*>(item);

        if(proxynode){
            m_proxynodes.removeAll(proxynode);
        }


        m_flownodesTable.take(itemIndex);


    }

    SerializedListModel::RemoveItem(item);
}

//void FlowNodeManager::Serialize(QJsonArray &jsonarray)
//{

//}

void FlowNodeManager::DeSerialize(QJsonArray &jsonarray)
{

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



