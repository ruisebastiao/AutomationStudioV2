#ifndef PROCESSINGSHAPESNODE_H
#define PROCESSINGSHAPESNODE_H

#include "processingnode.h"



class ProcessingShapesNode : public ProcessingNode
{
    Q_OBJECT

    Q_PROPERTY(std::vector<std::vector<cv::Point>> contours READ contours WRITE setContours NOTIFY contoursChanged)
    Q_PROPERTY(FlowNodePort* contoursPort READ contoursPort WRITE setContoursPort NOTIFY contoursPortChanged USER("serialize"))



public:
    ProcessingShapesNode();

    static  QQmlComponent*      delegate(QQmlEngine& engine) noexcept;


    // ProcessingNode interface
public:

    std::vector<std::vector<cv::Point>> contours() const
    {
        return m_contours;
    }
    FlowNodePort* contoursPort() const
    {
        return m_contoursPort;
    }

public slots:
    void setContours(std::vector<std::vector<cv::Point>> contours)
    {
        m_contours = contours;
        emit contoursChanged(m_contours);
        process();    
    }
    void setContoursPort(FlowNodePort* contoursPort)
    {
        if (m_contoursPort == contoursPort)
            return;

        m_contoursPort = contoursPort;
        emit contoursPortChanged(m_contoursPort);
    }

private:

    std::vector<std::vector<cv::Point>> m_contours;
    FlowNodePort* m_contoursPort=nullptr;

signals:
    void contoursChanged(std::vector<std::vector<cv::Point>> contours);
    void contoursPortChanged(FlowNodePort* contoursPort);

    // JsonSerializable interface
protected:
    void DeSerialize(QJsonObject &json) override;

    // ProcessingNode interface
protected:
    void doProcess() override;

    // ProcessingNode interface
public slots:
    virtual void setInput(QMat *input) override;
};

#endif // PROCESSINGSHAPESNODE_H
