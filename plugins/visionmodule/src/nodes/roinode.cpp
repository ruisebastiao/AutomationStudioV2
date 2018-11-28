#include "roinode.h"
#include "QObject"
#include "qautomationmodule.h"

#include <nodes/cv/processingbasenode.h>
#include <nodes/cv/processingcontoursnode.h>
#include <nodes/cv/processingenclosingnode.h>
#include <nodes/cv/processingendnode.h>
#include <nodes/cv/processingfilternode.h>
#include <nodes/cv/processinggeometricnode.h>
#include <nodes/cv/processinglogicalnode.h>
#include <nodes/cv/processingmasknode.h>
#include <nodes/cv/processingthresholdnode.h>


using namespace cv;

ROINode::ROINode()
{
    m_type=Type::ROINode;

    m_processingNodeTypes=ProcessingNode::getProcessingTypes();
    m_commonNodeTypes=FlowNode::getCommonTypes();
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

    for (int i = 0; i < m_ProcessingNodes.length(); ++i) {

        QJsonObject processingnodeObject;

        FlowNode* processing=static_cast<FlowNode*>(m_ProcessingNodes.at(i));

        processing->Serialize(processingnodeObject);

        processingnodesArray.append(processingnodeObject);
    }

    json["processingnodes"]=processingnodesArray;


    QJsonArray commonnodesArray;

    for (int i = 0; i < m_CommonNodes.length(); ++i) {

        QJsonObject commonnodeObject;

        FlowNode* commonnode=static_cast<FlowNode*>(m_CommonNodes.at(i));

        commonnode->Serialize(commonnodeObject);

        commonnodesArray.append(commonnodeObject);
    }

    json["commonnodes"]=commonnodesArray;


}




ProcessingNode *ROINode::createProcessingNode(qan::GraphView *graphView, QString nodetype){
    qan::Node* newnode=nullptr;

    if(nodetype=="ProcessingBaseNode"){
        newnode=graphView->getGraph()->insertNode<ProcessingBaseNode>(nullptr);
    }
    else if(nodetype=="ProcessingThresholdNode"){
        newnode=graphView->getGraph()->insertNode<ProcessingThresholdNode>(nullptr);
    }
    else if(nodetype=="ProcessingFilterNode"){
        newnode=graphView->getGraph()->insertNode<ProcessingFilterNode>(nullptr);
    }
    else if(nodetype=="ProcessingEndNode"){
        newnode=graphView->getGraph()->insertNode<ProcessingEndNode>(nullptr);
    }
    else if(nodetype=="ProcessingContoursNode"){
        newnode=graphView->getGraph()->insertNode<ProcessingContoursNode>(nullptr);
    }
    else if(nodetype=="ProcessingLogicalNode"){
        newnode=graphView->getGraph()->insertNode<ProcessingLogicalNode>(nullptr);
    }
    else if(nodetype=="ProcessingEnclosingNode"){
        newnode=graphView->getGraph()->insertNode<ProcessingEnclosingNode>(nullptr);
    }
    else if(nodetype=="ProcessingGeometricNode"){
        newnode=graphView->getGraph()->insertNode<ProcessingGeometricNode>(nullptr);
    }
    else if(nodetype=="ProcessingMaskNode"){
        newnode=graphView->getGraph()->insertNode<ProcessingMaskNode>(nullptr);
    }
    else{
        LOG_WARNING(QString("Unknown nodeobject processingType:%1").arg(nodetype));
    }



    ProcessingNode* procnode=dynamic_cast<ProcessingNode*>(newnode);


    return procnode;



}

ProcessingNode *ROINode::readProcessingNode(qan::GraphView *graphView, QJsonObject nodeobject)
{


    ProcessingNode* node=dynamic_cast<ProcessingNode*>(createProcessingNode(graphView,nodeobject["processingType"].toString()));
    if(node){
        node->DeSerialize(nodeobject);
    }



    return node;

}


