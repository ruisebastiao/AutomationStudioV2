#include "flownodemanager.h"

#include <nodes/proxyinputnode.h>

FlowNodeManager::FlowNodeManager(QObject *parent):QAbstractListModel(parent){


}

QMap<int, FlowNode *> FlowNodeManager::getFlownodesTable() const
{
    return m_flownodesTable;
}

FlowNode *FlowNodeManager::getByID(int id)
{

    FlowNode* nodefromid=nullptr;
    std::all_of(m_flownodes.begin(), m_flownodes.end(), [&,id](FlowNode* node) {
        // return false if you want to break, true otherwise
        if(node->id()==id){
            nodefromid=node;
            return false;
        }
        return true;
    });
    return  nodefromid;

}

FlowNode* FlowNodeManager::at(int index){
    return m_flownodes.at(index);
}

void FlowNodeManager::addNode(FlowNode *node)
{
    if(!node){
        return;
    }


    beginInsertRows(QModelIndex(), m_flownodes.length(), m_flownodes.length());   // kindly provided by superclass

    m_flownodes.append(node);
    m_flownodesTable[node->id()]=node;


    ProxyInputNode* proxynode=dynamic_cast<ProxyInputNode*>(node);


    endInsertRows();

    if(proxynode){
        m_proxynodes.append(proxynode);
        proxynode->setFlowNodes(this);

    }


    //    emit dataChanged(index(0), index(0));

    QModelIndex topLeft = createIndex(0,0);
    emit dataChanged(topLeft, topLeft);

    connect(node,&FlowNode::nameChanged,[this](){
        //        emit dataChanged(index(0), index(0));
        layoutAboutToBeChanged();
        layoutChanged();
    });

    emit lengthChanged(length());
}


void FlowNodeManager::removeNode(FlowNode *node)

{
    int itemIndex=m_flownodes.indexOf(node);

    if(itemIndex>=0){
        beginRemoveRows(QModelIndex(), static_cast<int>(itemIndex), static_cast<int>(itemIndex));   // kindly provided by superclass

        m_flownodes.removeAt(itemIndex);

        ProxyInputNode* proxynode=dynamic_cast<ProxyInputNode*>(node);

        if(proxynode){
            m_proxynodes.removeAll(proxynode);
        }


        m_flownodesTable.take(itemIndex);

        endRemoveRows();

        emit lengthChanged(length());
    }
}


int FlowNodeManager::rowCount(const QModelIndex &parent) const
{
    return length();
}

QVariant FlowNodeManager::data(const QModelIndex &index, int role) const
{
    if (index.row()<0 || index.row()>=m_flownodes.size()){
        return QVariant();
    }

    FlowNode* node= m_flownodes.at(index.row());
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

    std::sort(std::begin(m_flownodes), std::end(m_flownodes), [](FlowNode* a, FlowNode *b) {return a->id() < b->id(); });

    for (int var = 0; var < m_flownodes.length()-1; ++var) {
        if(m_flownodes.at(var+1)->id()-m_flownodes.at(var)->id()>1){
            // check for available ids
            FlowNode *node= m_flownodes.at(var);
            return node->id()+1;

        }
    }

    return m_flownodes.length();
}



QList<FlowNode *> FlowNodeManager::flownodes()
{
    return m_flownodes;
}



