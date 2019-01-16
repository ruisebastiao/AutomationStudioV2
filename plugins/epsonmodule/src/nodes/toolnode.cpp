#include "toolnode.h"

ToolNode::ToolNode()
{
    m_type=Type::ToolNode;
}

QQmlComponent *ToolNode::delegate(QQmlEngine &engine)  noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/ToolNodeItem.qml"));
    return delegate.get();
}

ToolInfo::ToolInfo()
{

}

ToolInfo::ToolInfo(QString id, QString projectname)
{
    setId(id);
    setProjectName(projectname);
}

void ToolInfo::Serialize(QJsonObject &json)
{
    JsonSerializable::Serialize(json,this);
}

void ToolInfo::DeSerialize(QJsonObject &json)
{
    JsonSerializable::DeSerialize(json,this);
}

ToolInfoList::ToolInfoList()
{

}

QHash<int, QByteArray> ToolInfoList::roleNames() const
{
    return {

        { ProjectNameRole, "toolProjectName" },
        { IDRole, "toolID" },
        { ToolRole, "tool" },
        { TextRole, "textRole" },


    };

}

QVariant ToolInfoList::data(const QModelIndex &index, int role) const
{
    if (index.row()<0 || index.row()>=m_internalList.length())
    {
        return QVariant();
    }

    ToolInfo *tool= m_internalList.at(index.row());
    if (role == ProjectNameRole)
        return tool->projectName();
    if (role == IDRole){

        return QVariant::fromValue(tool->id());
    }

    if (role == ToolRole){

        return QVariant::fromValue(tool);
    }

    if (role == TextRole){

        QString text;
        text=tool->id()+"|"+tool->projectName();
        return QVariant::fromValue(text);
    }
    return QVariant();
}

void ToolInfoList::removeItem(ToolInfo *item)
{
    SerializedListModel<ToolInfo>::removeItem(item);
}
