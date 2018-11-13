#ifndef PREPROCESSINGCONTOURS_H
#define PREPROCESSINGCONTOURS_H

#include "preprocessing.h"



class PreProcessingContours:public PreProcessing
{
    Q_OBJECT

    Q_PROPERTY(int threshold READ threshold WRITE setThreshold NOTIFY thresholdChanged USER("serialize"))

    Q_PROPERTY(int totalContours READ totalContours WRITE setTotalContours NOTIFY totalContoursChanged)
    Q_PROPERTY(int totalFilteredContours READ totalFilteredContours WRITE setTotalFilteredContours NOTIFY totalFilteredContoursChanged)


    Q_PROPERTY(double minCountourLength READ minCountourLength WRITE setMinCountourLength NOTIFY minCountourLengthChanged USER("serialize"))
    Q_PROPERTY(double maxCountourLength READ maxCountourLength WRITE setMaxCountourLength NOTIFY maxCountourLengthChanged USER("serialize"))

    Q_PROPERTY(double minCountourHeight READ minCountourHeight WRITE setMinCountourHeight NOTIFY minCountourHeightChanged USER("serialize"))
    Q_PROPERTY(double maxCountourHeight READ maxCountourHeight WRITE setMaxCountourHeight NOTIFY maxCountourHeightChanged USER("serialize"))

    Q_PROPERTY(double minCountourWidth READ minCountourWidth WRITE setMinCountourWidth NOTIFY minCountourWidthChanged USER("serialize"))
    Q_PROPERTY(double maxCountourWidth READ maxCountourWidth WRITE setMaxCountourWidth NOTIFY maxCountourWidthChanged USER("serialize"))


    Q_PROPERTY(std::vector<std::vector<cv::Point>> filteredContours READ filteredContours NOTIFY filteredContoursChanged)




public:
    PreProcessingContours();

    // PreProcessing interface
public:
    void apply(cv::Mat& input, cv::Mat& preprocessed,cv::Mat &original) override;
    int threshold() const
    {
        return m_threshold;
    }
    int totalContours() const
    {
        return m_totalContours;
    }

    int totalFilteredContours() const
    {
        return m_totalFilteredContours;
    }

    double minCountourLength() const
    {
        return m_minCountourLength;
    }

    double maxCountourLength() const
    {
        return m_maxCountourLength;
    }

    std::vector<std::vector<cv::Point>> filteredContours() const
    {
        return m_filteredContours;
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

public slots:
    void setThreshold(int threshold)
    {
        if (m_threshold == threshold)
            return;

        m_threshold = threshold;
        emit thresholdChanged(m_threshold);
        emit preProcessorConditionChanged();
    }
    void setTotalContours(int totalContours)
    {
        if (m_totalContours == totalContours)
            return;

        m_totalContours = totalContours;
        emit totalContoursChanged(m_totalContours);
    }

    void setTotalFilteredContours(int totalFilteredContours)
    {
        if (m_totalFilteredContours == totalFilteredContours)
            return;

        m_totalFilteredContours = totalFilteredContours;
        emit totalFilteredContoursChanged(m_totalFilteredContours);
        emit preProcessorConditionChanged();
    }

    void setMinCountourLength(double minCountourLength)
    {
        if (qFuzzyCompare(m_minCountourLength, minCountourLength))
            return;

        m_minCountourLength = minCountourLength;
        emit minCountourLengthChanged(m_minCountourLength);
        emit preProcessorConditionChanged();
    }

    void setMaxCountourLength(double maxCountourLength)
    {
        if (qFuzzyCompare(m_maxCountourLength, maxCountourLength))
            return;

        m_maxCountourLength = maxCountourLength;
        emit maxCountourLengthChanged(m_maxCountourLength);
        emit preProcessorConditionChanged();
    }

    void setMinCountourHeight(double minCountourHeight)
    {

        if (qFuzzyCompare(m_minCountourHeight, minCountourHeight))
            return;

        m_minCountourHeight = minCountourHeight;
        emit minCountourHeightChanged(m_minCountourHeight);
        emit preProcessorConditionChanged();
    }

    void setMaxCountourHeight(double maxCountourHeight)
    {

        if (qFuzzyCompare(m_maxCountourHeight, maxCountourHeight))
            return;

        m_maxCountourHeight = maxCountourHeight;
        emit maxCountourHeightChanged(m_maxCountourHeight);
        emit preProcessorConditionChanged();
    }

    void setMinCountourWidth(double minCountourWidth)
    {

        if (qFuzzyCompare(m_minCountourWidth, minCountourWidth))
            return;

        m_minCountourWidth = minCountourWidth;
        emit minCountourWidthChanged(m_minCountourWidth);
        emit preProcessorConditionChanged();
    }

    void setMaxCountourWidth(double maxCountourWidth)
    {

        if (qFuzzyCompare(m_maxCountourWidth, maxCountourWidth))
            return;

        m_maxCountourWidth = maxCountourWidth;
        emit maxCountourWidthChanged(m_maxCountourWidth);
        emit preProcessorConditionChanged();
    }

signals:
    void thresholdChanged(int threshold);

    void totalContoursChanged(int totalContours);

    void totalFilteredContoursChanged(int totalFilteredContours);

    void minCountourLengthChanged(double minCountourLength);

    void maxCountourLengthChanged(double maxCountourLength);

    void filteredContoursChanged(std::vector<std::vector<cv::Point>> filteredContours);

    void minCountourHeightChanged(double minCountourHeight);

    void maxCountourHeightChanged(double maxCountourHeight);

    void minCountourWidthChanged(double minCountourWidth);

    void maxCountourWidthChanged(double maxCountourWidth);

private:
    int m_threshold=125;
    int m_totalContours=0;
    int m_totalFilteredContours=0;
    double m_minCountourLength=500;
    double m_maxCountourLength=1000;

    std::vector<std::vector<cv::Point>> m_filteredContours;
    double m_minCountourHeight=100;
    double m_maxCountourHeight=1000;
    double m_minCountourWidth=100;
    double m_maxCountourWidth=1000;
};

#endif // PREPROCESSINGCONTOURS_H
