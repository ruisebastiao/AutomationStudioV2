#include "projectslistmodel.h"
#include <qdebug.h>

ProjectsListModel::ProjectsListModel(QObject *parent)
{

}

ProjectsListModel::~ProjectsListModel()
{
   clear();
   qDebug()<<"Clearing projects";

}





QHash<int, QByteArray> ProjectsListModel::roleNames() const
{
    return {
        { NameRole, "name" },
        { ProjectRole, "project" },
    };
}

QVariant ProjectsListModel::data(const QModelIndex &index, int role) const
{

    //    qDebug()<<" Data asked for "<<index.row()<<" and role "<<role;
    if (index.row()<0 || index.row()>=m_internalList.length())
    {
        return QVariant();
    }

    Project *project= m_internalList.at(index.row());
    if (role == NameRole){
        return project->name();
    }


    if (role == ProjectRole){
        //        QVariant var
        return QVariant::fromValue(project);
    }


    return QVariant();

}

