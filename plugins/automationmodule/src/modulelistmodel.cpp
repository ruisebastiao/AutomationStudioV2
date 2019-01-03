#include "modulelistmodel.h"


ModuleListModel::ModuleListModel()
{

}

ModuleListModel::~ModuleListModel()
{

    clear();
}

QVariant ModuleListModel::data(const QModelIndex &index, int role) const
{
    //    qDebug()<<" Data asked for "<<index.row()<<" and role "<<role;
    if (index.row()<0 || index.row()>=m_internalList.length())
    {
        return QVariant();
    }

    QAutomationModule *module= m_internalList.at(index.row());
    if (role == TypeRole){
        return module->type();
    }

//    if (role == ModuleInstanceRole){
//        return module->moduleInstance();
//    }



    if (role == ModuleRole){
        //        QVariant var
        return QVariant::fromValue(module);
    }

    if(role==ModuleIDRole){
        return QVariant::fromValue(module->id());

    }

    if(role==ModuleNameRole){
        return QVariant::fromValue(module->name());

    }


    return QVariant();

}


QHash<int, QByteArray> ModuleListModel::roleNames() const
{
    return {
        { TypeRole, "type" },
        { ModuleInstanceRole, "moduleinstance" },
        { ModuleSettingsRole, "modulesettings" },
        { ModuleRole, "module" },
        { ModuleNameRole, "moduleName" },
        { ModuleIDRole, "moduleID" }
    };
}

void ModuleListModel::removeItem(QAutomationModule *item)
{
    TypedListModel<QAutomationModule>::removeItem(item);
}

