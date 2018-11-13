#include "preprocessingthreshold.h"
#include "opencv2/imgproc.hpp"

using namespace cv;
PreProcessingThreshold::PreProcessingThreshold()
{

    m_type=Type::PreProcessingThreshold;
    m_visualItem="qrc:///PreProcessing/PreProcessingThresholdItem.qml";
    m_name="Threshold";
}

void PreProcessingThreshold::apply(QMat *input, QMat *preprocessed){

    threshold((*input->cvMat()),(*preprocessed->cvMat()),value(),255,THRESH_BINARY);

}
