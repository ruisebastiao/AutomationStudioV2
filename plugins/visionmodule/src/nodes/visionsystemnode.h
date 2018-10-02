#ifndef VISIONSYSTEMNODE_H
#define VISIONSYSTEMNODE_H

#include "frameviewernode.h"
#include "roinode.h"

#include <flownode.h>

#include <QtConcurrent>


class VisionSystemNode : public FlowNode
{
    Q_OBJECT

    Q_PROPERTY(QMat* frameSource READ frameSource WRITE setFrameSource NOTIFY frameSourceChanged )
    Q_PROPERTY(FlowNodePort* frameSourcePort READ frameSourcePort WRITE setFrameSourcePort NOTIFY frameSourcePortChanged USER("serialize"))

    Q_PROPERTY(bool processFrame READ processFrame WRITE setProcessFrame NOTIFY processFrameChanged )
    Q_PROPERTY(FlowNodePort* processFramePort READ processFramePort WRITE setProcessFramePort NOTIFY processFramePortChanged USER("serialize"))

    Q_PROPERTY(bool frameProcessed READ frameProcessed WRITE setFrameProcessed NOTIFY frameProcessedChanged )
    Q_PROPERTY(FlowNodePort* frameProcessedPort READ frameProcessedPort WRITE setFrameProcessedPort NOTIFY frameProcessedPortChanged USER("serialize"))


    Q_PROPERTY(qan::GraphView* visionGraphView READ visionGraphView WRITE setVisionGraphView NOTIFY visionGraphViewChanged)




public:

    VisionSystemNode();

    ~VisionSystemNode();

    static  QQmlComponent*      delegate(QQmlEngine& engine) noexcept;



    QMat* frameSource() const
    {
        return m_frameSource;
    }

    bool processFrame() const
    {
        return m_processFrame;
    }

    bool frameProcessed() const
    {
        return m_frameProcessed;
    }

public slots:


    void setFrameSource(QMat* frameSource)
    {


        m_frameSource = frameSource;
        emit frameSourceChanged(m_frameSource);

    }

    void setProcessFrame(bool processFrame)
    {

        m_processFrame = processFrame;


        emit processFrameChanged(m_processFrame);

        if(processFrame){

            LOG_INFO("Node ID|"+QString::number(this->id())+"|Processing started");


            QtConcurrent::run([this](){

                foreach (FlowNode* node, m_ROINodes) {
                    ROINode* roi=static_cast<ROINode*>(node);
                    roi->processFrameObject(m_frameSource);

                }

                //qDebug()<<"Frame processed";
                //setFrameProcessed(true);

            });


        }
    }

    void setFrameProcessed(bool frameProcessed)
    {


        m_frameProcessed = frameProcessed;

        if(frameProcessed){
            LOG_INFO("Node ID|"+QString::number(this->id())+"|Processing finished");
        }
        emit frameProcessedChanged(m_frameProcessed);
    }




    void setVisionGraphView(qan::GraphView* visionGraphView)
    {
        if (m_visionGraphView == visionGraphView)
            return;

        m_visionGraphView = visionGraphView;
        emit visionGraphViewChanged(m_visionGraphView);
    }


    void setFrameSourcePort(FlowNodePort* frameSourcePort)
    {
        if (m_frameSourcePort == frameSourcePort)
            return;

        m_frameSourcePort = frameSourcePort;
        emit frameSourcePortChanged(m_frameSourcePort);
    }

    void setProcessFramePort(FlowNodePort* processFramePort)
    {
        if (m_processFramePort == processFramePort)
            return;

        m_processFramePort = processFramePort;
        emit processFramePortChanged(m_processFramePort);
    }

    void setFrameProcessedPort(FlowNodePort* frameProcessedPort)
    {
        if (m_frameProcessedPort == frameProcessedPort)
            return;

        m_frameProcessedPort = frameProcessedPort;
        emit frameProcessedPortChanged(m_frameProcessedPort);
    }

public:
    void Serialize(QJsonObject &json);
    void DeSerialize(QJsonObject &json);

    qan::GraphView* visionGraphView() const
    {
        return m_visionGraphView;
    }

    FlowNodePort* frameSourcePort() const
    {
        return m_frameSourcePort;
    }

    FlowNodePort* processFramePort() const
    {
        return m_processFramePort;
    }

    FlowNodePort* frameProcessedPort() const
    {
        return m_frameProcessedPort;
    }

signals:

    void frameSourceChanged(QMat* frameSource);

    void processFrameChanged(bool processFrame);

    void frameProcessedChanged(bool frameProcessed);



    void visionGraphViewChanged(qan::GraphView* visionGraphView);

    void frameSourcePortChanged(FlowNodePort* frameSourcePort);

    void processFramePortChanged(FlowNodePort* processFramePort);

    void frameProcessedPortChanged(FlowNodePort* frameProcessedPort);

private:

    QMat* m_frameSource=nullptr;
    bool m_processFrame=false;
    bool m_frameProcessed=false;

    void readNode(QJsonObject roiobject);

    QList<ROINode *> m_ROINodes;

    QFuture<void> m_processingFuture;
    QFutureWatcher<void> m_processingFutureWatcher;

    qan::GraphView* m_visionGraphView=nullptr;

    FlowNodePort* m_frameSourcePort=nullptr;
    FlowNodePort* m_processFramePort=nullptr;
    FlowNodePort* m_frameProcessedPort=nullptr;
};

#endif // VISIONSYSTEMNODE_H
