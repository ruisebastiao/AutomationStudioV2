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

    Q_PROPERTY(double minCountourHeight READ minCountourHeight WRITE setMinCountourHeight NOTIFY minCountourHeightChanged USER("serialize"))
    Q_PROPERTY(double maxCountourHeight READ maxCountourHeight WRITE setMaxCountourHeight NOTIFY maxCountourHeightChanged USER("serialize"))

    Q_PROPERTY(double minCountourWidth READ minCountourWidth WRITE setMinCountourWidth NOTIFY minCountourWidthChanged USER("serialize"))
    Q_PROPERTY(double maxCountourWidth READ maxCountourWidth WRITE setMaxCountourWidth NOTIFY maxCountourWidthChanged USER("serialize"))


    Q_PROPERTY(std::vector<std::vector<cv::Point>> filteredContours READ filteredContours NOTIFY filteredContoursChanged)

    Q_PROPERTY(FlowNodePort* filteredContoursPort READ filteredContoursPort WRITE setFilteredContoursPort NOTIFY filteredContoursPortChanged USER("serialize"))

    Q_PROPERTY(int filteredContourIndex READ filteredContourIndex WRITE setFilteredContourIndex NOTIFY filteredContourIndexChanged)
    Q_PROPERTY(FlowNodePort* filteredContourIndexPort READ filteredContourIndexPort WRITE setFilteredContourIndexPort NOTIFY filteredContourIndexPortChanged USER("serialize"))

    Q_PROPERTY(std::vector<cv::Point> filteredContour READ filteredContour WRITE setFilteredContour NOTIFY filteredContourChanged)
    Q_PROPERTY(FlowNodePort* filteredContourPort READ filteredContourPort WRITE setFilteredContourPort NOTIFY filteredContourPortChanged USER("serialize"))



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

    double minCountourHeight() const
    {
        return m_minCountourHeight;
    }

    double maxCountourHeight() const
    {
        return m_maxCountourHeight;
    }

    double minCountourWidth() const
    {
        return m_minCountourWidth;
    }

    double maxCountourWidth() const
    {
        return m_maxCountourWidth;
    }

    int filteredContourIndex() const
    {
        return m_filteredContourIndex;
    }

    FlowNodePort* filteredContourIndexPort() const
    {
        return m_filteredContourIndexPort;
    }

    std::vector<cv::Point> filteredContour() const
    {
        return m_filteredContour;
    }

    FlowNodePort* filteredContourPort() const
    {
        return m_filteredContourPort;
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

    double m_minCountourHeight=0;

    double m_maxCountourHeight=1000;

    double m_minCountourWidth=0;

    double m_maxCountourWidth=1000;

    int m_filteredContourIndex=0;

    FlowNodePort* m_filteredContourIndexPort=nullptr;

    std::vector<cv::Point> m_filteredContour;

    FlowNodePort* m_filteredContourPort=nullptr;

signals:
    void totalContoursChanged(int totalContours);
    void minCountourLengthChanged(double minCountourLength);
    void maxCountourLengthChanged(double maxCountourLength);
    void totalFilteredContoursChanged(int totalFilteredContours);
    void filteredContoursChanged(std::vector<std::vector<cv::Point>> filteredContours);

    // JsonSerializable interface
    void filteredContoursPortChanged(FlowNodePort* filteredContoursPort);

    void minCountourHeightChanged(double minCountourHeight);

    void maxCountourHeightChanged(double maxCountourHeight);

    void minCountourWidthChanged(double minCountourWidth);

    void maxCountourWidthChanged(double maxCountourWidth);

    void filteredContourIndexChanged(int filteredContourIndex);

    void filteredContourIndexPortChanged(FlowNodePort* filteredContourIndexPort);

    void filteredContourChanged(std::vector<cv::Point> filteredContour);

    void filteredContourPortChanged(FlowNodePort* filteredContourPort);

protected:
    void DeSerialize(QJsonObject &json) override;

    // ProcessingNode interface
protected:
    void doProcess() override;

    // ProcessingNode interface
public slots:
    virtual void setInput(QMat *input) override;
    void setMinCountourHeight(double minCountourHeight)
    {

        m_minCountourHeight = minCountourHeight;
        emit minCountourHeightChanged(m_minCountourHeight);
    }
    void setMaxCountourHeight(double maxCountourHeight)
    {

        m_maxCountourHeight = maxCountourHeight;
        emit maxCountourHeightChanged(m_maxCountourHeight);
    }
    void setMinCountourWidth(double minCountourWidth)
    {

        m_minCountourWidth = minCountourWidth;
        emit minCountourWidthChanged(m_minCountourWidth);
    }
    void setMaxCountourWidth(double maxCountourWidth)
    {

        m_maxCountourWidth = maxCountourWidth;
        emit maxCountourWidthChanged(m_maxCountourWidth);
    }
    void setFilteredContourIndex(int filteredContourIndex)
    {
        m_filteredContourIndex = filteredContourIndex;
        emit filteredContourIndexChanged(m_filteredContourIndex);
    }
    void setFilteredContourIndexPort(FlowNodePort* filteredContourIndexPort)
    {
        if (m_filteredContourIndexPort == filteredContourIndexPort)
            return;

        m_filteredContourIndexPort = filteredContourIndexPort;
        emit filteredContourIndexPortChanged(m_filteredContourIndexPort);
    }
    void setFilteredContour(std::vector<cv::Point> filteredContour)
    {

        m_filteredContour = filteredContour;
        emit filteredContourChanged(m_filteredContour);
    }
    void setFilteredContourPort(FlowNodePort* filteredContourPort)
    {
        if (m_filteredContourPort == filteredContourPort)
            return;

        m_filteredContourPort = filteredContourPort;
        emit filteredContourPortChanged(m_filteredContourPort);
    }
};

#endif // PROCESSINGCONTOURSNODE_H
