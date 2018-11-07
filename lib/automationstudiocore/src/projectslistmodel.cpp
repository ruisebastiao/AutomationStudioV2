#include "projectslistmodel.h"
#include <qdebug.h>
namespace as{
ProjectsListModel::ProjectsListModel(QObject *parent)
{

}

ProjectsListModel::~ProjectsListModel()
{
   clear();
   qDebug()<<"Clearing projects";

}

void ProjectsListModel::AddProject(Project* project){
    beginInsertRows(QModelIndex(), rowCount(QModelIndex()), rowCount(QModelIndex()));   // kindly provided by superclass

    m_projects.append(project);

    endInsertRows();
}


void ProjectsListModel::clear(){

    if(m_projects.length()>0){

        beginRemoveRows(QModelIndex(), 0,m_projects.length()-1);   // kindly provided by superclass


        foreach (Project* project, m_projects) {
            delete project;
        }

        m_projects.clear();
        endRemoveRows();
    }


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
