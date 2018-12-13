#ifndef USERSLISTMODEL_H
#define USERSLISTMODEL_H

#include"automationstudiocoreglobal.h"

#include <QObject>

#include "serializedlistmodel.h"
#include "user.h"

namespace as{

class AUTOMATIONSTUDIO_CORE_EXPORT UsersListModel : public SerializedListModel<User>
{
    Q_OBJECT
    Q_ENUMS(MyRoles)

    Q_INTERFACES(JsonSerializable)

public:

    enum MyRoles {
        NameRole = Qt::UserRole + 1,
        UserRole

    };

    UsersListModel();

public:

    QVariant data(const QModelIndex &index, int role) const override;


    QHash<int, QByteArray> roleNames() const override;


    // JsonSerializable interface
public:
    virtual void Serialize(QJsonObject &json) override;
    virtual void DeSerialize(QJsonObject &json) override;
};

}

#endif // USERSLISTMODEL_H
