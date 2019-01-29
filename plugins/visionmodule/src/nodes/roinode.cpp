#include "roinode.h"
#include "QObject"
#include "qautomationmodule.h"

#include <nodes/cv/processingbasenode.h>
#include <nodes/cv/processingcontoursnode.h>
#include <nodes/cv/processingdrawingnode.h>
#include <nodes/cv/processingenclosingnode.h>
#include <nodes/cv/processingendnode.h>
#include <nodes/cv/processingfilternode.h>
#include <nodes/cv/processinggeometricnode.h>
#include <nodes/cv/processingmasknode.h>
#include <nodes/cv/processingthresholdnode.h>

#include <graphs/processingscenegraph.h>


using namespace cv;

ROINode::ROINode()
{
    m_type=Type::ROINode;
}


ROINode::~ROINode()
{
    
    
}

QQmlComponent *ROINode::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/ROINodeItem.qml"));
    return delegate.get();
    
}

QVariant ROINode::roiResults() const
{
    return m_roiResults;
}


void ROINode::Serialize(QJsonObject &json)
{
    FlowNode::Serialize(json);
}




void ROINode::initializeProcessingNode(ProcessingNode* procnode){
    
    if(procnode){
        
        
        //        procnode->setDrawSource(this->processedFrame());
        
        if(procnode->processingType()==ProcessingNode::ProcessingType::ProcessingBaseNode){
            m_basenode=qobject_cast<ProcessingBaseNode*>(procnode);
        }
        
        
        
        
        
        QObject::connect(procnode,&ProcessingNode::processingCompleted,this, [this](ProcessingNode* node){

            ProcessingEndNode* endnode=dynamic_cast<ProcessingEndNode*>(node);

            if(endnode){
                QMat* processed= endnode->output().value<QMat*>();
                this->m_roiResults=endnode->processingResults();
                m_processedFrame=processed;
                emit processedFrameChanged(processed);
                setRoiProcessingDone(true);
            }

        });
        

    }
    
    
    
}


void ROINode::DeSerialize(QJsonObject &json)
{
    FlowNode::DeSerialize(json);
}

void ROINode::processFrameObject(QMat *frame)
{
    
    setSourceFrame(frame);
    
}

void ROINode::setSourceFrame(QMat *sourceFrame)
{
    
    
    if (sourceFrame &&  sourceFrame->cvMat()->cols >= getItem()->x() + getItem()->width() && sourceFrame->cvMat()->rows >= getItem()->y() +getItem()->height()){
        
        const cv::Mat &in=*sourceFrame->cvMat();
        
        in(cv::Rect( getItem()->x(),  getItem()->y(),  getItem()->width(),  getItem()->height())).copyTo(*m_sourceFrame->cvMat());
        
        
        cvtColor(*m_sourceFrame->cvMat(),*m_processedFrame->cvMat(),CV_GRAY2BGR);
        
        m_roiResults.clear();
        
        //        emit sourceFrameChanged(m_sourceFrame);
        

        if(m_basenode){
            m_basenode->setInput(QVariant::fromValue(m_sourceFrame));
        }

        
    }
    
    
}

void ROINode::setRoiProcessingDone(bool roiProcessingDone)

{
    
    m_roiProcessingDone = roiProcessingDone;
    emit processedFrameChanged(m_processedFrame);
    
    LOG_INFO()<<"ROI Processing Done";
    
    emit roiProcessingDoneChanged(m_roiProcessingDone);
}
