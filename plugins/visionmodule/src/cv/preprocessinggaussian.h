#ifndef PREPROCESSINGGAUSSIAN_H
#define PREPROCESSINGGAUSSIAN_H

#include "preprocessing.h"




class PreProcessingGaussian : public PreProcessing
{
    Q_OBJECT

    Q_PROPERTY(int kernelSize READ kernelSize  WRITE setKernelSize NOTIFY kernelSizeChanged USER("serialize"))



private:

    int m_kernelSize=5;

public:
    PreProcessingGaussian();

    // JsonSerializable interface
protected:
//    void Serialize(QJsonObject &json) override;
//    void DeSerialize(QJsonObject &json) override;

    // PreProcessing interface
public:
    void applyPreProcessing(cv::Mat &in, cv::Mat &out) override;

    int kernelSize() const
    {
        return m_kernelSize;
    }

public slots:

    void setKernelSize(int kernelSize)
    {
        if (m_kernelSize == kernelSize)
            return;

        m_kernelSize = kernelSize;
        emit kernelSizeChanged(m_kernelSize);
        emit itemValueChanged();

    }

signals:

    void kernelSizeChanged(int kernelSize);
};

#endif // PREPROCESSINGGAUSSIAN_H
