#include "subprojectslistmodel.h"

subProjectsListModel::subProjectsListModel()
{

}

int subProjectsListModel::length()
{
    return m_internalList.length();
}

int subProjectsListModel::rowCount(const QModelIndex &parent) const
{
 return m_internalList.length();
}

QVariant subProjectsListModel::data(const QModelIndex &index, int role) const
{
    //    qDebug()<<" Data asked for "<<index.row()<<" and role "<<role;
    if (index.row()<0 || index.row()>=m_internalList.length())
    {
        return QVariant();
    }

    SubProject *subproject= m_internalList.at(index.row());



    if (role == subProjectRole){
        //        QVariant var
        return QVariant::fromValue(subproject);
    }

    if(role==subProjectIDRole){
        return QVariant::fromValue(subproject->id());

    }

    if(role==subProjectNameRole){
        return QVariant::fromValue(subproject->name());

    }


    return QVariant();
}

QHash<int, QByteArray> subProjectsListModel::roleNames() const
{
    return {
        { subProjectIDRole, "subProjectID" },
        { subProjectRole, "subProject" },
        { subProjectNameRole, "subProjectName" }
    };
}
