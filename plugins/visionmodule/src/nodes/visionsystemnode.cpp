#include "roinode.h"
#include "visionsystemnode.h"

VisionSystemNode::VisionSystemNode()
{


    m_type=Type::VisionSystemNode;


    m_processor = new RoisProcessor();

    m_processor->setFrameMat(m_frameMat);
    m_processor->setRois(m_rois);

    m_processorThread= new QThread;

    m_processor->moveToThread(m_processorThread);
    //connect(m_processor, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
    connect(m_processorThread, SIGNAL(started()), m_processor, SLOT(processNodes()));
    connect(m_processor, SIGNAL(roisProcessed(QString)), this, SLOT(roisProcessed(QString)));
    connect(m_processor, SIGNAL(finished()), m_processorThread, SLOT(quit()));
    connect(m_processor, SIGNAL(finished()), m_processor, SLOT(deleteLater()));
    connect(m_processorThread, SIGNAL(finished()), m_processorThread, SLOT(deleteLater()));

    m_processorThread->start();

}

VisionSystemNode::~VisionSystemNode()
{

    m_processor->quit();
    m_processorThread->terminate();
    m_processorThread->wait();


    LOG_INFO()<<"Vision system node deleted";

}

QQmlComponent *VisionSystemNode::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/VisionSystemNodeItem.qml"));
    return delegate.get();
}

void VisionSystemNode::setFrameBufferSource(QVariant frameBufferSource)
{

    m_frameBufferSource = frameBufferSource;
    emit frameBufferSourceChanged(m_frameBufferSource);

}




void VisionSystemNode::Serialize(QJsonObject &json)
{
    FlowNode::Serialize(json);


}

void VisionSystemNode::DeSerialize(QJsonObject &json)
{


    FlowNode::DeSerialize(json);

}


bool RoisProcessor::processing() const
{
    return m_processing;
}

QMat *RoisProcessor::frameMat() const
{
    return m_frameMat;
}

void RoisProcessor::setFrameMat(QMat *frameMat)
{
    m_frameMat = frameMat;
}

FlowNodeManager *RoisProcessor::rois() const
{
    return m_rois;
}

void RoisProcessor::setRois(FlowNodeManager *rois)
{
    m_rois = rois;

    connect(rois,&FlowNodeManager::flowNodeAdded,[&](FlowNode* flownode){
        ROINode* roinode=dynamic_cast<ROINode*>(flownode);
        if(roinode) {

            connect(roinode,&ROINode::roiProcessingDoneChanged,[&](bool){


                bool alldone=true;
                QString frameResults;
                for (int var = 0; var < m_rois->length(); ++var) {
                    ROINode* roi=dynamic_cast<ROINode*>(m_rois->at(var));

                    if(roi->roiProcessingDone()==false){
                        alldone=false;
                        break;
                    }

                    QString roiresult=roi->roiResults().value<QString>();


                    frameResults+=roiresult;

                    if(var<m_rois->length()-1){
                        frameResults+="|";
                    }



                }

                if(alldone){
                    emit roisProcessed(frameResults);


                }





            });
        }
    });






}
