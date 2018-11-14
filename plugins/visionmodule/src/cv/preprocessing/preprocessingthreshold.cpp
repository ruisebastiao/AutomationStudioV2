#include "preprocessingthreshold.h"


using namespace cv;
PreProcessingThreshold::PreProcessingThreshold()
{

    m_type=Type::PreProcessingThreshold;
    m_visualItem="qrc:///PreProcessing/PreProcessingThresholdItem.qml";
    m_name="Threshold";
}

void PreProcessingThreshold::apply(cv::Mat& input, cv::Mat& preprocessed, Mat &original){

    //    threshold((*input->cvMat()),(*preprocessed->cvMat()),value(),255,THRESH_BINARY);
    Mat dst = *new Mat();

    input.copyTo(dst);
    bilateralFilter(input,dst,13,40,40);

    dilate(dst,dst,2);
    //medianBlur(dst,dst,3);

    switch (m_thresholdType) {
    case AdaptativeGaussian:
        adaptiveThreshold(dst,preprocessed,value(),ADAPTIVE_THRESH_GAUSSIAN_C,CV_THRESH_BINARY,m_adaptativeBlockSize,m_adaptativeC);
        break;
    case AdaptativeMean:
        adaptiveThreshold(dst,preprocessed,value(),ADAPTIVE_THRESH_MEAN_C,CV_THRESH_BINARY,m_adaptativeBlockSize,m_adaptativeC);
        break;
    case Simple:
        threshold(dst,preprocessed,value(),255,CV_THRESH_BINARY);
        break;

    }

}
