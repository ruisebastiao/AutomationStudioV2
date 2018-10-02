#ifndef PROCESSINGCONTOURSNODE_H
#define PROCESSINGCONTOURSNODE_H

#include "processingnode.h"



class ProcessingContoursNode : public ProcessingNode
{
    Q_OBJECT

    Q_PROPERTY(int totalContours READ totalContours WRITE setTotalContours NOTIFY totalContoursChanged)
    Q_PROPERTY(int totalFilteredContours READ totalFilteredContours WRITE setTotalFilteredContours NOTIFY totalFilteredContoursChanged)


    Q_PROPERTY(double minCountourLength READ minCountourLength WRITE setMinCountourLength NOTIFY minCountourLengthChanged USER("serialize"))
    Q_PROPERTY(double maxCountourLength READ maxCountourLength WRITE setMaxCountourLength NOTIFY maxCountourLengthChanged USER("serialize"))

    Q_PROPERTY(std::vector<std::vector<cv::Point>> filteredContours READ filteredContours NOTIFY filteredContoursChanged)

    Q_PROPERTY(FlowNodePort* filteredContoursPort READ filteredContoursPort WRITE setFilteredContoursPort NOTIFY filteredContoursPortChanged USER("serialize"))


public:
    ProcessingContoursNode();

    static  QQmlComponent*      delegate(QQmlEngine& engine) noexcept;


    // ProcessingNode interface
public:

    int totalContours() const
    {
        return m_totalContours;
    }

    double minCountourLength() const
    {
        return m_minCountourLength;
    }

    double maxCountourLength() const
    {
        return m_maxCountourLength;
    }

    int totalFilteredContours() const
    {
        return m_totalFilteredContours;
    }

    std::vector<std::vector<cv::Point>> filteredContours() const
    {
        return m_filteredContours;
    }

    FlowNodePort* filteredContoursPort() const
    {
        return m_filteredContoursPort;
    }

public slots:


    double contourPerimeter(std::vector<cv::Point> contour);


    void setTotalContours(int totalContours)
    {
        if (m_totalContours == totalContours)
            return;

        m_totalContours = totalContours;
        emit totalContoursChanged(m_totalContours);
    }
    void setMinCountourLength(double minCountourLength)
    {
        if (qFuzzyCompare(m_minCountourLength, minCountourLength))
            return;

        m_minCountourLength = minCountourLength;
        emit minCountourLengthChanged(m_minCountourLength);
       // process();
    }

    void setTotalFilteredContours(int totalFilteredContours)
    {
        if (m_totalFilteredContours == totalFilteredContours)
            return;

        m_totalFilteredContours = totalFilteredContours;
        emit totalFilteredContoursChanged(m_totalFilteredContours);
    }

    void setMaxCountourLength(double maxCountourLength)
    {
        if (qFuzzyCompare(m_maxCountourLength, maxCountourLength))
            return;

        m_maxCountourLength = maxCountourLength;
        emit maxCountourLengthChanged(m_maxCountourLength);
       // process();
    }


    void setFilteredContoursPort(FlowNodePort* filteredContoursPort)
    {
        if (m_filteredContoursPort == filteredContoursPort)
            return;

        m_filteredContoursPort = filteredContoursPort;
        emit filteredContoursPortChanged(m_filteredContoursPort);
    }

private:
    int m_totalContours=0;

    double m_minCountourLength=0;

    double m_maxCountourLength=0;

    int m_totalFilteredContours=0;

    std::vector<std::vector<cv::Point>> m_filteredContours;

    FlowNodePort* m_filteredContoursPort=nullptr;

signals:
    void totalContoursChanged(int totalContours);
    void minCountourLengthChanged(double minCountourLength);
    void maxCountourLengthChanged(double maxCountourLength);
    void totalFilteredContoursChanged(int totalFilteredContours);
    void filteredContoursChanged(std::vector<std::vector<cv::Point>> filteredContours);

    // JsonSerializable interface
    void filteredContoursPortChanged(FlowNodePort* filteredContoursPort);

protected:
    void DeSerialize(QJsonObject &json) override;

    // ProcessingNode interface
protected:
    void doProcess() override;

    // ProcessingNode interface
public slots:
    virtual void setInput(QMat *input) override;
};

#endif // PROCESSINGCONTOURSNODE_H
