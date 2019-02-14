#ifndef PROCESSINGMASKNODE_H
#define PROCESSINGMASKNODE_H

#include "processingnode.h"



class ProcessingMaskNode : public ProcessingNode
{
    Q_OBJECT

    Q_PROPERTY(MaskType maskType READ maskType WRITE setMaskType NOTIFY maskTypeChanged USER("serialize"))

    Q_PROPERTY(QVariant input1 READ input1 WRITE setInput1 NOTIFY input1Changed REVISION 30 USER("serialize"))
    Q_PROPERTY(QVariant input2 READ input2 WRITE setInput2 NOTIFY input2Changed REVISION 30 USER("serialize"))
    Q_PROPERTY(QVariant input3 READ input3 WRITE setInput3 NOTIFY input3Changed REVISION 30 USER("serialize"))
    Q_PROPERTY(QVariant input4 READ input4 WRITE setInput4 NOTIFY input4Changed REVISION 30 USER("serialize"))

    Q_PROPERTY(QVariant maskOutput READ maskOutput WRITE setMaskOutput NOTIFY maskOutputChanged REVISION 31)

    //    Q_PROPERTY(QVariant input2 READ input2 WRITE setInput2 NOTIFY input2Changed REVISION 31)



public:
    ProcessingMaskNode();

    enum MaskType {
        MaskNone=0,
        MaskCircleRadius
    };
    Q_ENUM(MaskType)

    static  QQmlComponent *delegate(QQmlEngine &engine)noexcept;

    // JsonSerializable interface
private:
    MaskType m_maskType=MaskCircleRadius;

    QVariant m_input1=QVariant(QString(""));

    QVariant m_input2=QVariant(QString(""));

    QVariant m_input3=QVariant(QString(""));

    QVariant m_input4=QVariant(QString(""));

    QVariant m_maskOutput=QVariant::fromValue(new QMat());

public:
    void DeSerialize(QJsonObject &json) override;

    // ProcessingNode interface
    MaskType maskType() const
    {
        return m_maskType;
    }

    QVariant input1()
    {

        return m_input1;
    }

    QVariant input2() const
    {
        return m_input2;
    }

    QVariant input3() const
    {
        return m_input3;
    }

    QVariant input4() const
    {
        return m_input4;
    }

    QVariant maskOutput() const
    {
        return m_maskOutput;
    }

public slots:
    void setInput(QVariant input) override;

    void setMaskType(MaskType maskType)
    {
        if (m_maskType == maskType)
            return;

        m_maskType = maskType;

        FlowNodePort* port;
        switch (m_maskType) {
        case MaskNone:
            port=getPortFromKey("input1");
            if(port){
                port->setHidden(true);

            }
            port=getPortFromKey("input2");
            if(port){
                port->setHidden(true);

            }

            port=getPortFromKey("input3");
            if(port){
                port->setHidden(true);

            }

            port=getPortFromKey("input4");
            if(port){
                port->setHidden(true);

            }


            break;
        case MaskCircleRadius:
            port=getPortFromKey("input1");
            if(port){
                port->setHidden(false);
                port->setPortLabel("Center Point");
            }
            port=getPortFromKey("input2");
            if(port){
                port->setHidden(false);
                port->setPortLabel("Radius");
            }

            port=getPortFromKey("input3");
            if(port){
                port->setHidden(false);
                port->setPortLabel("Inner Radius");
            }

            port=getPortFromKey("input4");
            if(port){
                port->setHidden(true);

            }


            break;
        }

        emit maskTypeChanged(m_maskType);
    }

    void setInput1(QVariant input1)
    {

         if(maskType()== MaskCircleRadius){
             if(input1.canConvert<QString>()){
                 QString in=input1.value<QString>();
                 QStringList splitted=in.split(',');
                 if(splitted.length()==2){
                     cv::Point center(-1,-1);
                     center.x=splitted.at(0).toInt();
                     center.y=splitted.at(1).toInt();

                     input1=QVariant::fromValue(center);
                     //input1.fro
                 }
             }
         }
        m_input1 = input1;
        emit input1Changed(m_input1);
    }

    void setInput2(QVariant input2)
    {

        m_input2 = input2;
        emit input2Changed(m_input2);
    }

    void setInput3(QVariant input3)
    {

        m_input3 = input3;
        emit input3Changed(m_input3);
    }

    void setInput4(QVariant input4)
    {


        m_input4 = input4;
        emit input4Changed(m_input4);
    }

    void setMaskOutput(QVariant maskOutput)
    {
        if (m_maskOutput == maskOutput)
            return;

        m_maskOutput = maskOutput;
        emit maskOutputChanged(m_maskOutput);
    }

signals:
    void maskTypeChanged(MaskType maskType);

    void input1Changed(QVariant input1);

    void input2Changed(QVariant input2);

    void input3Changed(QVariant input3);

    void input4Changed(QVariant input4);

    void maskOutputChanged(QVariant maskOutput);

protected:
    void doProcess() override;

    // JsonSerializable interface
public:
    void Serialize(QJsonObject &json) override;
};

#endif // PROCESSINGMASKNODE_H
