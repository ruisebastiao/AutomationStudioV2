#include "roinode.h"
#include "QObject"

#include <nodes/cv/processingbasenode.h>
#include <nodes/cv/processingcontoursnode.h>
#include <nodes/cv/processingenclosingnode.h>
#include <nodes/cv/processingendnode.h>
#include <nodes/cv/processingfilternode.h>
#include <nodes/cv/processinggeometricnode.h>
#include <nodes/cv/processinglogicalnode.h>
#include <nodes/cv/processingthresholdnode.h>


using namespace cv;

ROINode::ROINode()
{
    m_type=Type::ROINode;
}

ROINode::~ROINode()
{
    m_roiEditorGraphView->deleteLater();
    for (int var = 0; var < m_ProcessingNodes.length(); ++var) {
        ProcessingNode* procnode= qobject_cast<ProcessingNode*>(m_ProcessingNodes.at(var));
        procnode->setParent(nullptr);
        procnode->deleteLater();
    }
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

    for (int i = 0; i < m_ProcessingNodes.length(); ++i) {

        QJsonObject processingnodeObject;

        FlowNode* processing=static_cast<FlowNode*>(m_ProcessingNodes.at(i));

        processing->Serialize(processingnodeObject);

        processingnodesArray.append(processingnodeObject);
    }

    json["processingnodes"]=processingnodesArray;


}


ProcessingNode *ROINode::readProcessingNode(qan::GraphView *graphView, QJsonObject nodeobject)
{
    qan::Node* newnode=nullptr;

    if(nodeobject["processingType"]=="ProcessingBaseNode"){
        newnode=graphView->getGraph()->insertNode<ProcessingBaseNode>(nullptr);
    }
    else if(nodeobject["processingType"]=="ProcessingThresholdNode"){
        newnode=graphView->getGraph()->insertNode<ProcessingThresholdNode>(nullptr);
    }
    else if(nodeobject["processingType"]=="ProcessingFilterNode"){
        newnode=graphView->getGraph()->insertNode<ProcessingFilterNode>(nullptr);
    }
    else if(nodeobject["processingType"]=="ProcessingEndNode"){
        newnode=graphView->getGraph()->insertNode<ProcessingEndNode>(nullptr);
    }
    else if(nodeobject["processingType"]=="ProcessingContoursNode"){
        newnode=graphView->getGraph()->insertNode<ProcessingContoursNode>(nullptr);
    }
    else if(nodeobject["processingType"]=="ProcessingLogicalNode"){
        newnode=graphView->getGraph()->insertNode<ProcessingLogicalNode>(nullptr);
    }
    else if(nodeobject["processingType"]=="ProcessingEnclosingNode"){
        newnode=graphView->getGraph()->insertNode<ProcessingEnclosingNode>(nullptr);
    }
    else if(nodeobject["processingType"]=="ProcessingGeometricNode"){
        newnode=graphView->getGraph()->insertNode<ProcessingGeometricNode>(nullptr);
    }
    else{
        LOG_WARNING(QString("Unknown nodeobject processingType:%1").arg(nodeobject["processingType"].toString()));
    }

    ProcessingNode* node=dynamic_cast<ProcessingNode*>(newnode);
    if(node){
        node->DeSerialize(nodeobject);

        //    connect()

    }



    return node;

}



void ROINode::DeSerialize(QJsonObject &json)
{
    FlowNode::DeSerialize(json);



    QJsonArray processingArray = json["processingnodes"].toArray();

    for (int i = 0; i < processingArray.count(); ++i) {



        FlowNode* node=nullptr;
        ProcessingNode* procnode=nullptr;

        QJsonObject processingObject=processingArray[i].toObject();


        node=readProcessingNode(m_roiEditorGraphView,processingObject);



        procnode=qobject_cast<ProcessingNode*>(node);
        if(procnode){
            procnode->setOriginalFrame(this->processedFrame());
            if(procnode->processingType()==ProcessingNode::ProcessingType::ProcessingBaseNode){
                node->bindSourceProperty(this,"sourceFrame","input");
                m_basenode=qobject_cast<ProcessingBaseNode*>(procnode);
            }




            QObject::connect(procnode,&ProcessingNode::isBaseNodeChanged,this, [&](bool isbase){

                if(isbase){
                    node->bindSourceProperty(this,"sourceFrame","input");
                }
                else{
                    node->unbindSourceProperty("input");
                }

            });



            QObject::connect(procnode,&ProcessingNode::processingCompleted,this, [this](ProcessingNode* endnode){
//                emit processedFrameChanged(m_processedFrame);
                setRoiProcessingDone(true);
            });




        }


        if(node){
            m_ProcessingNodes.append(node);
        }



    }

    FlowNode::loadNodeConnections(m_ProcessingNodes);

    setConfigsLoaded(true);




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


        emit sourceFrameChanged(m_sourceFrame);



    }


}

void ROINode::setRoiProcessingDone(bool roiProcessingDone)

{

    m_roiProcessingDone = roiProcessingDone;
    emit processedFrameChanged(m_processedFrame);

    LOG_INFO()<<"ROI Processing Done";

    emit roiProcessingDoneChanged(m_roiProcessingDone);
}
