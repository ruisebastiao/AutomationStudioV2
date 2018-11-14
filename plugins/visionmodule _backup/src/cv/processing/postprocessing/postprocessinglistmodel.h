#ifndef POSTPROCESSINGLISTMODEL_H
#define POSTPROCESSINGLISTMODEL_H

#include <cv/processing/processinglistmodel.h>


class PostProcessingListModel : public ProcessingListModel
{
    Q_OBJECT
    Q_INTERFACES(JsonSerializable)
public:

    PostProcessingListModel(QObject* parent=nullptr);

    // JsonSerializable interface
public:
    void DeSerialize(QJsonObject &json) override;
};

Q_DECLARE_METATYPE(PostProcessingListModel*)

#endif // POSTPROCESSINGLISTMODEL_H
