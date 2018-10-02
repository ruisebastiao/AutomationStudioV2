#ifndef PREPROCESSINGTHRESHOLD_H
#define PREPROCESSINGTHRESHOLD_H

#include "preprocessing.h"



class PreProcessingThreshold : public PreProcessing
{
    Q_OBJECT

    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged USER("serializable"))


public:
    PreProcessingThreshold();
    int value() const
    {
        return m_value;
    }

private:

    int m_value=128;


public slots:
    void setValue(int value)
    {
        if (m_value == value)
            return;

        m_value = value;
        emit valueChanged(m_value);

        emit itemValueChanged();

    }
signals:
    void valueChanged(int value);

    // PreProcessing interface
public:
    void applyPreProcessing(cv::Mat &in, cv::Mat &out) override;
};

#endif // PREPROCESSINGTHRESHOLD_H
