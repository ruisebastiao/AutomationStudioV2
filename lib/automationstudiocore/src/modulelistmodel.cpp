#include "modulelistmodel.h"

ModuleListModel::ModuleListModel()
{

}

int ModuleListModel::rowCount(const QModelIndex &parent) const
{
    return m_modules.length();
}

QVariant ModuleListModel::data(const QModelIndex &index, int role) const
{
    //    qDebug()<<" Data asked for "<<index.row()<<" and role "<<role;
    if (index.row()<0 || index.row()>=m_modules.size())
    {
        return QVariant();
    }

    Module *module= m_modules.at(index.row());
    if (role == TypeRole){
        return module->moduleType();
    }

    if (role == ModuleInstanceRole){
        return module->moduleInstance();
    }

    if (role == ModuleSettingsRole){
        return module->settingFile();
    }


    if (role == ModuleRole){
        //        QVariant var
        return QVariant::fromValue(module);
    }


    return QVariant();

}

void ModuleListModel::AddModule(Module *module)
{
    beginInsertRows(QModelIndex(), rowCount(QModelIndex()), rowCount(QModelIndex()));   // kindly provided by superclass

    m_modules.append(module);

    endInsertRows();
}

void ModuleListModel::clear()
{
    beginInsertRows(QModelIndex(), rowCount(QModelIndex()), rowCount(QModelIndex()));   // kindly provided by superclass

    m_modules.clear();

    endInsertRows();
}

QHash<int, QByteArray> ModuleListModel::roleNames() const
{
    return {
        { TypeRole, "type" },
        { ModuleInstanceRole, "moduleinstance" },
        { ModuleSettingsRole, "modulesettings" },
        { ModuleRole, "module" },
    };
}

Module *ModuleListModel::getItemAt(int index)
{
   return m_modules.at(index);
}

int ModuleListModel::count()
{
    return m_modules.length();
}
