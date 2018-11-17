#ifndef PROCESSINGCONTOURSNODE_H
#define PROCESSINGCONTOURSNODE_H

#include "processingnode.h"



class ProcessingContoursNode : public ProcessingNode
{
    Q_OBJECT

    Q_PROPERTY(int totalContours READ totalContours WRITE setTotalContours NOTIFY totalContoursChanged)
    Q_PROPERTY(int totalFilteredContours READ totalFilteredContours WRITE setTotalFilteredContours NOTIFY totalFilteredContoursChanged)


    Q_PROPERTY(int minCountourLength READ minCountourLength WRITE setMinCountourLength NOTIFY minCountourLengthChanged USER("serialize"))
    Q_PROPERTY(int maxCountourLength READ maxCountourLength WRITE setMaxCountourLength NOTIFY maxCountourLengthChanged USER("serialize"))

    Q_PROPERTY(int minCountourHeight READ minCountourHeight WRITE setMinCountourHeight NOTIFY minCountourHeightChanged USER("serialize"))
    Q_PROPERTY(int maxCountourHeight READ maxCountourHeight WRITE setMaxCountourHeight NOTIFY maxCountourHeightChanged USER("serialize"))

    Q_PROPERTY(int minCountourWidth READ minCountourWidth WRITE setMinCountourWidth NOTIFY minCountourWidthChanged USER("serialize"))
    Q_PROPERTY(int maxCountourWidth READ maxCountourWidth WRITE setMaxCountourWidth NOTIFY maxCountourWidthChanged USER("serialize"))

    Q_PROPERTY(int minCountourArea READ minCountourArea WRITE setMinCountourArea NOTIFY minCountourAreaChanged USER("serialize"))
    Q_PROPERTY(int maxCountourArea READ maxCountourArea WRITE setMaxCountourArea NOTIFY maxCountourAreaChanged USER("serialize"))


    Q_PROPERTY(std::vector<std::vector<cv::Point>> filteredContours READ filteredContours NOTIFY filteredContoursChanged)



public:
    ProcessingContoursNode();


    static  QQmlComponent*      delegate(QQmlEngine& engine) noexcept;

    // ProcessingNode interface
    int totalContours() const
    {
        return m_totalContours;
    }

    int minCountourLength() const
    {
        return m_minCountourLength;
    }

    int minCountourHeight() const
    {
        return m_minCountourHeight;
    }

    int maxCountourHeight() const
    {
        return m_maxCountourHeight;
    }

    int minCountourWidth() const
    {
        return m_minCountourWidth;
    }

    int minCountourArea() const
    {
        return m_minCountourArea;
    }

    int maxCountourArea() const
    {
        return m_maxCountourArea;
    }

    std::vector<std::vector<cv::Point>> filteredContours() const
    {
        return m_filteredContours;
    }

    int maxCountourLength() const
    {
        return m_maxCountourLength;
    }

    int maxCountourWidth() const
    {
        return m_maxCountourWidth;
    }

    int totalFilteredContours() const
    {
        return m_totalFilteredContours;
    }

public slots:
    virtual void setInput(QMat *input) override;

    void setTotalContours(int totalContours)
    {
        if (m_totalContours == totalContours)
            return;

        m_totalContours = totalContours;
        emit totalContoursChanged(m_totalContours);
    }

    void setMinCountourLength(int minCountourLength)
    {
        if (m_minCountourLength == minCountourLength)
            return;

        m_minCountourLength = minCountourLength;
        emit minCountourLengthChanged(m_minCountourLength);
    }

    void setMinCountourHeight(int minCountourHeight)
    {
        if (m_minCountourHeight == minCountourHeight)
            return;

        m_minCountourHeight = minCountourHeight;
        emit minCountourHeightChanged(m_minCountourHeight);
    }

    void setMaxCountourHeight(int maxCountourHeight)
    {
        if (m_maxCountourHeight == maxCountourHeight)
            return;

        m_maxCountourHeight = maxCountourHeight;
        emit maxCountourHeightChanged(m_maxCountourHeight);
    }

    void setMinCountourWidth(int minCountourWidth)
    {
        if (m_minCountourWidth == minCountourWidth)
            return;

        m_minCountourWidth = minCountourWidth;
        emit minCountourWidthChanged(m_minCountourWidth);
    }

    void setMinCountourArea(int minCountourArea)
    {
        if (m_minCountourArea == minCountourArea)
            return;

        m_minCountourArea = minCountourArea;
        emit minCountourAreaChanged(m_minCountourArea);
    }

    void setMaxCountourArea(int maxCountourArea)
    {
        if (m_maxCountourArea == maxCountourArea)
            return;

        m_maxCountourArea = maxCountourArea;
        emit maxCountourAreaChanged(m_maxCountourArea);
    }

    void setMaxCountourLength(int maxCountourLength)
    {
        if (m_maxCountourLength == maxCountourLength)
            return;

        m_maxCountourLength = maxCountourLength;
        emit maxCountourLengthChanged(m_maxCountourLength);
    }

    void setMaxCountourWidth(int maxCountourWidth)
    {
        if (m_maxCountourWidth == maxCountourWidth)
            return;

        m_maxCountourWidth = maxCountourWidth;
        emit maxCountourWidthChanged(m_maxCountourWidth);
    }

    void setTotalFilteredContours(int totalFilteredContours)
    {
        if (m_totalFilteredContours == totalFilteredContours)
            return;

        m_totalFilteredContours = totalFilteredContours;
        emit totalFilteredContoursChanged(m_totalFilteredContours);
    }

signals:
    void totalContoursChanged(int totalContours);

    void minCountourLengthChanged(int minCountourLength);

    void minCountourHeightChanged(int minCountourHeight);

    void maxCountourHeightChanged(int maxCountourHeight);

    void minCountourWidthChanged(int minCountourWidth);

    void minCountourAreaChanged(int minCountourArea);

    void maxCountourAreaChanged(int maxCountourArea);

    void filteredContoursChanged(std::vector<std::vector<cv::Point>> filteredContours);

    void maxCountourLengthChanged(int maxCountourLength);

    void maxCountourWidthChanged(int maxCountourWidth);

    void totalFilteredContoursChanged(int totalFilteredContours);

protected:
    virtual void doProcess() override;

private:

    int m_totalContours=0;
    int m_minCountourLength=100;
    int m_maxCountourLength=2000;

    int m_minCountourHeight=1000;
    int m_maxCountourHeight=2000;

    int m_minCountourWidth=1000;
    int m_maxCountourWidth=2000;

    int m_minCountourArea=1000;
    int m_maxCountourArea=50000;
    std::vector<std::vector<cv::Point>> m_filteredContours;
    int m_totalFilteredContours=0;

    // JsonSerializable interface
public:
    virtual void DeSerialize(QJsonObject &json) override;
};

#endif // PROCESSINGCONTOURSNODE_H
