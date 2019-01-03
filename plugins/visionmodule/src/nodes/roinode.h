#ifndef ROINODE_H
#define ROINODE_H

#include "flownode.h"

#include <src/nodes/cv/processingnode.h>

#include "opencv2/imgproc.hpp"
#include <qquickitem.h>

#include <qanGraphView.h>

#include <nodes/cv/processingbasenode.h>
#include "flownodemanager.h"


class ROINode : public FlowNode
{
    Q_OBJECT
public:
    ROINode();

    virtual ~ROINode() override;

    static  QQmlComponent*      delegate(QQmlEngine& engine) noexcept;



    Q_PROPERTY(QMat* sourceFrame READ sourceFrame WRITE setSourceFrame NOTIFY sourceFrameChanged)
    Q_PROPERTY(QMat* processedFrame READ processedFrame NOTIFY processedFrameChanged)


    Q_PROPERTY(bool liveProcessing READ liveProcessing WRITE setLiveProcessing NOTIFY liveProcessingChanged)

    Q_PROPERTY(qan::GraphView* roiEditorGraphView READ roiEditorGraphView WRITE setRoiEditorGraphView NOTIFY roiEditorGraphViewChanged)

    Q_PROPERTY(bool roiProcessingDone READ roiProcessingDone WRITE setRoiProcessingDone NOTIFY roiProcessingDoneChanged)

    Q_PROPERTY(FlowNodeManager* processingNodes READ processingNodes WRITE setProcessingNodes NOTIFY processingNodesChanged USER("serialize"))

public:
    void processFrameObject(QMat* frame);




public slots:



    void setLiveProcessing(bool liveProcessing)
    {
        if (m_liveProcessing == liveProcessing)
            return;

        m_liveProcessing = liveProcessing;
        emit liveProcessingChanged(m_liveProcessing);
    }

    void setRoiEditorGraphView(qan::GraphView* roiEditorGraphView)
    {
        if (m_roiEditorGraphView == roiEditorGraphView)
            return;

        m_roiEditorGraphView = roiEditorGraphView;

        if(m_roiEditorGraphView){
            SceneGraph* scenegraph=dynamic_cast<SceneGraph*>(m_roiEditorGraphView->getGraph());
            m_processingNodes->setScenegraph(scenegraph);
            scenegraph->connect(scenegraph,&SceneGraph::flowNodeAdded,[&](FlowNode* node){
                if(node){
                    ProcessingNode* procnode=dynamic_cast<ProcessingNode*>(node);
                    if(procnode){
                        this->initializeProcessingNode(procnode);
                    }

                    node->setParentModule(this->parentModule());
                }
            });
        }
        emit roiEditorGraphViewChanged(m_roiEditorGraphView);
    }


    void setSourceFrame(QMat* sourceFrame);


    void setRoiProcessingDone(bool roiProcessingDone);



    void setProcessingNodes(FlowNodeManager* processingNodes)
    {
        if (m_processingNodes == processingNodes)
            return;

        m_processingNodes = processingNodes;
        emit processingNodesChanged(m_processingNodes);
    }

signals:


    void roiProcessedFrameChanged(QMat* roiProcessedFrame);


    void createProcessingComponent(QString componentSource,QJsonObject json);

    void liveProcessingChanged(bool liveProcessing);

    void roiEditorGraphViewChanged(qan::GraphView* roiEditorGraphView);


    void sourceFrameChanged(QMat* sourceFrame);

    void roiProcessingDoneChanged(bool roiProcessingDone);

    void processedFrameChanged(QMat* processedFrame);

    void processingNodeTypesChanged(QVariantList processingNodeTypes);

    void commonNodeTypesChanged(QVariantList commonNodeTypes);

    void processingNodesChanged(FlowNodeManager* processingNodes);

private:



    bool m_liveProcessing=false;

    qan::GraphView* m_roiEditorGraphView=nullptr;


    QMat* m_sourceFrame=new QMat();

    bool m_roiProcessingDone=false;

    QMat* m_processedFrame=new QMat();
    ProcessingBaseNode* m_basenode=nullptr;

    FlowNodeManager* m_processingNodes=new FlowNodeManager(this);

public:
    void Serialize(QJsonObject &json) override;
    void DeSerialize(QJsonObject &json) override;

    bool liveProcessing() const
    {
        return m_liveProcessing;
    }
    qan::GraphView* roiEditorGraphView() const
    {
        return m_roiEditorGraphView;
    }

    QMat* sourceFrame() const
    {
        return m_sourceFrame;
    }
    bool roiProcessingDone() const
    {
        return m_roiProcessingDone;
    }
    QMat* processedFrame() const
    {
        return m_processedFrame;
    }



    void initializeProcessingNode(ProcessingNode *procnode);

    FlowNodeManager* processingNodes() const
    {
        return m_processingNodes;
    }
};

#endif // ROINODE_H
