#include "subprojectinfonode.h"

SubProjectInfoNode::SubProjectInfoNode()
{
    m_type=Type::SubProjectInfoNode;
}

QQmlComponent *SubProjectInfoNode::delegate(QQmlEngine &engine)  noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/SubProjectInfoNodeItem.qml"));
    return delegate.get();
}

SubProjectInfo::SubProjectInfo()
{

}

SubProjectInfo::SubProjectInfo(QString id, QString projectname)
{
    setId(id);
    setProjectName(projectname);
}

void SubProjectInfo::Serialize(QJsonObject &json)
{
    JsonSerializable::Serialize(json,this);
}

void SubProjectInfo::DeSerialize(QJsonObject &json)
{
    JsonSerializable::DeSerialize(json,this);
}

SubProjectInfoList::SubProjectInfoList()
{

}

QHash<int, QByteArray> SubProjectInfoList::roleNames() const
{
    return {

        { ProjectNameRole, "infoProjectName" },
        { IDRole, "infoID" },
        { InfoRole, "info" },
        { TextRole, "textRole" },


    };

}

QVariant SubProjectInfoList::data(const QModelIndex &index, int role) const
{
    if (index.row()<0 || index.row()>=m_internalList.length())
    {
        return QVariant();
    }

    SubProjectInfo *info= m_internalList.at(index.row());
    if (role == ProjectNameRole)
        return info->projectName();
    if (role == IDRole){

        return QVariant::fromValue(info->id());
    }

    if (role == InfoRole){

        return QVariant::fromValue(info);
    }

    if (role == TextRole){

        QString text;
        text=info->id()+"|"+info->projectName();
        return QVariant::fromValue(text);
    }
    return QVariant();
}

void SubProjectInfoList::removeItem(SubProjectInfo *item)
{
    SerializedListModel<SubProjectInfo>::removeItem(item);
}
