#ifndef VISIONSYSTEMNODE_H
#define VISIONSYSTEMNODE_H

#include "framebuffernode.h"
#include "frameviewernode.h"
#include "roinode.h"

#include <flownode.h>

#include <QtConcurrent>

#include <graphs/visiongraph.h>


class VisionSystemNode : public FlowNode
{
    Q_OBJECT

    Q_PROPERTY(QVariant frameSource READ frameSource WRITE setFrameSource NOTIFY frameSourceChanged REVISION 30)

    Q_PROPERTY(QVariant frameBufferSource READ frameBufferSource WRITE setFrameBufferSource NOTIFY frameBufferSourceChanged REVISION 30)


    Q_PROPERTY(QVariant processFrame READ processFrame WRITE setProcessFrame NOTIFY processFrameChanged REVISION 30)


    Q_PROPERTY(QVariant frameProcessed READ frameProcessed WRITE setFrameProcessed NOTIFY frameProcessedChanged REVISION 31)


    Q_PROPERTY(bool processOnNewFrame READ processOnNewFrame WRITE setProcessOnNewFrame NOTIFY processOnNewFrameChanged USER("serialize"))


    Q_PROPERTY(qan::GraphView* visionGraphView READ visionGraphView WRITE setVisionGraphView NOTIFY visionGraphViewChanged)


    Q_PROPERTY(FlowNodeManager* rois READ rois WRITE setRois NOTIFY roisChanged USER("serialize"))


public:

    VisionSystemNode();

    virtual ~VisionSystemNode() override;

    static  QQmlComponent*      delegate(QQmlEngine& engine) noexcept;



    QVariant frameSource() const
    {
        return m_frameSource;
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

        m_frameSource = frameSource;
        emit frameSourceChanged(m_frameSource);

        QMat* framesource=m_frameSource.value<QMat*>();
        if(framesource && framesource->cvMat()->empty()==false && processOnNewFrame()){
            setProcessFrame(true);
        }

    }

    void setProcessFrame(QVariant processFrame)
    {

        m_processFrame = processFrame;


        emit processFrameChanged(m_processFrame);

        if(processFrame.value<bool>()){

            LOG_INFO("Node ID|"+QString::number(this->id())+"|Processing started");

            QtConcurrent::run([this](){


                QMat* framesource=m_frameSource.value<QMat*>();

                for (int var = 0; var < m_rois->length(); ++var) {
                    ROINode* roi=static_cast<ROINode*>(m_rois->at(var));
                    roi->processFrameObject(framesource);

                }
                //                foreach (FlowNode* node, m_ROINodes) {
                //                    ROINode* roi=static_cast<ROINode*>(node);
                //                    roi->processFrameObject(framesource);

                //                }

                //qDebug()<<"Frame processed";
                //setFrameProcessed(true);

            });


        }
    }

    void setFrameProcessed(QVariant frameProcessed)
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


        if(m_visionGraphView){
            VisionGraph* graph=dynamic_cast<VisionGraph*>(m_visionGraphView->getGraph());
            m_rois->setScenegraph(graph);
            graph->connect(graph,&SceneGraph::flowNodeAdded,[&](FlowNode* node){
                ROINode* roinode=dynamic_cast<ROINode*>(node);
                if(roinode){
                    QObject::connect(roinode,&ROINode::roiProcessingDoneChanged,this,[this](){
                        this->setFrameProcessed(true);
                    });
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

private:

    QVariant m_frameSource=QVariant::fromValue(new QMat());
    QVariant m_processFrame=QVariant::fromValue(false);
    QVariant m_frameProcessed=QVariant::fromValue(false);

    //    void readROINode(QJsonObject roiobject);

    //    QList<ROINode *> m_ROINodes;

    QFuture<void> m_processingFuture;
    QFutureWatcher<void> m_processingFutureWatcher;

    qan::GraphView* m_visionGraphView=nullptr;

    bool m_processOnNewFrame=false;

    // FlowNode interface
    QVariant m_frameBufferSource=QVariant::fromValue(new FrameBufferListModel());

    FlowNodeManager* m_rois= new FlowNodeManager(this);

public:

    QVariant frameBufferSource() const
    {
        return m_frameBufferSource;
    }
    FlowNodeManager* rois() const
    {
        return m_rois;
    }
};

#endif // VISIONSYSTEMNODE_H
