#include "framebuffernode.h"
#include <opencv2/opencv.hpp>

using namespace cv;

FrameBufferNode::FrameBufferNode()
{
    m_type=FlowNode::Type::FrameBufferNode;
    m_frameBuffers= new FrameBufferListModel();
}

void FrameBufferNode::processCurrent()
{
    QMat* currentmat= m_frameBuffers->getItemAt(m_readIndex);

    m_fullBufferReaded=true;

    if(currentmat!=nullptr){
        LOG_INFO()<<"Processing frame "<<currentmat<< "at index "<<m_readIndex;

        (currentmat->cvMat())->copyTo((*m_frameSink->cvMat()));
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

    /// in
    ///
    m_numBuffersPort= new FlowNodePort(this,qan::PortItem::Type::In,"numBuffers");
    m_inPorts.append(m_numBuffersPort);

    m_readNextFramePort= new FlowNodePort(this,qan::PortItem::Type::In,"readNextFrame");
    m_inPorts.append(m_readNextFramePort);


    m_frameSourcePort= new FlowNodePort(this,qan::PortItem::Type::In,"frameSource");
    m_inPorts.append(m_frameSourcePort);


    /// Out

    m_frameSinkPort=new FlowNodePort(this,qan::PortItem::Type::Out,"frameSink");
    m_outPorts.append(m_frameSinkPort);

    m_frameStoredPort=new FlowNodePort(this,qan::PortItem::Type::Out,"frameStored");
    m_outPorts.append(m_frameStoredPort);

    m_bufferFullPort=new FlowNodePort(this,qan::PortItem::Type::Out,"bufferFull");
    m_outPorts.append(m_bufferFullPort);







    FlowNode::DeSerialize(json);
}

void FrameBufferNode::setFrameSource(QMat *frameSource)
{


    m_frameSource = frameSource;

    if(!frameSource || frameSource->cvMat()->empty()){
        return;
    }

    LOG_INFO()<<"Storing frame "<<frameSource<< "at index "<<m_writeIndex;

    QMat* currentmat= m_frameBuffers->getItemAt(m_writeIndex);


    if(currentmat!=nullptr){
        (frameSource->cvMat())->copyTo((*currentmat->cvMat()));
//        int storeindex=writeIndex();
//        QtConcurrent::run([&](){

//             QMat* storemat= m_frameBuffers->getItemAt(storeindex);

//             QString name=QString("img_%1.jpg").arg(storeindex);

//             cv::imwrite(name.toStdString(),(*storemat->cvMat()));

//        });

        m_frameBuffers->indexDataChanged(writeIndex());
        if(autoIncrementWriteIndex()){
            setWriteIndex(writeIndex()+1);
        }
    }
    emit frameSourceChanged(m_frameSource);
    setFrameStored(true);


}

void FrameBufferNode::setReadNextFrame(bool readNextFrame)
{

    m_readNextFrame = readNextFrame;
    if(m_readNextFrame){



        QMat* currentmat= m_frameBuffers->getItemAt(m_readIndex);


        if(currentmat!=nullptr && m_fullBufferReaded==false){
            LOG_INFO()<<"Reading frame "<<currentmat<< "at index "<<m_readIndex;

            (currentmat->cvMat())->copyTo((*m_frameSink->cvMat()));
            emit frameSinkChanged(m_frameSink);

            if(autoIncrementReadIndex()){
                setReadIndex(readIndex()+1);
            }
        }

    }
    emit readNextFrameChanged(m_readNextFrame);
}
