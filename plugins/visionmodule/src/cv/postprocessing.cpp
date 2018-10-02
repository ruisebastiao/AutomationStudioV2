#include "postprocessing.h"



PostProcessing::PostProcessing()
{

}

void PostProcessing::applyPostProcessing(cv::Mat &in,cv::Mat &out)
{

}

void PostProcessing::Serialize(QJsonObject &json)
{
    JsonSerializable::Serialize(json,this);
}

void PostProcessing::DeSerialize(QJsonObject &json)
{
    JsonSerializable::DeSerialize(json,this);
}
