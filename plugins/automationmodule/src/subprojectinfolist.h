#ifndef SUBPROJECTINFOLIST_H
#define SUBPROJECTINFOLIST_H

#include "subprojectinfo.h"

#include <serializedlistmodel.h>



class SubProjectInfoList:public SerializedListModel<SubProjectInfo>
{
    Q_OBJECT
    Q_INTERFACES(JsonSerializable)

public:
    enum InfoRoles {
        ProjectNameRole = Qt::UserRole + 1,
        IDRole,
        InfoRole,
        TextRole
    };
    SubProjectInfoList();
    SubProjectInfoList(const SubProjectInfoList& other){ }



    Q_INVOKABLE SubProjectInfo* getById(QString id){

        for (int var = 0; var < m_internalList.length(); ++var) {
            SubProjectInfo* info=m_internalList.at(var);
            if(info->id()==id){
                return info;
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
    Q_INVOKABLE void removeItem(SubProjectInfo *item) override;
};



#endif // SUBPROJECTINFOLIST_H
