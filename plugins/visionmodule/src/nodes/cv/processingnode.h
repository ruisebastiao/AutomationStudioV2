#ifndef PROCESSINGNODE_H
#define PROCESSINGNODE_H

#include <Logger.h>

#include <flownode.h>

#include <flownodeport.h>

#include <cv/preprocessing/preprocessing.h>

#include "cv/qmat.h"


#include "opencv2/imgproc.hpp"


class ProcessingNode : public FlowNode
{
    Q_OBJECT

    Q_PROPERTY(bool isBaseNode READ isBaseNode WRITE setIsBaseNode NOTIFY isBaseNodeChanged USER("serialize"))
    Q_PROPERTY(bool isEndNode READ isEndNode WRITE setIsEndNode NOTIFY isEndNodeChanged USER("serialize"))


    Q_PROPERTY(bool processingDone READ processingDone WRITE setProcessingDone NOTIFY processingDoneChanged)
    Q_PROPERTY(FlowNodePort* processingDonePort READ processingDonePort WRITE setProcessingDonePort NOTIFY processingDonePortChanged USER("serialize"))


    Q_PROPERTY(QMat* input READ input WRITE setInput NOTIFY inputChanged)
    Q_PROPERTY(FlowNodePort* inputPort READ inputPort WRITE setInputPort NOTIFY inputPortChanged USER("serialize"))

    Q_PROPERTY(QMat* output READ output WRITE setOutput NOTIFY outputChanged)
    Q_PROPERTY(FlowNodePort* outputPort READ outputPort WRITE setOutputPort NOTIFY outputPortChanged USER("serialize"))

    Q_PROPERTY(QMat* processedFrame READ processedFrame WRITE setProcessedFrame NOTIFY processedFrameChanged)


    Q_PROPERTY(bool process READ process WRITE setProcess NOTIFY processChanged)
    Q_PROPERTY(FlowNodePort* processPort READ processPort WRITE setProcessPort NOTIFY processPortChanged USER("serialize"))


    Q_PROPERTY(PreProcessingListModel* preProcessors READ preProcessors WRITE setPreProcessors NOTIFY preProcessorsChanged USER("serialize"))


//    Q_PROPERTY(Pre name READ name WRITE setName NOTIFY nameChanged)




public:

    ProcessingNode();

    ~ProcessingNode() override;


    static  QQmlComponent*      delegate(QQmlEngine& engine) noexcept;





    QMat* input() const
    {
        return m_input;
    }
    QMat* output() const
    {
        return m_output;
    }

    FlowNodePort* inputPort() const
    {
        return m_inputPort;
    }

    FlowNodePort* outputPort() const
    {
        return m_outputPort;
    }




    QMat* processedFrame() const
    {
        return m_processedFrame;
    }

    //    FlowNodePort* processedFramePort() const
    //    {
    //        return m_processedFramePort;
    //    }

    bool process() const
    {
        return m_process;
    }

    FlowNodePort* processPort() const
    {
        return m_processPort;
    }

    FlowNodePort* processingDonePort() const
    {
        return m_processingDonePort;
    }

    bool processingDone() const
    {
        return m_processingDone;
    }

    QMat* originalInput() const
    {
        return m_originalInput;
    }

    virtual void DeSerialize(QJsonObject &json) override;

    bool showOriginal() const
    {
        return m_showOriginal;
    }

    bool isBaseNode() const
    {
        return m_isBaseNode;
    }

    bool isEndNode() const
    {
        return m_isEndNode;
    }

    PreProcessingListModel* preProcessors() const
    {
        return m_preProcessors;
    }

public slots:
    void setInput(QMat* input);


    void setOutput(QMat* output)
    {
        if(!m_output && output){
            m_output=new QMat();
        }


        //  emit outputChanged(m_output);
    }

    void setInputPort(FlowNodePort* inputPort)
    {
        if (m_inputPort == inputPort)
            return;

        m_inputPort = inputPort;
        emit inputPortChanged(m_inputPort);
    }

    void setOutputPort(FlowNodePort* outputPort)
    {
        if (m_outputPort == outputPort)
            return;

        m_outputPort = outputPort;
        emit outputPortChanged(m_outputPort);
    }



    void setProcessedFrame(QMat* processedFrame)
    {

        m_processedFrame = processedFrame;
        emit processedFrameChanged(m_processedFrame);
    }


    void setProcess(bool process);



    void setProcessPort(FlowNodePort* processPort)
    {
        if (m_processPort == processPort)
            return;

        m_processPort = processPort;
        emit processPortChanged(m_processPort);
    }

    void setProcessingDone(bool processingDone)
    {

        m_processingDone = processingDone;
        emit processingDoneChanged(m_processingDone);
    }

    void setProcessingDonePort(FlowNodePort* processingDonePort)
    {
        if (m_processingDonePort == processingDonePort)
            return;

        m_processingDonePort = processingDonePort;
        emit processingDonePortChanged(m_processingDonePort);
    }


    void setIsBaseNode(bool isBaseNode)
    {
        if (m_isBaseNode == isBaseNode)
            return;

        m_isBaseNode = isBaseNode;
        emit isBaseNodeChanged(m_isBaseNode);
    }

    void setIsEndNode(bool isEndNode)
    {
        if (m_isEndNode == isEndNode)
            return;

        m_isEndNode = isEndNode;
        emit isEndNodeChanged(m_isEndNode);
    }

    void setPreProcessors(PreProcessingListModel* preProcessors)
    {
        if (m_preProcessors == preProcessors)
            return;

        m_preProcessors = preProcessors;
        emit preProcessorsChanged(m_preProcessors);
    }

signals:
    void inputChanged(QMat* input);
    void outputChanged(QMat* output);

    void inputPortChanged(FlowNodePort* inputPort);

    void outputPortChanged(FlowNodePort* outputPort);



    void processingCompleted(ProcessingNode* node);

    void processingChanged(bool processing);


    void sourceFrameChanged(QMat* sourceFrame);

    void processedFrameChanged(QMat* processedFrame);


    void processChanged(bool process);

    void processPortChanged(FlowNodePort* processPort);

    void processingDoneChanged(bool processingDone);

    void processingDonePortChanged(FlowNodePort* processingDonePort);


    void isBaseNodeChanged(bool isBaseNode);

    void isEndNodeChanged(bool isEndNode);

    void preProcessorsChanged(PreProcessingListModel* preProcessors);

private:



    FlowNodePort* m_inputPort=nullptr;
    FlowNodePort* m_outputPort=nullptr;



    //    FlowNodePort* m_processedFramePort=nullptr;

    bool m_process=false;

    FlowNodePort* m_processPort=nullptr;

    FlowNodePort* m_processingDonePort=nullptr;




    bool m_isBaseNode=false;

    bool m_isEndNode=false;

    PreProcessingListModel* m_preProcessors=nullptr;

protected:
    QMat* m_input=nullptr;
    QMat* m_originalInput=nullptr;

    QMat* m_output=new QMat();
    QMutex mMutex;
    bool m_processingDone=false;

    QMat* m_processedFrame=nullptr;
    bool m_showOriginal=false;

    void doProcess();


};





#endif // FLOWNODE_H
