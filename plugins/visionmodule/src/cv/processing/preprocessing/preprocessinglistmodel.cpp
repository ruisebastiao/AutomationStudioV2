#include "preprocessinglistmodel.h"
#include "preprocessingthreshold.h"

PreProcessingListModel::PreProcessingListModel(QObject* parent):ProcessingListModel(parent)
{

}

void PreProcessingListModel::DeSerialize(QJsonObject &json)
{
    QJsonArray preprocessorsArray = json["items"].toArray();

    for (int i = 0; i < preprocessorsArray.count(); ++i) {


        QJsonObject preprocessingObject=preprocessorsArray[i].toObject();

        if(preprocessingObject["type"]=="PreProcessingThreshold"){


            PreProcessingThreshold* item= new PreProcessingThreshold();
            item->DeSerialize(preprocessingObject);
            this->addProcessor(item);
        }
    }
}
