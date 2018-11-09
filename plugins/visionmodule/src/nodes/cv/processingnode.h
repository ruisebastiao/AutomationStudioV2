#ifndef PROCESSINGNODE_H
#define PROCESSINGNODE_H

#include <Logger.h>

#include <flownode.h>

#include <flownodeport.h>

#include "cv/qmat.h"


#include "opencv2/imgproc.hpp"


class ProcessingNode : public FlowNode
{
    Q_OBJECT

    Q_PROPERTY(bool drawInSource READ drawInSource WRITE setDrawInSource NOTIFY drawInSourceChanged USER("serialize"))

    Q_PROPERTY(bool processingDone READ processingDone WRITE setProcessingDone NOTIFY processingDoneChanged)
    Q_PROPERTY(FlowNodePort* processingDonePort READ processingDonePort WRITE setProcessingDonePort NOTIFY processingDonePortChanged USER("serialize"))

    Q_PROPERTY(QMat* originalInput READ originalInput WRITE setOriginalInput NOTIFY originalInputChanged)


    Q_PROPERTY(QMat* input READ input WRITE setInput NOTIFY inputChanged)
    Q_PROPERTY(FlowNodePort* inputPort READ inputPort WRITE setInputPort NOTIFY inputPortChanged USER("serialize"))

    Q_PROPERTY(QMat* output READ output WRITE setOutput NOTIFY outputChanged)
    Q_PROPERTY(FlowNodePort* outputPort READ outputPort WRITE setOutputPort NOTIFY outputPortChanged USER("serialize"))

    Q_PROPERTY(QMat* processedFrame READ processedFrame WRITE setProcessedFrame NOTIFY processedFrameChanged)


    Q_PROPERTY(bool process READ process WRITE setProcess NOTIFY processChanged)
    Q_PROPERTY(FlowNodePort* processPort READ processPort WRITE setProcessPort NOTIFY processPortChanged USER("serialize"))

    Q_PROPERTY(bool showOriginal READ showOriginal WRITE setShowOriginal NOTIFY showOriginalChanged)




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



    bool drawInSource() const
    {
        return m_drawInSource;
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

public slots:
    virtual void setInput(QMat* input)=0;

    void reProcess();

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





    void setDrawInSource(bool drawInSource)
    {
        if (m_drawInSource == drawInSource)
            return;

        m_drawInSource = drawInSource;
        emit drawInSourceChanged(m_drawInSource);
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

    void setOriginalInput(QMat* originalInput)
    {
        if (m_originalInput == originalInput)
            return;

        m_originalInput = originalInput;
        emit originalInputChanged(m_originalInput);
    }

    void setShowOriginal(bool showOriginal)
    {
        if (m_showOriginal == showOriginal)
            return;

        m_showOriginal = showOriginal;
        emit showOriginalChanged(m_showOriginal);
    }

signals:
    void inputChanged(QMat* input);
    void outputChanged(QMat* output);

    void inputPortChanged(FlowNodePort* inputPort);

    void outputPortChanged(FlowNodePort* outputPort);

    void baseNodeChanged(bool baseNode);

    void originalInputChanged(QMat* originalInput);

    void originalInputPortChanged(FlowNodePort* originalInputPort);

    void endNodeChanged(bool endNode);

    void processingCompleted();

    void processingChanged(bool processing);

    void originalsourceFrameChanged(QMat* originalsourceFrame);

    void drawInSourceChanged(bool drawInSource);

    void sourceFrameChanged(QMat* sourceFrame);

    void processedFrameChanged(QMat* processedFrame);


    void processChanged(bool process);

    void processPortChanged(FlowNodePort* processPort);

    void processingDoneChanged(bool processingDone);

    void processingDonePortChanged(FlowNodePort* processingDonePort);

    void showOriginalChanged(bool showOriginal);

private:



    FlowNodePort* m_inputPort=nullptr;
    FlowNodePort* m_outputPort=nullptr;


    bool m_drawInSource=false;


    //    FlowNodePort* m_processedFramePort=nullptr;

    bool m_process=false;

    FlowNodePort* m_processPort=nullptr;

    FlowNodePort* m_processingDonePort=nullptr;




protected:
    QMat* m_input=nullptr;
    QMat* m_originalInput=nullptr;

    QMat* m_output=new QMat();
    QMutex mMutex;
    bool m_processingDone=false;

    QMat* m_processedFrame=nullptr;
    bool m_showOriginal=false;

    virtual void doProcess()=0;


};





#endif // FLOWNODE_H
