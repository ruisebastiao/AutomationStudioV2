#ifndef PREPROCESSINGCONTOURS_H
#define PREPROCESSINGCONTOURS_H

#include "preprocessing.h"



class PreProcessingContours:public PreProcessing
{
    Q_OBJECT

    Q_PROPERTY(int threshold READ threshold WRITE setThreshold NOTIFY thresholdChanged USER("serialize"))



public:
    PreProcessingContours();

    // PreProcessing interface
public:
    void apply(cv::Mat& input, cv::Mat& preprocessed) override;
    int threshold() const
    {
        return m_threshold;
    }
public slots:
    void setThreshold(int threshold)
    {
        if (m_threshold == threshold)
            return;

        m_threshold = threshold;
        emit thresholdChanged(m_threshold);
    }
signals:
    void thresholdChanged(int threshold);

private:
    int m_threshold=125;
};

#endif // PREPROCESSINGCONTOURS_H
