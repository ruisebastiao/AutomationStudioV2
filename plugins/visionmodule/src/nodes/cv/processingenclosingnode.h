#ifndef PROCESSINGENCLOSINGNODE_H
#define PROCESSINGENCLOSINGNODE_H

#include "processingnode.h"



class ProcessingEnclosingNode : public ProcessingNode
{
    Q_OBJECT

    Q_PROPERTY(std::vector<std::vector<cv::Point>> contours READ contours WRITE setContours NOTIFY contoursChanged)
    Q_PROPERTY(FlowNodePort* contoursPort READ contoursPort WRITE setContoursPort NOTIFY contoursPortChanged USER("serialize"))

    Q_PROPERTY(QVariant enclosingShapes READ enclosingShapes WRITE setEnclosingShapes NOTIFY enclosingShapesChanged)
    Q_PROPERTY(FlowNodePort* enclosingShapesPort READ enclosingShapesPort WRITE setEnclosingShapesPort NOTIFY enclosingShapesPortChanged USER("serialize"))

    Q_PROPERTY(EnclosingType enclosingType READ enclosingType WRITE setEnclosingType NOTIFY enclosingTypeChanged USER("serialize"))



public:

    enum EnclosingType {
        RotatedRectEnclosing=0,
        BoundingRectEnclosing
    };
    Q_ENUM(EnclosingType )

    ProcessingEnclosingNode();

    // ProcessingNode interface
    static QQmlComponent *delegate(QQmlEngine &engine) noexcept;
public slots:
    void setInput(QMat *input) override;

    void setContours(std::vector<std::vector<cv::Point>> contours)
    {

        m_contours = contours;
        emit contoursChanged(m_contours);
    }

    void setContoursPort(FlowNodePort* contoursPort)
    {
        if (m_contoursPort == contoursPort)
            return;

        m_contoursPort = contoursPort;
        emit contoursPortChanged(m_contoursPort);
    }

    void setEnclosingShapes(QVariant enclosingShapes)
    {


        m_enclosingShapes = enclosingShapes;
        emit enclosingShapesChanged(m_enclosingShapes);
    }

    void setEnclosingShapesPort(FlowNodePort* enclosingShapesPort)
    {
        if (m_enclosingShapesPort == enclosingShapesPort)
            return;

        m_enclosingShapesPort = enclosingShapesPort;
        emit enclosingShapesPortChanged(m_enclosingShapesPort);
    }

    void setEnclosingType(EnclosingType enclosingType)
    {
        if (m_enclosingType == enclosingType)
            return;

        m_enclosingType = enclosingType;
        emit enclosingTypeChanged(m_enclosingType);
        if(configsLoaded() && connectionsLoaded()){
            setProcess(true);
        }
    }

protected:
    void doProcess() override;

    // JsonSerializable interface
public:
    void DeSerialize(QJsonObject &json) override;



    FlowNodePort* contoursPort() const
    {
        return m_contoursPort;
    }

    QVariant enclosingShapes() const
    {
        return m_enclosingShapes;
    }

    FlowNodePort* enclosingShapesPort() const
    {
        return m_enclosingShapesPort;
    }

    std::vector<std::vector<cv::Point>> contours() const
    {
        return m_contours;
    }

    EnclosingType enclosingType() const
    {
        return m_enclosingType;
    }

signals:
    void contoursChanged(std::vector<std::vector<cv::Point>> contours);

    void contoursPortChanged(FlowNodePort* contoursPort);

    void enclosingShapesChanged(QVariant enclosingShapes);

    void enclosingShapesPortChanged(FlowNodePort* enclosingShapesPort);

    void enclosingTypeChanged(EnclosingType enclosingType);

private:

    std::vector<std::vector<cv::Point>> m_contours;
    FlowNodePort* m_contoursPort=nullptr;
    QVariant m_enclosingShapes=QVariant();

    FlowNodePort* m_enclosingShapesPort=nullptr;
    EnclosingType m_enclosingType=RotatedRectEnclosing;
};

#endif // PROCESSINGENCLOSINGNODE_H
