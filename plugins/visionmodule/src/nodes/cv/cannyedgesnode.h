#ifndef CANNYEDGESNODE_H
#define CANNYEDGESNODE_H

#include "processingnode.h"



class CannyEdgesNode : public ProcessingNode
{
    Q_OBJECT

     Q_PROPERTY(int thresholdlow READ thresholdlow WRITE setThresholdlow NOTIFY thresholdlowChanged USER("serializable"))
     Q_PROPERTY(int thresholdhigh READ thresholdhigh WRITE setThresholdhigh NOTIFY thresholdhighChanged USER("serializable"))


public:
    CannyEdgesNode();

     static  QQmlComponent*      delegate(QQmlEngine& engine) noexcept;

     // ProcessingNode interface
     int thresholdlow() const
     {
         return m_thresholdlow;
     }

     int thresholdhigh() const
     {
         return m_thresholdhigh;
     }

public slots:
    void setInput(QMat *input) override;

    void setThresholdlow(int thresholdlow)
    {
        if (m_thresholdlow == thresholdlow)
            return;

        m_thresholdlow = thresholdlow;
        emit thresholdlowChanged(m_thresholdlow);
    }

    void setThresholdhigh(int thresholdhigh)
    {
        if (m_thresholdhigh == thresholdhigh)
            return;

        m_thresholdhigh = thresholdhigh;
        emit thresholdhighChanged(m_thresholdhigh);
    }

signals:
    void thresholdlowChanged(int thresholdlow);

    void thresholdhighChanged(int thresholdhigh);

protected:
    void doProcess() override;

private:

    int m_thresholdlow=100;

    int m_thresholdhigh=255;

};

#endif // CANNYEDGESNODE_H
