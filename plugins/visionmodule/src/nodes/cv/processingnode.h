#ifndef PROCESSINGNODE_H
#define PROCESSINGNODE_H

#include <Logger.h>

#include <flownode.h>

#include <flownodeport.h>

#include <boost/foreach.hpp>


#include "cv/qmat.h"


#include <opencv2/opencv.hpp>



class ProcessingNode : public FlowNode
{
    Q_OBJECT



    Q_PROPERTY(QMat* maskInput READ maskInput WRITE setMaskInput NOTIFY maskInputChanged REVISION 30)
    Q_PROPERTY(QMat* drawSource READ drawSource WRITE setDrawSource NOTIFY drawSourceChanged REVISION 30)

    Q_PROPERTY(QMat* input READ input WRITE setInput NOTIFY inputChanged REVISION 30)
    Q_PROPERTY(bool process READ process WRITE setProcess NOTIFY processChanged REVISION 30)

    Q_PROPERTY(bool processingDone READ processingDone WRITE setProcessingDone NOTIFY processingDoneChanged REVISION 31)
    Q_PROPERTY(QMat* output READ output NOTIFY outputChanged REVISION 31)


    Q_PROPERTY(QMat* originalInput READ originalInput WRITE setOriginalInput NOTIFY originalInputChanged)
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged USER("serialize"))
    Q_PROPERTY(ProcessingType  processingType  READ processingType CONSTANT FINAL USER("serialize"))
    Q_PROPERTY(bool inPlaceProcessing READ inPlaceProcessing WRITE setInPlaceProcessing NOTIFY inPlaceProcessingChanged)

    Q_PROPERTY(bool applyMask READ applyMask WRITE setApplyMask NOTIFY applyMaskChanged USER("serialize"))
    Q_PROPERTY(bool drawOnSource READ drawOnSource WRITE setDrawOnSource NOTIFY drawOnSourceChanged USER("serialize"))



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



    static QVariantList getProcessingTypes(){
        QVariantList ret;

        int enumscount=QMetaEnum::fromType<ProcessingType>().keyCount();
        for (int i = 0; i < enumscount; ++i) {
            ProcessingType procctype= static_cast<ProcessingType>(QMetaEnum::fromType<ProcessingType>().value(i));

            QVariantMap map;


            switch (procctype) {

            case ProcessingType::ProcessingContoursNode:
                map.insert(QVariant::fromValue(procctype).value<QString>(),"Contours");

                break;

            case ProcessingType::ProcessingDrawingNode:
                map.insert(QVariant::fromValue(procctype).value<QString>(),"Drawing");

                break;

            case ProcessingType::ProcessingEnclosingNode:
                map.insert(QVariant::fromValue(procctype).value<QString>(),"Enclosing shapes");

                break;

            case ProcessingType::ProcessingFilterNode:
                map.insert(QVariant::fromValue(procctype).value<QString>(),"Filtering");

                break;

            case ProcessingType::ProcessingGeometricNode:
                map.insert(QVariant::fromValue(procctype).value<QString>(),"Geometric Operations");

                break;

            case ProcessingType::ProcessingLogicalNode:
                map.insert(QVariant::fromValue(procctype).value<QString>(),"Logic Operations");

                break;


            case ProcessingType::ProcessingMaskNode:
                map.insert(QVariant::fromValue(procctype).value<QString>(),"Mask");

                break;
            case ProcessingType::ProcessingShapesNode:
                map.insert(QVariant::fromValue(procctype).value<QString>(),"Shape Finder");

                break;
            case ProcessingType::ProcessingThresholdNode:
                map.insert(QVariant::fromValue(procctype).value<QString>(),"Binarization");

                break;


            default:
//                static_assert(true, "");
                break;
            }

            if(map.empty()==false)
                ret.append(map);

        }


        return ret;




    }



    QMat* input() const
    {
        return m_input;
    }
    QMat* output() const
    {
        return m_output;
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

    void setProcess(bool process);

    void reProcess();


    void setProcessingDone(bool processingDone)
    {

        m_processingDone = processingDone;
        emit processingDoneChanged(m_processingDone);
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

    void setMaskInput(QMat* maskInput)
    {

        m_maskInput = maskInput;
        emit maskInputChanged(m_maskInput);
    }

    void setDrawSource(QMat* drawSource)
    {
        if (m_drawSource == drawSource)
            return;

        m_drawSource = drawSource;
        emit drawSourceChanged(m_drawSource);
    }

    void setApplyMask(bool applyMask)
    {
        FlowNodePort* port=getPortFromKey("maskInput");

        if(port){
            if(!applyMask){

                auto edgeitem=  port->getPortItem()->getInEdgeItems().at(0);
                if(edgeitem){
                    this->getGraph()->removeEdge(edgeitem->getEdge());
                }
                port->setHidden(true);
            }
            else{
                port->setHidden(false);
            }
        }
        if (m_applyMask == applyMask)
            return;


        m_applyMask = applyMask;


        emit applyMaskChanged(m_applyMask);
    }

    void setDrawOnSource(bool drawOnSource)
    {

        FlowNodePort* port=getPortFromKey("drawSource");


        if(port){
            if(!drawOnSource ){

                auto edgeitem=  port->getPortItem()->getInEdgeItems().at(0);
                if(edgeitem){
                    this->getGraph()->removeEdge(edgeitem->getEdge());
                }
                port->setHidden(true);
            }
            else{
                port->setHidden(false);
            }
        }

        if (m_drawOnSource == drawOnSource)
            return;

        m_drawOnSource = drawOnSource;



        emit drawOnSourceChanged(m_drawOnSource);
    }

signals:
    void inputChanged(QMat* input);
    void outputChanged(QMat* output);


    void processingCompleted(ProcessingNode* node);

    void processingChanged(bool processing);


    void sourceFrameChanged(QMat* sourceFrame);

    void processChanged(bool process);


    void processingDoneChanged(bool processingDone);


    void originalInputChanged(QMat* originalInput);

    void inPlaceProcessingChanged(bool inPlaceProcessing);

    void enabledChanged(bool enabled);


    void maskInputChanged(QMat* maskInput);

    void drawSourceChanged(QMat* drawSource);

    void applyMaskChanged(bool applyMask);

    void drawOnSourceChanged(bool drawOnSource);

private:




    bool m_inPlaceProcessing=false;


    bool m_enabled=true;



    bool m_process=false;



    bool m_applyMask=false;

    bool m_drawOnSource=false;

protected:

    QMat* m_input=nullptr;
    QMat* m_originalInput=new QMat();
    QMat* m_maskInput= new QMat();

    QMat* m_drawSource=new QMat();

    QMat* m_output=new QMat();
    QMutex mMutex;
    bool m_processingDone=false;

    QMat* m_originalFrame=new QMat();

    bool m_showOriginal=false;

    virtual void doProcess()=0;

    ProcessingType m_processingType;




    // FlowNode interface
public:
    QString name() const override;

    


    QMat* maskInput() const
    {
        return m_maskInput;
    }
    QMat* drawSource() const
    {
        return m_drawSource;
    }
    bool applyMask() const
    {
        return m_applyMask;
    }
    bool drawOnSource() const
    {
        return m_drawOnSource;
    }
};

Q_DECLARE_METATYPE(cv::Rect);
Q_DECLARE_METATYPE(std::vector<cv::Rect>);

Q_DECLARE_METATYPE(cv::RotatedRect);
Q_DECLARE_METATYPE(std::vector<cv::RotatedRect>);



#endif // FLOWNODE_H
