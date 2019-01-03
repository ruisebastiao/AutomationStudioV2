#include "modulelistmodel.h"


ModuleListModel::ModuleListModel()
{

}

ModuleListModel::~ModuleListModel()
{

    clear();
}


int ModuleListModel::getAvailableID()
{

    std::sort(std::begin(m_internalList), std::end(m_internalList), [](QAutomationModule* a, QAutomationModule *b) {return a->id() < b->id(); });

    for (int var = 0; var < m_internalList.length()-1; ++var) {
        if(m_internalList.at(var+1)->id()-m_internalList.at(var)->id()>1){
            // check for available ids
            QAutomationModule *module= m_internalList.at(var);
            return module->id()+1;

        }
    }

    return m_internalList.length();
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

