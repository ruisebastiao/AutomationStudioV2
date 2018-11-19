#include "processingthresholdnode.h"

using namespace cv;

ProcessingThresholdNode::ProcessingThresholdNode()
{
    m_processingType=ProcessingType::ProcessingThresholdNode;
}

QQmlComponent *ProcessingThresholdNode::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/Cv/ProcessingThresholdNodeItem.qml"));
    return delegate.get();

}

void ProcessingThresholdNode::setInput(QMat *input)
{
    
    ProcessingNode::setInput(input);
}

void ProcessingThresholdNode::doProcess()
{

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

        switch (m_thresholdType) {
        case AdaptativeGaussian:
            adaptiveThreshold(*m_input->cvMat(),*targetMat,value(),ADAPTIVE_THRESH_GAUSSIAN_C,CV_THRESH_BINARY,m_adaptativeBlockSize,m_adaptativeC);
            break;
        case AdaptativeMean:
            adaptiveThreshold(*m_input->cvMat(),*targetMat,value(),ADAPTIVE_THRESH_MEAN_C,CV_THRESH_BINARY,m_adaptativeBlockSize,m_adaptativeC);
            break;
        case Simple:
            threshold(*m_input->cvMat(),*targetMat,value(),255,CV_THRESH_BINARY);
            break;

        }

//        targetMat->copyTo(*m_processedMat->cvMat());
    }


    ProcessingNode::doProcess();
}
