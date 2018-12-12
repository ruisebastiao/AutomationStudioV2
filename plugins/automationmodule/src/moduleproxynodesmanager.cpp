#include "moduleproxynodesmanager.h"

ProxyNodesManager::ProxyNodesManager(QObject *parent) : QAbstractListModel(parent)
{

}

int ProxyNodesManager::rowCount(const QModelIndex &parent) const
{
    return  m_moduleproxynodes.length();
}

QVariant ProxyNodesManager::data(const QModelIndex &index, int role) const
{
    if (index.row()<0 || index.row()>=m_moduleproxynodes.size()){
        return QVariant();
    }

    ModuleProxyInputNode* node= m_moduleproxynodes.at(index.row());
    if(node==nullptr){
        return QVariant();
    }

    if (role == Qt::DisplayRole){

        return QVariant::fromValue(node->name()+"|ID:"+QString::number(node->id()));
    }

    if (role == NodeRole){

        return QVariant::fromValue(node);
    }






    return QVariant();
}

QHash<int, QByteArray> ProxyNodesManager::roleNames() const
{
    return {


        { NodeRole, "nodeRole" }

    };
}

//ProxyNodeInfo::ProxyNodeInfo(int moduleID, ProxyInputNode *node)
//{
//    m_moduleID=moduleID;
//    m_node=node;
//}

//int ProxyNodeInfo::moduleID() const
//{
//    return m_moduleID;
//}


//ProxyInputNode *ProxyNodeInfo::node() const
//{
//    return m_node;
//}
