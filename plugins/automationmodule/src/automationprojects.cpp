#include "automationprojects.h"

AutomationProjects::AutomationProjects(QObject *parent)
{
    m_modules.clear();
}

void AutomationProjects::AddModule(QAutomationModule* module){
    beginInsertRows(QModelIndex(), rowCount(QModelIndex()), rowCount(QModelIndex()));   // kindly provided by superclass

    m_modules.append(module);

    endInsertRows();
}


void AutomationProjects::clear(){
    beginInsertRows(QModelIndex(), rowCount(QModelIndex()), rowCount(QModelIndex()));   // kindly provided by superclass

    m_modules.clear();

    endInsertRows();
}

QHash<int, QByteArray> AutomationProjects::roleNames() const
{
    return { { NameRole, "name" },
        { TypeRole, "type" },
        { ModuleRole, "module" },
    };
}


int AutomationProjects::rowCount(const QModelIndex &parent) const
{
    return m_modules.size();
}

QVariant AutomationProjects::data(const QModelIndex &index, int role) const
{

    //    qDebug()<<" Data asked for "<<index.row()<<" and role "<<role;
    if (index.row()<0 || index.row()>=m_modules.size())
    {
        return {};
    }

    QAutomationModule *module = m_modules.at(index.row());
    if (role == NameRole){
        return module->name();
    }
    if (role == TypeRole){
        return QVariant::fromValue(module->type());
    }

    if (role == ModuleRole){
        //        QVariant var
        return QVariant::fromValue(module);
    }


    return {};

}
