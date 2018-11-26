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

void ProcessingFilterNode::setInput(QMat *input)
{

    ProcessingNode::setInput(input);
}

void ProcessingFilterNode::doProcess()
{
    if(!m_input || m_input->cvMat()->empty()){
        return;
    }

    if(enabled()==false){
        m_output=m_input;
    }
    else{

        if(!m_input || m_input->cvMat()->empty()){
            return;
        }

        if(enabled()==false){
            m_output=m_input;
        }
        else{



            Mat* targetMat;

            //    setInPlaceProcessing(true);
            if(inPlaceProcessing()){
                targetMat=m_input->cvMat();
                m_output=m_input;
            }
            else{
                targetMat=m_output->cvMat();
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


            bilateralFilter(*m_input->cvMat(),*targetMat,13,40,40);


        }
    }
    ProcessingNode::doProcess();



}