void ROINode::initializeProcessingNode(ProcessingNode* procnode){

    if(procnode){
        connect(procnode,&FlowNode::removeNode,[&](FlowNode* nodetoremove){
            int nodepos=m_ProcessingNodes.indexOf( nodetoremove);
            if(nodepos>0){
                FlowNode* noderemoved=m_ProcessingNodes.at(nodepos);
                if(noderemoved){
                    m_ProcessingNodes.removeAll(noderemoved);
                    this->m_roiEditorGraphView->getGraph()->removeNode(noderemoved);

                }

            }
        });




        procnode->setOriginalFrame(this->processedFrame());
        if(procnode->processingType()==ProcessingNode::ProcessingType::ProcessingBaseNode){
//            procnode->bindSourceProperty(this,"sourceFrame","input");
            m_basenode=qobject_cast<ProcessingBaseNode*>(procnode);
        }





        QObject::connect(procnode,&ProcessingNode::processingCompleted,this, [this](ProcessingNode* endnode){
            setRoiProcessingDone(true);
        });


        m_ProcessingNodes.append(procnode);

    }



}


void ROINode::DeSerialize(QJsonObject &json)
{
    FlowNode::DeSerialize(json);



    QJsonArray processingArray = json["processingnodes"].toArray();

    for (int i = 0; i < processingArray.count(); ++i) {




        QJsonObject processingObject=processingArray[i].toObject();


        ProcessingNode* procnode=readProcessingNode(m_roiEditorGraphView,processingObject);

        initializeProcessingNode(procnode);




    }

    emit processingNodeTypesChanged(m_processingNodeTypes);


    QJsonArray commonNodesArray = json["commonnodes"].toArray();

    for (int i = 0; i < commonNodesArray.count(); ++i) {


        QJsonObject commonnodeObject=commonNodesArray[i].toObject();
        FlowNode* commonnode=QAutomationModule::readCommonNode(m_roiEditorGraphView,commonnodeObject);
        m_CommonNodes.append(commonnode);


    }






}


void ROINode::addCommonNode(QPoint loc, QVariantMap nodeinfo)
{
    qDebug()<<"Adding common node:"<<nodeinfo<<" @ "<<loc;

    QString procType;
    QMapIterator<QString, QVariant> i(nodeinfo);
    while (i.hasNext()) {
        i.next();
        procType=i.key();

    }

    FlowNode *commonnode=QAutomationModule::createCommonNode(m_roiEditorGraphView,procType);

    if(commonnode){
        commonnode->getItem()->setProperty("x",QVariant::fromValue(loc.x()));
        commonnode->getItem()->setProperty("y",QVariant::fromValue(loc.y()));


        std::list<FlowNode*> allnodeslist;


        allnodeslist.merge(m_ProcessingNodes.toStdList());
        allnodeslist.merge(m_CommonNodes.toStdList());

        QList<FlowNode*> allnodes=QList<FlowNode*>::fromStdList(allnodeslist);

        int nodeid=FlowNode::getAvailableID(allnodes);


        if(nodeid==-1){
            nodeid=m_ProcessingNodes.length()+m_CommonNodes.length();
        }

        commonnode->setId(nodeid);

        m_CommonNodes.append(commonnode);


    }
}

void ROINode::addProcNode(QPoint loc,QVariantMap nodeinfo){
    qDebug()<<"Adding Processing node:"<<nodeinfo<<" @ "<<loc;

    QString procType;
    QMapIterator<QString, QVariant> i(nodeinfo);
    while (i.hasNext()) {
        i.next();
        procType=i.key();

    }

    ProcessingNode *procnode=createProcessingNode(m_roiEditorGraphView,procType);

    if(procnode){
        procnode->getItem()->setProperty("x",QVariant::fromValue(loc.x()));
        procnode->getItem()->setProperty("y",QVariant::fromValue(loc.y()));



        int nodeid=FlowNode::getAvailableID(m_ProcessingNodes);


        if(nodeid==-1){
            nodeid=m_ProcessingNodes.length();
        }

        procnode->setId(nodeid);

        initializeProcessingNode(procnode);

        QJsonObject Qo;
        procnode->initializePorts(Qo);


    }
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
