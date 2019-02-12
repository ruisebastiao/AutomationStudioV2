#include "processingfilternode.h"
using namespace cv;


ProcessingFilterNode::ProcessingFilterNode()
{

    m_processingType=ProcessingType::ProcessingFilterNode;

}


QQmlComponent *ProcessingFilterNode::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/Cv/ProcessingFilterNodeItem.qml"));
    return delegate.get();

}

void ProcessingFilterNode::setInput(QVariant input)
{

    ProcessingNode::setInput(input);
}

void ProcessingFilterNode::doProcess()
{


    if(disabled().value<bool>()){
        return;
    }
    QMat* in=m_input.value<QMat*>();
    QMat* out=m_output.value<QMat*>();


    if(!in || in->cvMat()->empty() || !out){
        // TODO Send Error
        return;
    }



    if(enabled()==false){
        m_output=m_input;
    }
    else{





        Mat* targetMat;

        //    setInPlaceProcessing(true);
        if(inPlaceProcessing()){
            targetMat=in->cvMat();
            m_output=m_input;
        }
        else{
            targetMat=out->cvMat();
        }

        //            switch (m_thresholdType) {
        //            case AdaptativeGaussian:
        //                adaptiveThreshold(*m_input->cvMat(),*targetMat,value(),ADAPTIVE_THRESH_GAUSSIAN_C,CV_THRESH_BINARY,m_adaptativeBlockSize,m_adaptativeC);
        //                break;
        //            case AdaptativeMean:
        //                adaptiveThreshold(*m_input->cvMat(),*targetMat,value(),ADAPTIVE_THRESH_MEAN_C,CV_THRESH_BINARY,m_adaptativeBlockSize,m_adaptativeC);
        //                break;
        //            case Simple:
        //                threshold(*m_input->cvMat(),*targetMat,value(),255,CV_THRESH_BINARY);
        //                break;


        bilateralFilter(*in->cvMat(),*targetMat,13,40,40);



    }
    ProcessingNode::doProcess();



}
