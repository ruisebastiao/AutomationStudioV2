#include "preprocessing.h"
#include "preprocessingcontours.h"
#include "preprocessingthreshold.h"

PreProcessing::PreProcessing(QObject *parent) : QObject(parent)
{

}

QString PreProcessing::visualItem() const
{
    return m_visualItem;
}

void PreProcessing::Serialize(QJsonObject &json)
{
    JsonSerializable::Serialize(json,this);
}

void PreProcessing::DeSerialize(QJsonObject &json)
{
    //const bool wasBlocked = this->blockSignals(true);
    // no signals here

    JsonSerializable::DeSerialize(json,this);
   // this->blockSignals(wasBlocked);

    setLoaded(true);


}

void PreProcessingListModel::Serialize(QJsonObject &json)
{
    //FlowNode::Serialize(json);

    QJsonArray preprocessingArray;

    for (int i = 0; i < m_preprocessors.length(); ++i) {

        QJsonObject preprocessingObject;

        PreProcessing* processing=static_cast<PreProcessing*>(m_preprocessors.at(i));

        processing->Serialize(preprocessingObject);

        preprocessingArray.append(preprocessingObject);
    }

    json["items"]=preprocessingArray;

}

void PreProcessingListModel::DeSerialize(QJsonObject &json)
{

    QJsonArray preprocessorsArray = json["items"].toArray();

    for (int i = 0; i < preprocessorsArray.count(); ++i) {


        QJsonObject preprocessingObject=preprocessorsArray[i].toObject();

        if(preprocessingObject["type"]=="PreProcessingThreshold"){


            PreProcessingThreshold* item= new PreProcessingThreshold();
            item->DeSerialize(preprocessingObject);
            this->addPreprocessor(item);
        }
        else if(preprocessingObject["type"]=="PreProcessingContours"){


            PreProcessingContours* item= new PreProcessingContours();
            item->DeSerialize(preprocessingObject);
            this->addPreprocessor(item);
        }

    }
}

int PreProcessingListModel::rowCount(const QModelIndex &parent) const
{
    return m_preprocessors.length();
}
