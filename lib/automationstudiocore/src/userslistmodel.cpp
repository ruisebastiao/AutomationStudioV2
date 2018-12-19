#include "userslistmodel.h"


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


}

void UsersListModel::DeSerialize(QJsonObject &json)
{

}

//void UsersListModel::Serialize(QJsonArray &jsonarray)
//{
//    SerializedListModel::Serialize(jsonarray);


//}

//void UsersListModel::DeSerialize(QJsonArray &jsonarray)
//{
//    SerializedListModel::DeSerialize(jsonarray);
//}




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

