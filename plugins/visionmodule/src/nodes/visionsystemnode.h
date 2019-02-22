#ifndef VISIONSYSTEMNODE_H
#define VISIONSYSTEMNODE_H

#include "framebuffernode.h"
#include "frameviewernode.h"
#include "roinode.h"

#include <flownode.h>

#include <QtConcurrent>

#include <graphs/visiongraph.h>

#include <nodes/cv/processingendnode.h>


class RoisProcessor : public QObject
{
    Q_OBJECT
public:
    RoisProcessor() {


    }

    void quit(){
        m_quit=true;
        wait_for_processing.wakeAll();
    }

    void doProcess(){
        wait_for_processing.wakeAll();
    }

    virtual ~RoisProcessor() {}
    bool processing() const;

    QMat *frameMat() const;
    void setFrameMat(QMat *frameMat);

    FlowNodeManager *rois() const;
    void setRois(FlowNodeManager *rois);

public slots:

    void processNodes()
    {

        while(m_quit==false){
            mutex.lock();
            wait_for_processing.wait(&mutex);
            if(m_quit){
                break;
            }

            m_processing=true;

            QMat* framesource=m_frameMat->clone();

            for (int var = 0; var < m_rois->length(); ++var) {
                ROINode* roi=static_cast<ROINode*>(m_rois->at(var));
                roi->processFrameObject(framesource);
            }

            m_processing=false;
            mutex.unlock();

        }

        mutex.unlock();

        emit finished();
    }

private:
    FlowNodeManager* m_rois=nullptr;
    QMat* m_frameMat=new QMat();
    bool m_processing=false;
    QMutex mutex;
    bool m_quit=false;
    QWaitCondition wait_for_processing;
signals:
    void roisProcessed(QString results);
    void finished();
};


class VisionSystemNode : public FlowNode
{
    Q_OBJECT

    Q_PROPERTY(QVariant frameSource READ frameSource WRITE setFrameSource NOTIFY frameSourceChanged REVISION 30)

    Q_PROPERTY(QVariant frameBufferSource READ frameBufferSource WRITE setFrameBufferSource NOTIFY frameBufferSourceChanged REVISION 30)


    Q_PROPERTY(QVariant processFrame READ processFrame WRITE setProcessFrame NOTIFY processFrameChanged REVISION 30)


    Q_PROPERTY(QVariant frameProcessed READ frameProcessed WRITE setFrameProcessed NOTIFY frameProcessedChanged REVISION 31)

    Q_PROPERTY(QVariant results READ results WRITE setResults NOTIFY resultsChanged REVISION 31)


    Q_PROPERTY(bool processOnNewFrame READ processOnNewFrame WRITE setProcessOnNewFrame NOTIFY processOnNewFrameChanged USER("serialize"))


    Q_PROPERTY(qan::GraphView* visionGraphView READ visionGraphView WRITE setVisionGraphView NOTIFY visionGraphViewChanged)


    Q_PROPERTY(FlowNodeManager* rois READ rois WRITE setRois NOTIFY roisChanged USER("serialize"))

    Q_PROPERTY(bool highPerformanceMode READ highPerformanceMode WRITE setHighPerformanceMode NOTIFY highPerformanceModeChanged)



public:

    VisionSystemNode();

    virtual ~VisionSystemNode() override;

    static  QQmlComponent*      delegate(QQmlEngine& engine) noexcept;



    QVariant frameSource() const
    {
        return QVariant::fromValue(m_frameMat);
    }

    QVariant processFrame() const
    {
        return m_processFrame;
    }

    QVariant frameProcessed() const
    {
        return m_frameProcessed;
    }

public slots:


    void setFrameSource(QVariant frameSource)
    {





        QMat* frameMat=frameSource.value<QMat*>();

        if(frameMat->cvMat()->empty()==false){
            frameMat->cvMat()->copyTo(*m_frameMat->cvMat());
        }

        emit frameSourceChanged(frameSource);



        if(m_frameMat && m_frameMat->cvMat()->empty()==false && processOnNewFrame()){
            setProcessFrame(true);
        }

    }

