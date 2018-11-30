#include "framebuffernode.h"
#include <opencv2/opencv.hpp>

using namespace cv;

FrameBufferNode::FrameBufferNode()
{
    m_type=FlowNode::Type::FrameBufferNode;
    //    m_frameBuffers= new FrameBufferListModel();





}

void FrameBufferNode::processCurrent()
{
    FrameBufferListModel* framebuffers=m_frameBuffers.value<FrameBufferListModel*>();

    QMat* currentmat= framebuffers->getItemAt(m_readIndex);

    QMat* framesink=m_frameSink.value<QMat*>();

    m_fullBufferReaded=true;

    if(currentmat!=nullptr){
        LOG_INFO()<<"Processing frame "<<currentmat<< "at index "<<m_readIndex;

        (currentmat->cvMat())->copyTo((*framesink->cvMat()));
        emit frameSinkChanged(m_frameSink);
    }
}


QQmlComponent *FrameBufferNode::delegate(QQmlEngine &engine)noexcept
{


    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/FrameBufferNodeItem.qml"));
    return delegate.get();

}

void FrameBufferNode::Serialize(QJsonObject &json)
{

    FlowNode::Serialize(json);
}

void FrameBufferNode::DeSerialize(QJsonObject &json)
{




    FlowNode::DeSerialize(json);
}

void FrameBufferNode::setFrameSource(QVariant frameSource)
{


    m_frameSource = frameSource;

//    QMat* mat=m_frameSink.value<QMat*>();

    QMat* framesource=m_frameSource.value<QMat*>();
    if(!framesource || framesource->cvMat()->empty()){
        return;
    }

    LOG_INFO()<<"Storing frame "<<frameSource<< "at index "<<m_writeIndex;
    FrameBufferListModel* framebuffers=m_frameBuffers.value<FrameBufferListModel*>();


    QMat* currentmat= framebuffers->getItemAt(m_writeIndex);


    if(currentmat!=nullptr){
        (framesource->cvMat())->copyTo((*currentmat->cvMat()));
        //        int storeindex=writeIndex();
        //        QtConcurrent::run([&](){

        //             QMat* storemat= m_frameBuffers->getItemAt(storeindex);

        //             QString name=QString("img_%1.jpg").arg(storeindex);

        //             cv::imwrite(name.toStdString(),(*storemat->cvMat()));

        //        });

        framebuffers->indexDataChanged(writeIndex());
        if(autoIncrementWriteIndex()){
            setWriteIndex(writeIndex()+1);
        }
    }
    emit frameSourceChanged(m_frameSource);
    setFrameStored(true);


}

void FrameBufferNode::setReadNextFrame(QVariant readNextFrame)
{

    m_readNextFrame = readNextFrame;
    if(m_readNextFrame.value<bool>()){

        FrameBufferListModel* framebuffers=m_frameBuffers.value<FrameBufferListModel*>();
        QMat* currentmat= framebuffers->getItemAt(m_readIndex);
        QMat* framesink= m_frameSink.value<QMat*>();


        if(currentmat!=nullptr && m_fullBufferReaded==false){
            LOG_INFO()<<"Reading frame "<<currentmat<< "at index "<<m_readIndex;

            (currentmat->cvMat())->copyTo((*framesink->cvMat()));
            emit frameSinkChanged(m_frameSink);

            if(autoIncrementReadIndex()){
                setReadIndex(readIndex()+1);
            }
        }

    }
    emit readNextFrameChanged(m_readNextFrame);
}
