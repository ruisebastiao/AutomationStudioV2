#ifndef PREPROCESSINGTHRESHOLD_H
#define PREPROCESSINGTHRESHOLD_H



#include <QObject>

#include <cv/processing/processing.h>

class PreProcessingThreshold : public Processing
{
    Q_OBJECT


    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged USER("serialize"))

    Q_PROPERTY(int adaptativeBlockSize READ adaptativeBlockSize WRITE setAdaptativeBlockSize NOTIFY adaptativeBlockSizeChanged  USER("serialize"))

    Q_PROPERTY(int adaptativeC READ adaptativeC WRITE setAdaptativeC NOTIFY adaptativeCChanged USER("serialize"))

    Q_PROPERTY(ThresholdType thresholdType READ thresholdType WRITE setThresholdType NOTIFY thresholdTypeChanged USER("serialize"))



public:
    PreProcessingThreshold();

    enum ThresholdType {

        Simple=0,
        AdaptativeGaussian,
        AdaptativeMean

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

    int adaptativeC() const
    {
        return m_adaptativeC;
    }

public slots:
    void setValue(int value)
    {
        if (m_value == value)
            return;


        m_value = value;
        emit valueChanged(m_value);
        if(loaded()){
            emit processorConditionChanged();
        }
    }
    void setThresholdType(ThresholdType thresholdType)
    {
        if (m_thresholdType == thresholdType)
            return;

        m_thresholdType = thresholdType;
        emit thresholdTypeChanged(m_thresholdType);
        if(loaded()){
            emit processorConditionChanged();
        }
    }

    void setAdaptativeBlockSize(int adaptativeBlockSize)
    {
        if (m_adaptativeBlockSize == adaptativeBlockSize)
            return;

        m_adaptativeBlockSize = adaptativeBlockSize;
        emit adaptativeBlockSizeChanged(m_adaptativeBlockSize);
        if(loaded()){
            emit processorConditionChanged();
        }
    }

    void setAdaptativeC(int adaptativeC)
    {
        if (m_adaptativeC == adaptativeC)
            return;

        m_adaptativeC = adaptativeC;
        if(loaded()){
            emit processorConditionChanged();
        }
    }

signals:
    void valueChanged(int value);
    void thresholdTypeChanged(ThresholdType thresholdType);


    void adaptativeBlockSizeChanged(int adaptativeBlockSize);

    void adaptativeCChanged(int adaptativeC);

private:

    int m_value=125;

    ThresholdType m_thresholdType=Simple;
    int m_adaptativeBlockSize=11;
    int m_adaptativeC=2;
};

#endif // PREPROCESSINGTHRESHOLD_H
