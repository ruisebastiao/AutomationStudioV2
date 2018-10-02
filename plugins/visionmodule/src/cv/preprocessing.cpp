#include "preprocessing.h"



PreProcessing::PreProcessing(QQuickItem *parent)
{

}

void PreProcessing::applyPreProcessing(cv::Mat &in, cv::Mat &out)
{

    out.copyTo(m_processedMat);

}

cv::Mat PreProcessing::getProcessedMat() const
{
    return m_processedMat;
}

void PreProcessing::Serialize(QJsonObject &json)
{
    JsonSerializable::Serialize(json,this);
}

void PreProcessing::DeSerialize(QJsonObject &json)
{
    JsonSerializable::DeSerialize(json,this);
}
