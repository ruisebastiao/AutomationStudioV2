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

    switch (m_thresholdType) {
    case Adaptative:
        adaptiveThreshold(input,preprocessed,value(),ADAPTIVE_THRESH_MEAN_C,CV_THRESH_BINARY,adaptativeBlockSize(),2);
        break;

    case Simple:
        threshold(input,preprocessed,value(),255,CV_THRESH_BINARY);
        break;

    }

}
