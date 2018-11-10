#include "processingcornerharrisnode.h"

using namespace cv;

ProcessingCornerHarrisNode::ProcessingCornerHarrisNode()
{
    m_type=Type::ProcessingCornerHarrisNode;
}



QQmlComponent *ProcessingCornerHarrisNode::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   qan_FlowNode_delegate;
    if ( !qan_FlowNode_delegate )
        qan_FlowNode_delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/Cv/ProcessingCornerHarrisNodeItem.qml"));
    return qan_FlowNode_delegate.get();

}

void ProcessingCornerHarrisNode::setInput(QMat *input)
{

    ProcessingNode::setInput(input);
    process();
}

void ProcessingCornerHarrisNode::doProcess()
{
    if(!m_input){
        return;
    }

    RNG rng(12345);

    int maxCorners = 23;

    /// Parameters for Shi-Tomasi algorithm
       maxCorners = MAX(maxCorners, 1);
       std::vector<Point2f> corners;
       double qualityLevel = 0.5;
       double minDistance = 10;
       int blockSize = 3, gradientSize = 5;
       bool useHarrisDetector = false;
       double k = 0.04;

       /// Copy the source image
       Mat copy = (*m_input->cvMat()).clone();

       /// Apply corner detection
       goodFeaturesToTrack( *m_input->cvMat(),
                            corners,
                            maxCorners,
                            qualityLevel,
                            minDistance,
                            Mat(),
                            blockSize,
                            gradientSize,
                            useHarrisDetector,
                            k );


       /// Draw corners detected
       LOG_INFO() << "** Number of corners detected: " << corners.size();
       int radius = 4;
       for( size_t i = 0; i < corners.size(); i++ )
       {
           circle( copy, corners[i], radius, Scalar(rng.uniform(0,255), rng.uniform(0, 256), rng.uniform(0, 256)), FILLED );
       }


    copy.copyTo((*m_output->cvMat()));

    //    Mat corners, dilated_corners;
    //    preCornerDetect(image, corners, 3);
    //    // dilation with 3x3 rectangular structuring element
    //    dilate(corners, dilated_corners, Mat(), 1);
    //    Mat corner_mask = corners == dilated_corners;



    //   dilate(*m_output->cvMat(),*m_output->cvMat(),1);

    emit outputChanged(m_output);
    ProcessingNode::doProcess();

}
