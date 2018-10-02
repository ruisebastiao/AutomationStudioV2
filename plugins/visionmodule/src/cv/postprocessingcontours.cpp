#include "postprocessingcontours.h"

PostProcessingContours::PostProcessingContours()
{

}

void PostProcessingContours::applyPostProcessing(cv::Mat &in, cv::Mat &out)
{



    PostProcessing::applyPostProcessing(in,out);
}
