#include "roinode.h"
#include "QObject"


#include <src/nodes/cv/processingthresholdnode.h>

#include <src/nodes/cv/processingcontoursnode.h>
#include <src/nodes/cv/processingshapesnode.h>

#include <nodes/cv/cannyedgesnode.h>


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

    QJsonArray preprocessingArray;

    for (int i = 0; i < m_ProcessingNodes.length(); ++i) {

        QJsonObject preprocessingObject;

        FlowNode* processing=static_cast<FlowNode*>(m_ProcessingNodes.at(i));

        processing->Serialize(preprocessingObject);

        preprocessingArray.append(preprocessingObject);
    }

    json["processing"]=preprocessingArray;


}


ProcessingNode *ROINode::readProcessingNode(qan::GraphView *graphView, QJsonObject nodeobject)
{
    qan::Node* newnode=nullptr;

    if(nodeobject["type"]=="ProcessingThresholdNode"){
        newnode=graphView->getGraph()->insertNode<ProcessingThresholdNode>(nullptr);
    }
    else if(nodeobject["type"]=="ProcessingContoursNode"){
        newnode=graphView->getGraph()->insertNode<ProcessingContoursNode>(nullptr);
    }
    else if(nodeobject["type"]=="ProcessingShapesNode"){
        newnode=graphView->getGraph()->insertNode<ProcessingShapesNode>(nullptr);
    }
    else if(nodeobject["type"]=="CannyEdgesNode"){
        newnode=graphView->getGraph()->insertNode<CannyEdgesNode>(nullptr);
    }
    else{
        LOG_WARNING(QString("Unknown nodeobject type:%1").arg(nodeobject["type"].toString()));
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


    QJsonArray processingArray = json["processing"].toArray();

    for (int i = 0; i < processingArray.count(); ++i) {



        FlowNode* node=nullptr;
        ProcessingNode* procnode=nullptr;

        QJsonObject processingObject=processingArray[i].toObject();


        node=readProcessingNode(m_roiEditorGraphView,processingObject);


        procnode=qobject_cast<ProcessingNode*>(node);
        if(procnode){
            if(procnode->baseNode()){
                m_procBaseNode=procnode;
                node->bindSourceProperty(this,"sourceFrame","originalInput");

                node->bindSourceProperty(this,"processedFrame","processedFrame");

            }


            QObject::connect(procnode,&ProcessingNode::baseNodeChanged,[this,node,procnode](bool isbasenode){
                if(isbasenode){

                    m_procBaseNode=procnode;
                    node->bindSourceProperty(this,"sourceFrame","originalInput");

                    node->bindSourceProperty(this,"processedFrame","processedFrame");

                    foreach (FlowNode* proc_nodeitem, this->m_ProcessingNodes) {
                        if(proc_nodeitem!=procnode){
                            ((ProcessingNode*)proc_nodeitem)->setBaseNode(false);
                        }
                    }

                }
                else{

                    node->unbindSourceProperty("originalInput");

                    node->unbindSourceProperty("processedFrame");
                }
            }
            );




            QMetaObject::Connection* processingconnection = new QMetaObject::Connection;


            if(procnode->endNode()){



                *processingconnection=QObject::connect(procnode,&ProcessingNode::processingCompleted,this, [this]{
                    setRoiProcessingDone(true);
                });



            }

            QObject::connect(procnode,&ProcessingNode::endNodeChanged,[this,processingconnection,procnode](bool isendnode){
                if(isendnode){


                    QObject::disconnect(*processingconnection);


                    *processingconnection=QObject::connect(procnode,&ProcessingNode::processingCompleted,this, [this]{
                        setRoiProcessingDone(true);
                    });

                    foreach (FlowNode* proc_nodeitem, this->m_ProcessingNodes) {
                        if(proc_nodeitem!=procnode){
                            ((ProcessingNode*)proc_nodeitem)->setEndNode(false);
                        }
                    }
                }
                else{

                    QObject::disconnect(*processingconnection);
                }
            }
            );


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

    if(m_procBaseNode){
        m_procBaseNode->setInput(m_sourceFrame);

        m_procBaseNode->setProcess(true);
    }
}

void ROINode::setSourceFrame(QMat *sourceFrame)
{


    if (sourceFrame &&  sourceFrame->cvMat()->cols >= getItem()->x() + getItem()->width() && sourceFrame->cvMat()->rows >= getItem()->y() +getItem()->height()){

        const cv::Mat &in=*sourceFrame->cvMat();

        in(cv::Rect( getItem()->x(),  getItem()->y(),  getItem()->width(),  getItem()->height())).copyTo(*m_sourceFrame->cvMat());



        emit sourceFrameChanged(m_sourceFrame);

        emit processedFrameChanged(m_processedFrame);


    }


}

void ROINode::setRoiProcessingDone(bool roiProcessingDone)

{

    m_roiProcessingDone = roiProcessingDone;
    emit processedFrameChanged(m_processedFrame);

    emit roiProcessingDoneChanged(m_roiProcessingDone);
}
