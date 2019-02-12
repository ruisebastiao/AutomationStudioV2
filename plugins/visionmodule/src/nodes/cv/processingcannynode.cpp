#include "processingcannynode.h"

ProcessingCannyNode::ProcessingCannyNode()
{

    m_processingType=ProcessingType::ProcessingCannyNode;

}


QQmlComponent *ProcessingCannyNode::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/Cv/ProcessingCannyNodeItem.qml"));
    return delegate.get();

}

void ProcessingCannyNode::setInput(QVariant input)
{
    //    if(m_input){
    //        m_input->cvMat()->copyTo(*m_originalInput->cvMat());
    //    }

    ProcessingNode::setInput(input);
}

void ProcessingCannyNode::doProcess()
{
    if(disabled().value<bool>()){
        return;
    }

    int scale = delta();
     int delta = 10;
     int ddepth = CV_16S;

    // TODO
    // value colde be read once at variant change
    QMat* in=m_input.value<QMat*>();

    // TODO move local vars to protected
    QMat* output=m_output.value<QMat*>();
    QMat* drawsource=m_drawSource.value<QMat*>();


    int thresh = 100;
    int max_thresh = 255;

    if(!in || in->cvMat()->empty()){
        return;
    }

    /// Detect edges using canny
//    Canny( *in->cvMat(), *output->cvMat(), thresh, thresh*2, 3 );

    /// Generate grad_x and grad_y
     cv::Mat grad_x, grad_y;
     cv::Mat abs_grad_x, abs_grad_y;

     /// Gradient X
     //Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
     Sobel( *in->cvMat(), grad_x, ddepth, 1, 0, 3, scale, delta, cv::BORDER_DEFAULT );
     convertScaleAbs( grad_x, abs_grad_x );

     /// Gradient Y
     //Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
     Sobel( *in->cvMat(), grad_y, ddepth, 0, 1, 3, scale, delta, cv::BORDER_DEFAULT );
     convertScaleAbs( grad_y, abs_grad_y );

     /// Total Gradient (approximate)
     addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, *output->cvMat() );

    ProcessingNode::doProcess();
}
