#ifndef POSTPROCESSING_H
#define POSTPROCESSING_H

#include <jsonserializable.h>

#include "opencv2/imgproc.hpp"

#include "processing.h"


class PostProcessing: public Processing,public JsonSerializable
{
    Q_OBJECT


public:
    PostProcessing();

    virtual void applyPostProcessing(cv::Mat &in,cv::Mat &out);

    // JsonSerializable interface
protected:
    virtual void Serialize(QJsonObject &json) override;
    virtual void DeSerialize(QJsonObject &json) override;
};

#endif // POSTPROCESSING_H
