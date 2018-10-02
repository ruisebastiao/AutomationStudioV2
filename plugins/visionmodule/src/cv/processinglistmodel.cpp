#include "processinglistmodel.h"

ProcessingListModel::ProcessingListModel(QObject *parent)
    : QAbstractListModel(parent)
{

}

void ProcessingListModel::addProcessing(Processing *item)
{
    beginInsertRows(QModelIndex(), m_list.size(), m_list.size());
    m_list.append(item);
    endInsertRows();
    emit newProcessingAdded(item);

}

int ProcessingListModel::rowCount(const QModelIndex &parent) const
{
    return m_list.size();
}


QVariant ProcessingListModel::data(const QModelIndex &index, int role) const
{
    if ( index.row() >= m_list.size() )
        return QVariant();

    if ( role == ProcessingRole )
        return QVariant::fromValue(m_list[index.row()]);
    if ( role == ProcessingNameRole ){

        return QVariant::fromValue(m_list[index.row()]->name());
    }

    return QVariant();
}

Processing* ProcessingListModel::at(int index)
{
    if ( index < m_list.size() )
        return m_list.at(index);
    return nullptr;
}


int ProcessingListModel::size() const
{
    return m_list.size();
}


QHash<int, QByteArray> ProcessingListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ProcessingRole] = "processing";
    roles[ProcessingNameRole] = "name";
    return roles;
}