    void setProcessFrame(QVariant processFrame)
    {

        m_processFrame = processFrame;


        emit processFrameChanged(m_processFrame);

        if(processFrame.value<bool>()){


            if(m_processor->processing()){
                LOG_INFO("Node ID|"+QString::number(this->id())+"|Waiting for processing finished");
                Utilities::NonBlockingExec([&](){
                    while (m_processor->processing()) {
                        QThread::msleep(10);
                    }
                });
            }


            LOG_INFO("Node ID|"+QString::number(this->id())+"|Processing started");


            setResults("");
            m_finishedROIS=0;
            m_processor->doProcess();


        }
    }

    void roisProcessed(QString results){
        LOG_INFO("Node ID|"+QString::number(this->id())+"|Frame Processing finished");
        setResults(results);

        setFrameProcessed(true);

    }

    void setFrameProcessed(QVariant frameProcessed)
    {


        m_frameProcessed = frameProcessed;


        emit frameProcessedChanged(m_frameProcessed);
    }




    void setVisionGraphView(qan::GraphView* visionGraphView)
    {
        if (m_visionGraphView == visionGraphView)
            return;

        m_visionGraphView = visionGraphView;


        emit visionGraphViewChanged(m_visionGraphView);


        if(m_visionGraphView){
            VisionGraph* graph=dynamic_cast<VisionGraph*>(m_visionGraphView->getGraph());
            m_rois->setScenegraph(graph);
            graph->connect(graph,&SceneGraph::flowNodeAdded,[&](FlowNode* node){
                ROINode* roinode=dynamic_cast<ROINode*>(node);
                if(roinode){

                }
                node->setParentModule(this->parentModule());
            });

        }
    }



    void setProcessOnNewFrame(bool processOnNewFrame)
    {
        if (m_processOnNewFrame == processOnNewFrame)
            return;

        m_processOnNewFrame = processOnNewFrame;
        emit processOnNewFrameChanged(m_processOnNewFrame);
    }

    void setFrameBufferSource(QVariant frameBufferSource);


    void setRois(FlowNodeManager* rois)
    {
        if (m_rois == rois)
            return;

        m_rois = rois;

        emit roisChanged(m_rois);
    }

    void setResults(QVariant results)
    {
        if (m_results == results)
            return;

        m_results = results;
        emit resultsChanged(m_results);
    }

    void setHighPerformanceMode(bool highPerformanceMode)
    {
        if (m_highPerformanceMode == highPerformanceMode)
            return;

        m_highPerformanceMode = highPerformanceMode;
        emit highPerformanceModeChanged(m_highPerformanceMode);
    }

public:
    void Serialize(QJsonObject &json) override;
    void DeSerialize(QJsonObject &json) override;

    qan::GraphView* visionGraphView() const
    {
        return m_visionGraphView;
    }


    bool processOnNewFrame() const
    {
        return m_processOnNewFrame;
    }

signals:

    void frameSourceChanged(QVariant frameSource);

    void processFrameChanged(QVariant processFrame);

    void frameProcessedChanged(QVariant frameProcessed);



    void visionGraphViewChanged(qan::GraphView* visionGraphView);

    void frameSourcePortChanged(FlowNodePort* frameSourcePort);

    void processFramePortChanged(FlowNodePort* processFramePort);

    void frameProcessedPortChanged(FlowNodePort* frameProcessedPort);

    void processOnNewFrameChanged(bool processOnNewFrame);

    void frameBufferSourceChanged(QVariant frameBufferSource);

    void roisChanged(FlowNodeManager* rois);

    void resultsChanged(QVariant results);

    void highPerformanceModeChanged(bool highPerformanceMode);

private:

    QMat* m_frameMat=new QMat();
    QVariant m_processFrame=QVariant::fromValue(false);
    QVariant m_frameProcessed=QVariant::fromValue(false);

    RoisProcessor* m_processor;
    QThread* m_processorThread;

    qan::GraphView* m_visionGraphView=nullptr;

    bool m_processOnNewFrame=false;

    // FlowNode interface
    QVariant m_frameBufferSource=QVariant::fromValue(new FrameBufferListModel());

    FlowNodeManager* m_rois= new FlowNodeManager(this);

    int m_finishedROIS=0;

    QVariant m_results=QVariant::fromValue(QString(""));

    bool m_highPerformanceMode=true;

public:

    QVariant frameBufferSource() const
    {
        return m_frameBufferSource;
    }
    FlowNodeManager* rois() const
    {
        return m_rois;
    }
    QVariant results() const
    {
        return m_results;
    }
    bool highPerformanceMode() const
    {
        return m_highPerformanceMode;
    }
};

#endif // VISIONSYSTEMNODE_H
