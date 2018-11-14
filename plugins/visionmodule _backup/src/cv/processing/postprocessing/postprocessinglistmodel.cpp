#include "postprocessingcontours.h"
#include "postprocessinglistmodel.h"

PostProcessingListModel::PostProcessingListModel(QObject* parent):ProcessingListModel(parent)
{

}

void PostProcessingListModel::DeSerialize(QJsonObject &json)
{
    QJsonArray postprocessorsArray = json["items"].toArray();

    for (int i = 0; i < postprocessorsArray.count(); ++i) {


        QJsonObject postprocessingObject=postprocessorsArray[i].toObject();

        if(postprocessingObject["type"]=="PostProcessingContours"){
            PostProcessingContours* item= new PostProcessingContours();
            item->DeSerialize(postprocessingObject);
            this->addProcessor(item);
        }

    }
}

