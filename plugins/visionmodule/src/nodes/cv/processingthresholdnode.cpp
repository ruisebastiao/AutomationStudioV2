#include "processingthresholdnode.h"

using namespace cv;

ProcessingThresholdNode::ProcessingThresholdNode()
{
    m_processingType=ProcessingType::ProcessingThresholdNode;
    ProcessingNode::processingTypeTable[m_processingType]="Binarization";
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
    
    //    if(m_input){
    //        m_input->cvMat()->copyTo(*m_originalInput->cvMat());
    //    }

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



        Mat targetMat;

        if(!m_maskInput||m_maskInput->cvMat()->empty()){

            m_input->cvMat()->copyTo(targetMat);
        }
        else{

            m_input->cvMat()->copyTo(targetMat,*m_maskInput->cvMat());


        }

        switch (m_thresholdType) {
        case AdaptativeGaussian:
            adaptiveThreshold(targetMat,targetMat,value(),ADAPTIVE_THRESH_GAUSSIAN_C,CV_THRESH_BINARY,m_adaptativeBlockSize,m_adaptativeC);
            break;
        case AdaptativeMean:
            adaptiveThreshold(targetMat,targetMat,value(),ADAPTIVE_THRESH_MEAN_C,CV_THRESH_BINARY,m_adaptativeBlockSize,m_adaptativeC);
            break;
        case Simple:
            threshold(targetMat,targetMat,value(),255,CV_THRESH_BINARY);
            break;

        }

        targetMat.copyTo(*m_output->cvMat());
//        targetMat->copyTo(*m_processedMat->cvMat());
    }


    ProcessingNode::doProcess();
}
