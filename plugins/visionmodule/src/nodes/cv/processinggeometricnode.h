#ifndef PROCESSINGGEOMETRICNODE_H
#define PROCESSINGGEOMETRICNODE_H

#include "processingnode.h"



class ProcessingGeometricNode : public ProcessingNode
{
    Q_OBJECT


    Q_PROPERTY(QVariant input1 READ input1 WRITE setInput1 NOTIFY input1Changed REVISION 30)

    Q_PROPERTY(QVariant input2 READ input2 WRITE setInput2 NOTIFY input2Changed REVISION 30)


    Q_PROPERTY(QVariant input3 READ input3 WRITE setInput3 NOTIFY input3Changed REVISION 30)


    Q_PROPERTY(QVariant output1 READ output1 WRITE setOutput1 NOTIFY output1Changed REVISION 31)
    Q_PROPERTY(QVariant output2 READ output2 WRITE setOutput2 NOTIFY output2Changed REVISION 31)
    Q_PROPERTY(QVariant output3 READ output3 WRITE setOutput3 NOTIFY output3Changed REVISION 31)



    Q_PROPERTY(GeometricType geometricType READ geometricType WRITE setGeometricType NOTIFY geometricTypeChanged USER("serialize"))

public:
    enum GeometricType {
        GeometricNotSet=0,
        Geometric2PointLine,
        GeometricLinePointLine,
        GeometricPointAngleLengthLine,
        Geometric3PointCircle
    };
    Q_ENUM(GeometricType)

    ProcessingGeometricNode();

    // ProcessingNode interface
public slots:
    void setInput(QVariant input) override;

    void setInput1(QVariant input1)
    {


        m_input1 = input1;

        std::vector<cv::RotatedRect> rect_obj1 = m_input1.value<std::vector<cv::RotatedRect>>();
        std::vector<cv::Rect> rect_obj2 = m_input1.value<std::vector<cv::Rect>>();

        if(rect_obj1.size()>0){

        }


        if(rect_obj2.size()>0){

        }


        emit input1Changed(m_input1);
    }


    void setInput2(QVariant input2)
    {

        m_input2 = input2;

        std::vector<cv::RotatedRect> rect_obj1 = m_input2.value<std::vector<cv::RotatedRect>>();
        std::vector<cv::Rect> rect_obj2 = m_input2.value<std::vector<cv::Rect>>();

        if(rect_obj1.size()>0){

        }


        if(rect_obj2.size()>0){

        }


        emit input2Changed(m_input2);
    }

    void setGeometricType(GeometricType geometricType)
    {
        if (m_geometricType == geometricType)
            return;

        m_geometricType = geometricType;

        FlowNodePort* port;
        switch (m_geometricType) {
        case Geometric2PointLine:

            port=getPortFromKey("input1");
            if(port){
                port->setHidden(false);
                port->setPortLabel("Start Point");
            }
            port=getPortFromKey("input2");
            if(port){
                port->setHidden(false);
                port->setPortLabel("End Point");
            }

            port=getPortFromKey("input3");
            if(port){
                port->setHidden(true);

            }

            port=getPortFromKey("output1");
            if(port){
                port->setHidden(false);
                port->setPortLabel("Line Segment");
            }

            port=getPortFromKey("output2");
            if(port){
                port->setHidden(false);
                port->setPortLabel("Line Angle");
            }
            port=getPortFromKey("output3");
            if(port){
                port->setHidden(true);

            }



            break;
        case GeometricPointAngleLengthLine:
            port=getPortFromKey("input1");
            if(port){
                port->setHidden(false);
                port->setPortLabel("Center Point");
            }
            port=getPortFromKey("input2");
            if(port){
                port->setHidden(false);
                port->setPortLabel("Angle");
            }

            port=getPortFromKey("input3");
            if(port){
                port->setHidden(false);
                port->setPortLabel("Length");
            }



            break;
        case GeometricLinePointLine:
            port=getPortFromKey("input1");
            if(port){
                port->setHidden(false);
                port->setPortLabel("Start Point");
            }
            port=getPortFromKey("input2");
            if(port){
                port->setHidden(false);
                port->setPortLabel("Line Segment");
            }

            port=getPortFromKey("input3");
            if(port){
                port->setHidden(true);

            }

            port=getPortFromKey("output1");
            if(port){
                port->setHidden(false);
                port->setPortLabel("Line Segment");
            }

            port=getPortFromKey("output2");
            if(port){
                port->setHidden(false);
                port->setPortLabel("Line Angle");
            }
            port=getPortFromKey("output3");
            if(port){
                port->setHidden(true);

            }

            break;
        case Geometric3PointCircle:
            break;
        }



        emit geometricTypeChanged(m_geometricType);
    }

    void setOutput1(QVariant output1)
    {


        m_output1 = output1;
        emit output1Changed(m_output1);
    }

    void setInput3(QVariant input3)
    {


        m_input3 = input3;
        emit input3Changed(m_input3);
    }


    void setOutput2(QVariant output2)
    {


        m_output2 = output2;
        emit output2Changed(m_output2);
    }

    void setOutput3(QVariant output3)
    {


        m_output3 = output3;
        emit output3Changed(m_output3);
    }

protected:
    void doProcess() override;

    // JsonSerializable interface
public:
    void DeSerialize(QJsonObject &json) override;
    static  QQmlComponent *delegate(QQmlEngine &engine)noexcept;
    QVariant input1() const
    {
        return m_input1;
    }

    QVariant input2() const
    {
        return m_input2;
    }


    GeometricType geometricType() const
    {
        return m_geometricType;
    }

    QVariant output1() const
    {
        return m_output1;
    }

    QVariant input3() const
    {
        return m_input3;
    }


signals:
    void input1Changed(QVariant input1);

    void input2Changed(QVariant input2);
    void geometricTypeChanged(GeometricType geometricType);
    void output1Changed(QVariant output1);
    void input3Changed(QVariant input3);



    void output2Changed(QVariant output2);

    void output3Changed(QVariant output3);

private:

    GeometricType m_geometricType=GeometricNotSet;

    QVariant m_output1=QVariant::fromValue(nullptr);
    QVariant m_input1=QVariant::fromValue(new QMat());
    QVariant m_input2=QVariant::fromValue(new QMat());
    QVariant m_input3=QVariant::fromValue(new QMat());

    QVariant lineSegment();




    // FlowNode interface
    QVariant m_output2=QVariant::fromValue(nullptr);

    QVariant m_output3=QVariant::fromValue(nullptr);

public:

    QVariant output2() const
    {
        return m_output2;
    }
    QVariant output3() const
    {
        return m_output3;
    }
};

#endif // PROCESSINGGEOMETRICNODE_H
