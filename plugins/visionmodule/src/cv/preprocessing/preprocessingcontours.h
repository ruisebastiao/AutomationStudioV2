#ifndef PREPROCESSINGCONTOURS_H
#define PREPROCESSINGCONTOURS_H

#include "preprocessing.h"



class PreProcessingContours:public PreProcessing
{
    Q_OBJECT

    Q_PROPERTY(int threshold READ threshold WRITE setThreshold NOTIFY thresholdChanged USER("serialize"))

    Q_PROPERTY(int totalContours READ totalContours WRITE setTotalContours NOTIFY totalContoursChanged)
    Q_PROPERTY(int totalFilteredContours READ totalFilteredContours WRITE setTotalFilteredContours NOTIFY totalFilteredContoursChanged)


    Q_PROPERTY(int minCountourLength READ minCountourLength WRITE setMinCountourLength NOTIFY minCountourLengthChanged USER("serialize"))
    Q_PROPERTY(int maxCountourLength READ maxCountourLength WRITE setMaxCountourLength NOTIFY maxCountourLengthChanged USER("serialize"))

    Q_PROPERTY(int minCountourHeight READ minCountourHeight WRITE setMinCountourHeight NOTIFY minCountourHeightChanged USER("serialize"))
    Q_PROPERTY(int maxCountourHeight READ maxCountourHeight WRITE setMaxCountourHeight NOTIFY maxCountourHeightChanged USER("serialize"))

    Q_PROPERTY(int minCountourWidth READ minCountourWidth WRITE setMinCountourWidth NOTIFY minCountourWidthChanged USER("serialize"))
    Q_PROPERTY(int maxCountourWidth READ maxCountourWidth WRITE setMaxCountourWidth NOTIFY maxCountourWidthChanged USER("serialize"))


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

    int minCountourLength() const
    {
        return m_minCountourLength;
    }

    int maxCountourLength() const
    {
        return m_maxCountourLength;
    }

    std::vector<std::vector<cv::Point>> filteredContours() const
    {
        return m_filteredContours;
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

    int maxCountourWidth() const
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
        if(loaded()){
         if(loaded()){
            emit preProcessorConditionChanged();
        }
        }
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
         if(loaded()){
            emit preProcessorConditionChanged();
        }
    }

    void setMinCountourLength(int minCountourLength)
    {
        if (m_minCountourLength== minCountourLength)
            return;

        m_minCountourLength = minCountourLength;
        emit minCountourLengthChanged(m_minCountourLength);
         if(loaded()){
            emit preProcessorConditionChanged();
        }
    }

    void setMaxCountourLength(int maxCountourLength)
    {
        if (m_maxCountourLength== maxCountourLength)
            return;

        m_maxCountourLength = maxCountourLength;
        emit maxCountourLengthChanged(m_maxCountourLength);
         if(loaded()){
            emit preProcessorConditionChanged();
        }
    }

    void setMinCountourHeight(int minCountourHeight)
    {

        if (m_minCountourHeight== minCountourHeight)
            return;

        m_minCountourHeight = minCountourHeight;
        emit minCountourHeightChanged(m_minCountourHeight);
         if(loaded()){
            emit preProcessorConditionChanged();
        }
    }

    void setMaxCountourHeight(int maxCountourHeight)
    {

        if (m_maxCountourHeight == maxCountourHeight)
            return;

        m_maxCountourHeight = maxCountourHeight;
        emit maxCountourHeightChanged(m_maxCountourHeight);
         if(loaded()){
            emit preProcessorConditionChanged();
        }
    }

    void setMinCountourWidth(int minCountourWidth)
    {

        if (m_minCountourWidth == minCountourWidth)
            return;

        m_minCountourWidth = minCountourWidth;
        emit minCountourWidthChanged(m_minCountourWidth);
         if(loaded()){
            emit preProcessorConditionChanged();
        }
    }

    void setMaxCountourWidth(int maxCountourWidth)
    {

        if (m_maxCountourWidth== maxCountourWidth)
            return;

        m_maxCountourWidth = maxCountourWidth;
        emit maxCountourWidthChanged(m_maxCountourWidth);
         if(loaded()){
            emit preProcessorConditionChanged();
        }
    }

signals:
    void thresholdChanged(int threshold);

    void totalContoursChanged(int totalContours);

    void totalFilteredContoursChanged(int totalFilteredContours);

    void minCountourLengthChanged(int minCountourLength);

    void maxCountourLengthChanged(int maxCountourLength);

    void filteredContoursChanged(std::vector<std::vector<cv::Point>> filteredContours);

    void minCountourHeightChanged(int minCountourHeight);

    void maxCountourHeightChanged(int maxCountourHeight);

    void minCountourWidthChanged(int minCountourWidth);

    void maxCountourWidthChanged(int maxCountourWidth);

private:
    int m_threshold=125;
    int m_totalContours=0;
    int m_totalFilteredContours=0;
    int m_minCountourLength=500;
    int m_maxCountourLength=1000;

    std::vector<std::vector<cv::Point>> m_filteredContours;
    int m_minCountourHeight=100;
    int m_maxCountourHeight=1000;
    int m_minCountourWidth=100;
    int m_maxCountourWidth=1000;
};

#endif // PREPROCESSINGCONTOURS_H
