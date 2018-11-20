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



    Q_PROPERTY(bool processingDone READ processingDone WRITE setProcessingDone NOTIFY processingDoneChanged)
    Q_PROPERTY(FlowNodePort* processingDonePort READ processingDonePort WRITE setProcessingDonePort NOTIFY processingDonePortChanged USER("serialize"))


    Q_PROPERTY(QMat* input READ input WRITE setInput NOTIFY inputChanged)
    Q_PROPERTY(FlowNodePort* inputPort READ inputPort WRITE setInputPort NOTIFY inputPortChanged USER("serialize"))

    Q_PROPERTY(QMat* output READ output NOTIFY outputChanged)
    Q_PROPERTY(FlowNodePort* outputPort READ outputPort WRITE setOutputPort NOTIFY outputPortChanged USER("serialize"))




    Q_PROPERTY(bool process READ process WRITE setProcess NOTIFY processChanged)
    Q_PROPERTY(FlowNodePort* processPort READ processPort WRITE setProcessPort NOTIFY processPortChanged USER("serialize"))


    Q_PROPERTY(ProcessingType  processingType  READ processingType CONSTANT FINAL USER("serialize"))
    Q_PROPERTY(bool inPlaceProcessing READ inPlaceProcessing WRITE setInPlaceProcessing NOTIFY inPlaceProcessingChanged)


    Q_PROPERTY(QMat* originalInput READ originalInput WRITE setOriginalInput NOTIFY originalInputChanged)


    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged USER("serialize"))

    
public:
    enum class ProcessingType {
        ProcessingBaseNode,
        ProcessingEndNode,
        ProcessingDrawingNode,
        ProcessingThresholdNode,
        ProcessingFilterNode,
        ProcessingContoursNode,
        ProcessingShapesNode,
        ProcessingLogicalNode,
        ProcessingEnclosingNode,
        ProcessingGeometricNode,
        ProcessingNumericNode,
        ProcessingMaskNode

    };
    Q_ENUM(ProcessingType)


    ProcessingNode();

    ~ProcessingNode() override;






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



    virtual void DeSerialize(QJsonObject &json) override;

    bool showOriginal() const
    {
        return m_showOriginal;
    }


    ProcessingType processingType() const
    {
        return m_processingType;
    }

    bool inPlaceProcessing() const
    {
        return m_inPlaceProcessing;
    }


    bool enabled() const
    {
        return m_enabled;
    }

    void setOriginalFrame(QMat *originalFrame);

    QMat* originalInput() const
    {
        return m_originalInput;
    }

    bool process() const
    {
        return m_process;
    }

public slots:
    virtual void setInput(QMat* input)=0;



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





    void setProcess(bool process);

    void reProcess();


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




    void setInPlaceProcessing(bool inPlaceProcessing)
    {
        if (m_inPlaceProcessing == inPlaceProcessing)
            return;

        m_inPlaceProcessing = inPlaceProcessing;
        emit inPlaceProcessingChanged(m_inPlaceProcessing);
    }

    void setEnabled(bool enabled)
    {
        if (m_enabled == enabled)
            return;

        m_enabled = enabled;
        emit enabledChanged(m_enabled);

        if(configsLoaded()){
            setProcess(true);
        }

    }

    void setOriginalInput(QMat* originalInput)
    {


        m_originalInput = originalInput;
        emit originalInputChanged(m_originalInput);
    }

signals:
    void inputChanged(QMat* input);
    void outputChanged(QMat* output);

    void inputPortChanged(FlowNodePort* inputPort);

    void outputPortChanged(FlowNodePort* outputPort);



    void processingCompleted(ProcessingNode* node);

    void processingChanged(bool processing);


    void sourceFrameChanged(QMat* sourceFrame);



    void processChanged(bool process);

    void processPortChanged(FlowNodePort* processPort);

    void processingDoneChanged(bool processingDone);

    void processingDonePortChanged(FlowNodePort* processingDonePort);


    void isBaseNodeChanged(bool isBaseNode);

    void isEndNodeChanged(bool isEndNode);



    void originalInputChanged(QMat* originalInput);

    void inPlaceProcessingChanged(bool inPlaceProcessing);

    void enabledChanged(bool enabled);




private:



    bool m_inPlaceProcessing=false;


    bool m_enabled=true;



    bool m_process;

protected:

    QMat* m_input=nullptr;
    QMat* m_originalInput=new QMat();

    QMat* m_output=new QMat();
    QMutex mMutex;
    bool m_processingDone=false;

    QMat* m_originalFrame=new QMat();

    bool m_showOriginal=false;

    virtual void doProcess()=0;

    ProcessingType m_processingType;
    FlowNodePort* m_inputPort=nullptr;
    FlowNodePort* m_outputPort=nullptr;


    FlowNodePort* m_processPort=nullptr;

    FlowNodePort* m_processingDonePort=nullptr;


};


Q_DECLARE_METATYPE(cv::Rect);
Q_DECLARE_METATYPE(std::vector<cv::Rect>);

Q_DECLARE_METATYPE(cv::RotatedRect);
Q_DECLARE_METATYPE(std::vector<cv::RotatedRect>);



#endif // FLOWNODE_H
