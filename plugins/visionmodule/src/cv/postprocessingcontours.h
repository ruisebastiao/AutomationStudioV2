#ifndef POSTPROCESSINGCONTOURS_H
#define POSTPROCESSINGCONTOURS_H

#include "postprocessing.h"



class PostProcessingContours : public PostProcessing
{
public:
    PostProcessingContours();

    // PostProcessing interface
public:
    virtual void applyPostProcessing(cv::Mat &in, cv::Mat &out) override;
};

#endif // POSTPROCESSINGCONTOURS_H
