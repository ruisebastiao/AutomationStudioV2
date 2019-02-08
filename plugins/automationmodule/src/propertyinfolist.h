#ifndef PROPERTYINFOLIST_H
#define PROPERTYINFOLIST_H

#include "propertyinfo.h"
#include "automationmoduleglobal.h"

#include <serializedlistmodel.h>



class AUTOMATIONMODULE_EXPORT PropertyInfoList:public SerializedListModel<ProperyInfo>
{
    Q_OBJECT
    Q_INTERFACES(JsonSerializable)

public:
    enum InfoRoles {
        PropertyNameRole = Qt::UserRole + 1,
        PropertyValueRole,
        PropertyInfoRole,
        TextRole
    };
    PropertyInfoList();
    PropertyInfoList(const PropertyInfoList& other){ }



    Q_INVOKABLE ProperyInfo* getByValue(QString value){
\
        for (int var = 0; var < m_internalList.length(); ++var) {
            ProperyInfo* info=m_internalList.at(var);
            if(info->propertyValue()==value){
                return info;
            }
        }

        return nullptr;
    }

    Q_INVOKABLE ProperyInfo* getByName(QString name){

        for (int var = 0; var < m_internalList.length(); ++var) {
            ProperyInfo* info=m_internalList.at(var);
            if(info){
                if(info->propertyName()==name){
                    return info;
                }
            }

        }

        return nullptr;
    }

    // QAbstractItemModel interface
public:
    QHash<int, QByteArray> roleNames() const override;

    // QAbstractItemModel interface
public:
    QVariant data(const QModelIndex &index, int role) const override;

    // TypedListModel interface
public:
    Q_INVOKABLE void removeItem(ProperyInfo *item) override;
};



#endif // PROPERTYINFOLIST_H
