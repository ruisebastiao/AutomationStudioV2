#ifndef PROCESSINGGEOMETRICNODE_H
#define PROCESSINGGEOMETRICNODE_H

#include "processingnode.h"



class ProcessingGeometricNode : public ProcessingNode
{
    Q_OBJECT


    Q_PROPERTY(QVariant input1 READ input1 WRITE setInput1 NOTIFY input1Changed)
    Q_PROPERTY(FlowNodePort* input1Port READ input1Port WRITE setInput1Port NOTIFY input1PortChanged USER("serialize"))

    Q_PROPERTY(QVariant input2 READ input2 WRITE setInput2 NOTIFY input2Changed)
    Q_PROPERTY(FlowNodePort* input2Port READ input2Port WRITE setInput2Port NOTIFY input2PortChanged USER("serialize"))

    Q_PROPERTY(QVariant input3 READ input3 WRITE setInput3 NOTIFY input3Changed)
    Q_PROPERTY(FlowNodePort* input3Port READ input3Port WRITE setInput3Port NOTIFY input3PortChanged USER("serialize"))

    Q_PROPERTY(QVariant output1 READ output1 WRITE setOutput1 NOTIFY output1Changed)
    Q_PROPERTY(FlowNodePort* output1Port READ output1Port WRITE setOutput1Port NOTIFY output1PortChanged USER("serialize"))


    Q_PROPERTY(GeometricType geometricType READ geometricType WRITE setGeometricType NOTIFY geometricTypeChanged USER("serialize"))

private:

    QVariant m_input1;

    FlowNodePort* m_input1Port=nullptr;

    QVariant m_input2;

    FlowNodePort* m_input2Port=nullptr;


public:
    enum GeometricType {
        Geometric2PointLine=0,
        GeometricPointAngleLengthLine,
        Geometric3PointCircle
    };
    Q_ENUM(GeometricType)

    ProcessingGeometricNode();

    // ProcessingNode interface
public slots:
    void setInput(QMat *input) override;

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

    void setInput1Port(FlowNodePort* input1Port)
    {
        if (m_input1Port == input1Port)
            return;

        m_input1Port = input1Port;
        emit input1PortChanged(m_input1Port);
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

    void setInput2Port(FlowNodePort* input2Port)
    {
        if (m_input2Port == input2Port)
            return;

        m_input2Port = input2Port;
        emit input2PortChanged(m_input2Port);
    }

    void setGeometricType(GeometricType geometricType)
    {
        if (m_geometricType == geometricType)
            return;

        m_geometricType = geometricType;
        emit geometricTypeChanged(m_geometricType);
    }

    void setOutput1(QVariant output1)
    {
        if (m_output1 == output1)
            return;

        m_output1 = output1;
        emit output1Changed(m_output1);
    }

    void setOutput1Port(FlowNodePort* output1Port)
    {
        if (m_output1Port == output1Port)
            return;

        m_output1Port = output1Port;
        emit output1PortChanged(m_output1Port);
    }

    void setInput3(QVariant input3)
    {
        if (m_input3 == input3)
            return;

        m_input3 = input3;
        emit input3Changed(m_input3);
    }

    void setInput3Port(FlowNodePort* input3Port)
    {
        if (m_input3Port == input3Port)
            return;

        m_input3Port = input3Port;
        emit input3PortChanged(m_input3Port);
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
    FlowNodePort* input1Port() const
    {
        return m_input1Port;
    }

    QVariant input2() const
    {
        return m_input2;
    }

    FlowNodePort* input2Port() const
    {
        return m_input2Port;
    }

    GeometricType geometricType() const
    {
        return m_geometricType;
    }

    QVariant output1() const
    {
        return m_output1;
    }

    FlowNodePort* output1Port() const
    {
        return m_output1Port;
    }

    QVariant input3() const
    {
        return m_input3;
    }

    FlowNodePort* input3Port() const
    {
        return m_input3Port;
    }

signals:
    void input1Changed(QVariant input1);
    void input1PortChanged(FlowNodePort* input1Port);
    void input2Changed(QVariant input2);
    void input2PortChanged(FlowNodePort* input2Port);
    void geometricTypeChanged(GeometricType geometricType);

    void output1Changed(QVariant output1);

    void output1PortChanged(FlowNodePort* output1Port);

    void input3Changed(QVariant input3);

    void input3PortChanged(FlowNodePort* input3Port);

private:

    GeometricType m_geometricType=Geometric2PointLine;

    QVariant m_output1;
    FlowNodePort* m_output1Port=nullptr;
    QLineF lineSegment();
    QVariant m_input3;
    FlowNodePort* m_input3Port=nullptr;

    // FlowNode interface
public:
    void initializePorts() override;
};

#endif // PROCESSINGGEOMETRICNODE_H
