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

void ProcessingThresholdNode::setInput(QVariant input)
{
    
    //    if(m_input){
    //        m_input->cvMat()->copyTo(*m_originalInput->cvMat());
    //    }

    ProcessingNode::setInput(input);
}

void ProcessingThresholdNode::doProcess()
{


    QMat* in=m_input.value<QMat*>();
    QMat* mask=m_maskInput.value<QMat*>();

    if(!in || in->cvMat()->empty()){
        return;
    }

    if(enabled()==false){
        m_output=m_input;
    }
    else{



        Mat targetMat;

        if(!mask ||mask->cvMat()->empty()){

            in->cvMat()->copyTo(targetMat);
        }
        else{

            in->cvMat()->copyTo(targetMat,*mask->cvMat());


        }

        switch (m_thresholdType) {
        case AdaptativeGaussian:
            adaptiveThreshold(targetMat,targetMat,value().value<int>(),ADAPTIVE_THRESH_GAUSSIAN_C,CV_THRESH_BINARY,m_adaptativeBlockSize.value<int>(),m_adaptativeC.value<int>());
            break;
        case AdaptativeMean:
            adaptiveThreshold(targetMat,targetMat,value().value<int>(),ADAPTIVE_THRESH_MEAN_C,CV_THRESH_BINARY,m_adaptativeBlockSize.value<int>(),m_adaptativeC.value<int>());
            break;
        case Simple:
            threshold(targetMat,targetMat,value().value<int>(),255,CV_THRESH_BINARY);
            break;

        }

        targetMat.copyTo(*m_output.value<QMat*>()->cvMat());
        //        targetMat->copyTo(*m_processedMat->cvMat());
    }


    ProcessingNode::doProcess();
}
