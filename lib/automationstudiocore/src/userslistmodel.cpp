#include "userslistmodel.h"

namespace as {


UsersListModel::UsersListModel()
{

}



QHash<int, QByteArray> UsersListModel::roleNames() const
{
    return {

        { NameRole, "name" },
        { UserRole, "user" }

    };
}

void UsersListModel::Serialize(QJsonObject &json)
{
    QJsonArray itemsArray;
    for (int itemIndex = 0; itemIndex < m_internalList.length(); ++itemIndex) {
        QJsonObject itemObject;

        User *user= m_internalList.at(itemIndex);
        user->Serialize(itemObject);

        itemsArray.append(itemObject);

    }

//    auto teste=json["list"];

    json["list"]=itemsArray;

}

void UsersListModel::DeSerialize(QJsonObject &json)
{
        QJsonArray listArray = json["list"].toArray();
        for (int listIndex = 0; listIndex < listArray.size(); ++listIndex) {
            QJsonObject projectObject = listArray[listIndex].toObject();

            User *item= new User();
            item->DeSerialize(projectObject);

            AddItem(item);

        }
}




QVariant UsersListModel::data(const QModelIndex &index, int role) const
{

    //    qDebug()<<" Data asked for "<<index.row()<<" and role "<<role;
    if (index.row()<0 || index.row()>=m_internalList.length())
    {
        return {};
    }

    User *user = m_internalList.at(index.row());
    if (role == NameRole) return user->name();
    if (role == UserRole){
        //        QVariant var
        return QVariant::fromValue(user);
    }


    return {};

}
}
