#ifndef PREPROCESSINGLISTMODEL_H
#define PREPROCESSINGLISTMODEL_H

#include <cv/processing/processinglistmodel.h>



class PreProcessingListModel : public ProcessingListModel
{
    Q_OBJECT
    Q_INTERFACES(JsonSerializable)
public:

    PreProcessingListModel(QObject* parent=nullptr);

    // JsonSerializable interface
public:
    void DeSerialize(QJsonObject &json) override;
};

//qRegisterMetaType<>("PreProcessingListModel*");

Q_DECLARE_METATYPE(PreProcessingListModel*)

#endif // PREPROCESSINGLISTMODEL_H
