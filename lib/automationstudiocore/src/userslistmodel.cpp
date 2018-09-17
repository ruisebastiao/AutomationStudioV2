#include "userslistmodel.h"

namespace as {


UsersListModel::UsersListModel()
{
    m_users.clear();
}

void UsersListModel::AddUser(User* user){
    beginInsertRows(QModelIndex(), rowCount(QModelIndex()), rowCount(QModelIndex()));   // kindly provided by superclass

    m_users.append(user);

    endInsertRows();
}


void UsersListModel::clear(){
    beginInsertRows(QModelIndex(), rowCount(QModelIndex()), rowCount(QModelIndex()));   // kindly provided by superclass

    m_users.clear();

    endInsertRows();
}

QHash<int, QByteArray> UsersListModel::roleNames() const
{
    return {

        { NameRole, "name" },
        { UserRole, "user" }

    };
}


User* UsersListModel::getItemAt(int index){
    if(index<m_users.length()){
        return m_users.at(index);
    }
    else {
        return nullptr;
    }
}


int UsersListModel::rowCount(const QModelIndex &parent) const
{
    return m_users.size();
}

QVariant UsersListModel::data(const QModelIndex &index, int role) const
{

    //    qDebug()<<" Data asked for "<<index.row()<<" and role "<<role;
    if (index.row()<0 || index.row()>=m_users.size())
    {
        return {};
    }

    User *user = m_users.at(index.row());
    if (role == NameRole) return user->name();
    if (role == UserRole){
        //        QVariant var
        return QVariant::fromValue(user);
    }


    return {};

}
}
