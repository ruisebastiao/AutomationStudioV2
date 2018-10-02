#include "preprocessingthreshold.h"

PreProcessingThreshold::PreProcessingThreshold()
{

    m_type=ProcessingType::PreProcThreshold;
    setName("Threshold");
}

void PreProcessingThreshold::applyPreProcessing(cv::Mat &in, cv::Mat &out)
{
    if(enabled()){

        cv::threshold(in,out,m_value, 255,cv::THRESH_BINARY );

        PreProcessing::applyPreProcessing(in,out);
    }
}
