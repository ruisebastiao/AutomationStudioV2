#ifndef VISIONSYSTEMNODE_H
#define VISIONSYSTEMNODE_H

#include "frameviewernode.h"
#include "roinode.h"

#include <flownode.h>

#include <QtConcurrent>


class VisionSystemNode : public FlowNode
{
    Q_OBJECT

    Q_PROPERTY(QMat* frameSource READ frameSource WRITE setFrameSource NOTIFY frameSourceChanged REVISION 30)


    Q_PROPERTY(bool processFrame READ processFrame WRITE setProcessFrame NOTIFY processFrameChanged REVISION 31)


    Q_PROPERTY(bool frameProcessed READ frameProcessed WRITE setFrameProcessed NOTIFY frameProcessedChanged REVISION 31)


    Q_PROPERTY(bool processOnNewFrame READ processOnNewFrame WRITE setProcessOnNewFrame NOTIFY processOnNewFrameChanged USER("serialize"))


    Q_PROPERTY(qan::GraphView* visionGraphView READ visionGraphView WRITE setVisionGraphView NOTIFY visionGraphViewChanged)




public:

    VisionSystemNode();

    virtual ~VisionSystemNode() override;

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

        if(m_frameSource && m_frameSource->cvMat()->empty()==false && processOnNewFrame()){
            setProcessFrame(true);
        }

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

//        if(frameProcessed){
//            LOG_INFO("Node ID|"+QString::number(this->id())+"|Processing finished");
//        }
        emit frameProcessedChanged(m_frameProcessed);
    }




    void setVisionGraphView(qan::GraphView* visionGraphView)
    {
        if (m_visionGraphView == visionGraphView)
            return;

        m_visionGraphView = visionGraphView;
        emit visionGraphViewChanged(m_visionGraphView);
    }



    void setProcessOnNewFrame(bool processOnNewFrame)
    {
        if (m_processOnNewFrame == processOnNewFrame)
            return;

        m_processOnNewFrame = processOnNewFrame;
        emit processOnNewFrameChanged(m_processOnNewFrame);
    }

public:
    void Serialize(QJsonObject &json);
    void DeSerialize(QJsonObject &json);

    qan::GraphView* visionGraphView() const
    {
        return m_visionGraphView;
    }


    bool processOnNewFrame() const
    {
        return m_processOnNewFrame;
    }

signals:

    void frameSourceChanged(QMat* frameSource);

    void processFrameChanged(bool processFrame);

    void frameProcessedChanged(bool frameProcessed);



    void visionGraphViewChanged(qan::GraphView* visionGraphView);

    void frameSourcePortChanged(FlowNodePort* frameSourcePort);

    void processFramePortChanged(FlowNodePort* processFramePort);

    void frameProcessedPortChanged(FlowNodePort* frameProcessedPort);

    void processOnNewFrameChanged(bool processOnNewFrame);

private:

    QMat* m_frameSource=nullptr;
    bool m_processFrame=false;
    bool m_frameProcessed=false;

    void readROINode(QJsonObject roiobject);

    QList<ROINode *> m_ROINodes;

    QFuture<void> m_processingFuture;
    QFutureWatcher<void> m_processingFutureWatcher;

    qan::GraphView* m_visionGraphView=nullptr;

    bool m_processOnNewFrame=false;

    // FlowNode interface
public:
    
};

#endif // VISIONSYSTEMNODE_H
