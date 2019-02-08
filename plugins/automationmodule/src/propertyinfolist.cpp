#include "propertyinfolist.h"


PropertyInfoList::PropertyInfoList()
{

}

QHash<int, QByteArray> PropertyInfoList::roleNames() const
{
    return {

        { PropertyNameRole, "propertyName" },
        { PropertyValueRole, "propertyValue" },
        { PropertyInfoRole, "propertyInfo" },
        { TextRole, "textRole" },


    };

}

QVariant PropertyInfoList::data(const QModelIndex &index, int role) const
{
    if (index.row()<0 || index.row()>=m_internalList.length())
    {
        return QVariant(QString("???"));
    }

    ProperyInfo *info= m_internalList.at(index.row());
    if (role == PropertyNameRole)
        return info->propertyName();
    if (role == PropertyValueRole){

        return QVariant::fromValue(info->propertyValue());
    }

    if (role == PropertyInfoRole){

        return QVariant::fromValue(info);
    }

    if (role == TextRole){

        QString text;
        text=info->propertyName()+"|"+info->propertyValue();
        return QVariant::fromValue(text);
    }
    return QVariant(QString("???"));
}

void PropertyInfoList::removeItem(ProperyInfo *item)
{
    SerializedListModel<ProperyInfo>::removeItem(item);
}

