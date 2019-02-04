#include "processingnodemanager.h"

#include <nodes/cv/processingnode.h>

ProcessingNodeManager::ProcessingNodeManager(QObject *parent)
{

}

QVariant ProcessingNodeManager::data(const QModelIndex &index, int role) const
{
    if (index.row()<0 || index.row()>=m_internalList.size()){
        return QVariant();
    }

    QVariant return_val=FlowNodeManager::data(index,role);


    if(return_val.isValid()==false){
        ProcessingNode* node= dynamic_cast<ProcessingNode*>(m_internalList.at(index.row()));
        if(node==nullptr){
            return QVariant();
        }


        if (role == ProcessingTypeRole){

            return QVariant::fromValue(node->processingType());
        }



        return QVariant();

    }
    else {
        return return_val;
    }


}

QHash<int, QByteArray> ProcessingNodeManager::roleNames() const
{
    QHash<int, QByteArray> roles=FlowNodeManager::roleNames();

    roles.insert( ProcessingTypeRole, "ProcessingTypeRole" );

    return roles;
}
