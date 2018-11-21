#include "flownodemanager.h"

FlowNodeManager::FlowNodeManager(QObject *parent):QAbstractListModel(parent){
    m_filterType= FlowNode::Type::NodeNone;


    QObject::connect(this,SIGNAL(onFlowNodeLoaded(FlowNode*)),this,SLOT(onNodeAdded(FlowNode*)));


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

void FlowNodeManager::addNode(FlowNode *node)

{
    beginInsertRows(QModelIndex(), rowCount(QModelIndex()), rowCount(QModelIndex()));   // kindly provided by superclass

    m_flownodes.append(node);
    m_flownodesTable[node->id()]=node;

    endInsertRows();

    emit lengthChanged(m_flownodes.size());
}


void FlowNodeManager::removeNode(FlowNode *node)

{
    int itemIndex=m_flownodes.indexOf(node);

    if(itemIndex>=0){
        beginRemoveRows(QModelIndex(), static_cast<int>(itemIndex), static_cast<int>(itemIndex));   // kindly provided by superclass

        m_flownodes.removeAt(itemIndex);
        m_flownodesTable.take(itemIndex);

        endRemoveRows();

        emit lengthChanged(m_flownodes.size());
    }
}


int FlowNodeManager::rowCount(const QModelIndex &parent) const

{
    return m_flownodes.length();
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

    return QVariant();
}

QHash<int, QByteArray> FlowNodeManager::roleNames() const
{


    return {

        { NameRole, "nodeName" },
        { IDRole, "nodeID" },
        { NodeRole, "node" }

    };

}



QList<FlowNode *> FlowNodeManager::flownodes()
{
    return m_flownodes;
}

void FlowNodeManager::onNodeAdded(FlowNode *nodeloaded)
{
    addNode(nodeloaded);

}

void FlowNodeManager::setFilterType(const FlowNode::Type &filterType)
{
    if(filterType!=m_filterType){
        m_filterType = filterType;
    }

}


