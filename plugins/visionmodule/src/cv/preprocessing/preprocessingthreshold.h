#ifndef PREPROCESSINGTHRESHOLD_H
#define PREPROCESSINGTHRESHOLD_H

#include "preprocessing.h"

#include <QObject>

class PreProcessingThreshold : public PreProcessing
{
    Q_OBJECT


    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged USER("serialize"))

    Q_PROPERTY(int adaptativeBlockSize READ adaptativeBlockSize WRITE setAdaptativeBlockSize NOTIFY adaptativeBlockSizeChanged  USER("serialize"))


    Q_PROPERTY(ThresholdType thresholdType READ thresholdType WRITE setThresholdType NOTIFY thresholdTypeChanged USER("serialize"))



public:
    PreProcessingThreshold();

    enum ThresholdType {

        Simple=0,
        Adaptative

    };
    Q_ENUM(ThresholdType)

    int value() const
    {
        return m_value;
    }

    void apply(cv::Mat &input, cv::Mat &preprocessed,cv::Mat &original) override;
    ThresholdType thresholdType() const
    {
        return m_thresholdType;
    }

    int adaptativeBlockSize() const
    {
        return m_adaptativeBlockSize;
    }

public slots:
    void setValue(int value)
    {
        if (m_value == value)
            return;


        m_value = value;
        emit valueChanged(m_value);
        emit preProcessorConditionChanged();
    }
    void setThresholdType(ThresholdType thresholdType)
    {
        if (m_thresholdType == thresholdType)
            return;

        m_thresholdType = thresholdType;
        emit thresholdTypeChanged(m_thresholdType);
        emit preProcessorConditionChanged();
    }

    void setAdaptativeBlockSize(int adaptativeBlockSize)
    {
        if (m_adaptativeBlockSize == adaptativeBlockSize)
            return;

        m_adaptativeBlockSize = adaptativeBlockSize;
        emit adaptativeBlockSizeChanged(m_adaptativeBlockSize);
        emit preProcessorConditionChanged();
    }

signals:
    void valueChanged(int value);
    void thresholdTypeChanged(ThresholdType thresholdType);


    void adaptativeBlockSizeChanged(int adaptativeBlockSize);

private:

    int m_value=125;

    ThresholdType m_thresholdType=Simple;
    int m_adaptativeBlockSize=11;
};

#endif // PREPROCESSINGTHRESHOLD_H
