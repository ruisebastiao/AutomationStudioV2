#include "preprocessinggaussian.h"

PreProcessingGaussian::PreProcessingGaussian()
{

    m_type=ProcessingType::PreProcGaussian;
    setName("Gaussian filter");
}


void PreProcessingGaussian::applyPreProcessing(cv::Mat &in, cv::Mat &out)
{
    if(enabled()){
        cv::GaussianBlur(in,out,cv::Size(m_kernelSize,m_kernelSize),0);
        PreProcessing::applyPreProcessing(in,out);
    }
}
