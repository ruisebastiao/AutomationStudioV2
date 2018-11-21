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



    Q_PROPERTY(GeometricType geometricType READ geometricType WRITE setGeometricType NOTIFY geometricTypeChanged USER("serialize"))

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
        emit geometricTypeChanged(m_geometricType);
    }

    void setOutput1(QVariant output1)
    {
        if (m_output1 == output1)
            return;

        m_output1 = output1;
        emit output1Changed(m_output1);
    }

    void setInput3(QVariant input3)
    {
        if (m_input3 == input3)
            return;

        m_input3 = input3;
        emit input3Changed(m_input3);
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



private:

    GeometricType m_geometricType=Geometric2PointLine;

    QVariant m_output1;

    QLineF lineSegment();
    QVariant m_input1;
    QVariant m_input2;
    QVariant m_input3;


    // FlowNode interface
public:
    
};

#endif // PROCESSINGGEOMETRICNODE_H
