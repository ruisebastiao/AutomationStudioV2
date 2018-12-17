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
#include <nodes/cv/processinglogicalnode.h>
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


void ROINode::Serialize(QJsonObject &json)
{
    FlowNode::Serialize(json);
    
    QJsonArray processingnodesArray;
    
    for (int i = 0; i < m_ProcessingNodes->length(); ++i) {
        
        QJsonObject processingnodeObject;
        
        FlowNode* processing=static_cast<FlowNode*>(m_ProcessingNodes->at(i));
        
        processing->Serialize(processingnodeObject);
        
        processingnodesArray.append(processingnodeObject);
    }
    
    json["processingnodes"]=processingnodesArray;
    

    
}




void ROINode::initializeProcessingNode(ProcessingNode* procnode){
    
    if(procnode){
//        connect(procnode,&FlowNode::removeNode,[&](FlowNode* nodetoremove){
//            int nodepos=m_ProcessingNodes.indexOf( nodetoremove);
//            if(nodepos>0){
//                FlowNode* noderemoved=m_ProcessingNodes.at(nodepos);
//                if(noderemoved){
//                    m_ProcessingNodes.removeAll(noderemoved);
//                    this->m_roiEditorGraphView->getGraph()->removeNode(noderemoved);
                    
//                }
                
//            }
//        });
        
        
        
        
        //        procnode->setDrawSource(this->processedFrame());
        
        if(procnode->processingType()==ProcessingNode::ProcessingType::ProcessingBaseNode){
            m_basenode=qobject_cast<ProcessingBaseNode*>(procnode);
        }
        
        
        
        
        
        QObject::connect(procnode,&ProcessingNode::processingCompleted,this, [this](ProcessingNode* endnode){
            QMat* processed= endnode->output().value<QMat*>();
            m_processedFrame=processed;
            emit processedFrameChanged(processed);
            setRoiProcessingDone(true);
        });
        

    }
    
    
    
}


void ROINode::DeSerialize(QJsonObject &json)
{
    FlowNode::DeSerialize(json);
    
    
    
//    QJsonArray processingArray = json["processingnodes"].toArray();
    
//    for (int i = 0; i < processingArray.count(); ++i) {
        
        
        
        
//        QJsonObject processingObject=processingArray[i].toObject();
        
        
//        ProcessingNode* procnode=readProcessingNode(m_roiEditorGraphView,processingObject);
        
//        initializeProcessingNode(procnode);
        
        
        
        
//    }
    
//    emit processingNodeTypesChanged(m_processingNodeTypes);
    
    
//    QJsonArray commonNodesArray = json["commonnodes"].toArray();
    
//    for (int i = 0; i < commonNodesArray.count(); ++i) {
        
        
//        QJsonObject commonnodeObject=commonNodesArray[i].toObject();
//        ProcessingSceneGraph* procscene=dynamic_cast<ProcessingSceneGraph*>(m_roiEditorGraphView);
//        FlowNode* commonnode=procscene->createNode(commonnodeObject["type"].toString());
//        if(commonnode){
//            commonnode->DeSerialize(commonnodeObject);
//        }
//        m_CommonNodes.append(commonnode);
        
        
//    }

       
}



//void ROINode::addProcNode(QPoint loc,QVariantMap nodeinfo){
//    qDebug()<<"Adding Processing node:"<<nodeinfo<<" @ "<<loc;
    

    
//    ProcessingNode *procnode=createProcessingNode(m_roiEditorGraphView,procType);
    
//    if(procnode){
//        procnode->getItem()->setProperty("x",QVariant::fromValue(loc.x()));
//        procnode->getItem()->setProperty("y",QVariant::fromValue(loc.y()));
        
        
        
//        int nodeid=FlowNode::getAvailableID(QAutomationModule::flownodemanager->flownodes());
//        if(nodeid==-1){
//            nodeid=QAutomationModule::flownodemanager->length();
//        }
//        procnode->setId(nodeid);
//        emit QAutomationModule::flownodemanager->onFlowNodeLoaded(procnode);
        
        
//        initializeProcessingNode(procnode);
        
//        QJsonObject Qo;
//        procnode->initializePorts(Qo);
        
//        procnode->initializeNode();
        
        
        
//    }
//}



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
        
        
        
        //        emit sourceFrameChanged(m_sourceFrame);
        
        m_basenode->setInput(QVariant::fromValue(m_sourceFrame));
        
    }
    
    
}

void ROINode::setRoiProcessingDone(bool roiProcessingDone)

{
    
    m_roiProcessingDone = roiProcessingDone;
    emit processedFrameChanged(m_processedFrame);
    
    LOG_INFO()<<"ROI Processing Done";
    
    emit roiProcessingDoneChanged(m_roiProcessingDone);
}
