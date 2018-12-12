#include "modulelistmodel.h"

ModuleListModel::ModuleListModel()
{

}

ModuleListModel::~ModuleListModel()
{

    clear();
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

    if(role==ModuleIDRole){
        return QVariant::fromValue(module->moduleID());

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

    if(m_modules.length()>0){

        beginRemoveRows(QModelIndex(), 0,m_modules.length()-1);   // kindly provided by superclass

        foreach (Module* module, m_modules) {
            module->deleteLater();
        }

        m_modules.clear();

        endRemoveRows();

    }


}

QHash<int, QByteArray> ModuleListModel::roleNames() const
{
    return {
        { TypeRole, "type" },
        { ModuleInstanceRole, "moduleinstance" },
        { ModuleSettingsRole, "modulesettings" },
        { ModuleRole, "module" },
        { ModuleIDRole, "moduleID" }
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
