#ifndef USERSLISTMODEL_H
#define USERSLISTMODEL_H

#include"automationstudiocoreglobal.h"

#include <QAbstractListModel>
#include <QObject>

#include "user.h"

namespace as{

class AUTOMATIONSTUDIO_CORE_EXPORT UsersListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(MyRoles)
public:

    enum MyRoles {
        NameRole = Qt::UserRole + 1,
        UserRole

    };

    UsersListModel();

public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;


    Q_INVOKABLE User* getItemAt(int index);

    void AddUser(User *user);
    void clear();
    QHash<int, QByteArray> roleNames() const;
private:
    QList<User*> m_users;
};

}

#endif // USERSLISTMODEL_H
