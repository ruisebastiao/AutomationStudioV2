#include "projectslistmodel.h"

namespace as{
ProjectsListModel::ProjectsListModel(QObject *parent)
{

}

void ProjectsListModel::AddProject(Project* project){
    beginInsertRows(QModelIndex(), rowCount(QModelIndex()), rowCount(QModelIndex()));   // kindly provided by superclass

    m_projects.append(project);

    endInsertRows();
}


void ProjectsListModel::clear(){
    beginInsertRows(QModelIndex(), rowCount(QModelIndex()), rowCount(QModelIndex()));   // kindly provided by superclass

    m_projects.clear();

    endInsertRows();
}


QHash<int, QByteArray> ProjectsListModel::roleNames() const
{
    return {
        { NameRole, "name" },
        { ProjectRole, "project" },
    };
}

Project *ProjectsListModel::getItemAt(int index)
{
    return m_projects.at(index);
}

int ProjectsListModel::count()
{
    return m_projects.length();
}


int ProjectsListModel::rowCount(const QModelIndex &parent) const
{
    return m_projects.length();
}

QVariant ProjectsListModel::data(const QModelIndex &index, int role) const
{

    //    qDebug()<<" Data asked for "<<index.row()<<" and role "<<role;
    if (index.row()<0 || index.row()>=m_projects.size())
    {
        return QVariant();
    }

    Project *project= m_projects.at(index.row());
    if (role == NameRole){
        return project->name();
    }


    if (role == ProjectRole){
        //        QVariant var
        return QVariant::fromValue(project);
    }


    return QVariant();

}
}
