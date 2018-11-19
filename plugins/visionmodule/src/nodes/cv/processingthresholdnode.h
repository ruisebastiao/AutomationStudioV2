#ifndef PROCESSINGTHRESHOLDNODE_H
#define PROCESSINGTHRESHOLDNODE_H

#include "processingnode.h"

class ProcessingThresholdNode : public ProcessingNode
{
    Q_OBJECT

    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged USER("serialize"))

    Q_PROPERTY(int adaptativeBlockSize READ adaptativeBlockSize WRITE setAdaptativeBlockSize NOTIFY adaptativeBlockSizeChanged  USER("serialize"))

    Q_PROPERTY(int adaptativeC READ adaptativeC WRITE setAdaptativeC NOTIFY adaptativeCChanged USER("serialize"))

    Q_PROPERTY(ThresholdType thresholdType READ thresholdType WRITE setThresholdType NOTIFY thresholdTypeChanged USER("serialize"))


public:

    enum ThresholdType {

        Simple=0,
        AdaptativeGaussian,
        AdaptativeMean

    };
    Q_ENUM(ThresholdType)

    ProcessingThresholdNode();
    
    // ProcessingNode interface
    int value() const
    {
        return m_value;
    }

    int adaptativeBlockSize() const
    {
        return m_adaptativeBlockSize;
    }

    int adaptativeC() const
    {
        return m_adaptativeC;
    }

    ThresholdType thresholdType() const
    {
        return m_thresholdType;
    }

    static  QQmlComponent*      delegate(QQmlEngine& engine) noexcept;


public slots:
    virtual void setInput(QMat *input) override;
    
    void setValue(int value)
    {
        if (m_value == value)
            return;

        m_value = value;
        emit valueChanged(m_value);

        if(configsLoaded()){
            setProcess(true);
        }
    }

    void setAdaptativeBlockSize(int adaptativeBlockSize)
    {
        if (m_adaptativeBlockSize == adaptativeBlockSize)
            return;

        m_adaptativeBlockSize = adaptativeBlockSize;
        emit adaptativeBlockSizeChanged(m_adaptativeBlockSize);

        if(configsLoaded()){
            setProcess(true);
        }
    }

    void setAdaptativeC(int adaptativeC)
    {
        if (m_adaptativeC == adaptativeC)
            return;

        m_adaptativeC = adaptativeC;
        emit adaptativeCChanged(m_adaptativeC);

        if(configsLoaded()){
            setProcess(true);
        }
    }

    void setThresholdType(ThresholdType thresholdType)
    {
        if (m_thresholdType == thresholdType)
            return;

        m_thresholdType = thresholdType;
        emit thresholdTypeChanged(m_thresholdType);

        if(configsLoaded()){
            setProcess(true);
        }
    }

signals:
    void valueChanged(int value);

    void adaptativeBlockSizeChanged(int adaptativeBlockSize);

    void adaptativeCChanged(int adaptativeC);

    void thresholdTypeChanged(ThresholdType thresholdType);

private:

    int m_value=125;

    int m_adaptativeBlockSize=41;

    int m_adaptativeC=2;

    ThresholdType m_thresholdType=Simple;

protected:
    virtual void doProcess() override;
};

#endif // PROCESSINGTHRESHOLDNODE_H
