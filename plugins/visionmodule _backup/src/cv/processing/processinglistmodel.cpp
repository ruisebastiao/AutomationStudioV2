#include "processinglistmodel.h"


void ProcessingListModel::Serialize(QJsonObject &json)
{
    //FlowNode::Serialize(json);

    QJsonArray processingArray;

    for (int i = 0; i < m_processors.length(); ++i) {

        QJsonObject processingObject;

        Processing* processing=static_cast<Processing*>(m_processors.at(i));

        processing->Serialize(processingObject);

        processingArray.append(processingObject);
    }

    json["items"]=processingArray;

}

void ProcessingListModel::DeSerialize(QJsonObject &json)
{
//   JsonSerializable::DeSerialize(json,this);

}

int ProcessingListModel::rowCount(const QModelIndex &parent) const
{
    return m_processors.length();
}
