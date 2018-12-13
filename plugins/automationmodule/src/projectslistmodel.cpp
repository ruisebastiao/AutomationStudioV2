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


int ProjectsListModel::getAvailableID()
{

    std::sort(std::begin(m_internalList), std::end(m_internalList), [](Project* a, Project *b) {return a->id() < b->id(); });

    for (int var = 0; var < m_internalList.length()-1; ++var) {
        if(m_internalList.at(var+1)->id()-m_internalList.at(var)->id()>1){
            // check for available ids
            Project *project= m_internalList.at(var);
            return project->id()+1;

        }
    }

    return m_internalList.length();
}


void ProjectsListModel::createNewProject()
{
    Project* newproject=new Project(this);
    newproject->setId(getAvailableID());
    AddItem(newproject);
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

