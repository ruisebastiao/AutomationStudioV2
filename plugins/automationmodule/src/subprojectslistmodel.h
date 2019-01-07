#ifndef SUBPROJECTSLISTMODEL_H
#define SUBPROJECTSLISTMODEL_H

#include "serializedlistmodel.h"
#include "subproject.h"

class subProjectsListModel:public SerializedListModel<SubProject>
{
    Q_OBJECT
    Q_ENUMS(ListRoles)
    Q_INTERFACES(JsonSerializable)

public:
    enum ListRoles {
        subProjectIDRole = Qt::UserRole + 1,
        subProjectRole,
        subProjectNameRole
    };

    subProjectsListModel();

    Q_INVOKABLE int length();

    inline Q_INVOKABLE int indexOf(SubProject* item){
        return m_internalList.indexOf(item);
    }

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    int getAvailableID()
    {

        std::sort(std::begin(m_internalList), std::end(m_internalList), [](SubProject* a, SubProject *b) {return a->id() < b->id(); });

        for (int var = 0; var < m_internalList.length()-1; ++var) {
            if(m_internalList.at(var+1)->id()-m_internalList.at(var)->id()>1){
                // check for available ids
                SubProject *subproject= m_internalList.at(var);
                return subproject->id()+1;

            }
        }

        return m_internalList.length();
    }

};

#endif // SUBPROJECTSLISTMODEL_H
