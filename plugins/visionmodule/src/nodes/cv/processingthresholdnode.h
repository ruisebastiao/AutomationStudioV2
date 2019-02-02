#ifndef PROCESSINGTHRESHOLDNODE_H
#define PROCESSINGTHRESHOLDNODE_H

#include "processingnode.h"
#include "math.h"

class ProcessingThresholdNode : public ProcessingNode
{
    Q_OBJECT

    Q_PROPERTY(QVariant value READ value WRITE setValue NOTIFY valueChanged USER("serialize") REVISION 30)

    Q_PROPERTY(QVariant adaptativeBlockSize READ adaptativeBlockSize WRITE setAdaptativeBlockSize NOTIFY adaptativeBlockSizeChanged  USER("serialize") REVISION 30)

    Q_PROPERTY(QVariant adaptativeC READ adaptativeC WRITE setAdaptativeC NOTIFY adaptativeCChanged USER("serialize") REVISION 30)

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
    QVariant value() const
    {
        return m_value;
    }

    QVariant adaptativeBlockSize() const
    {
        return m_adaptativeBlockSize;
    }

    QVariant adaptativeC() const
    {
        return m_adaptativeC;
    }

    ThresholdType thresholdType() const
    {
        return m_thresholdType;
    }

    static  QQmlComponent*      delegate(QQmlEngine& engine) noexcept;


public slots:
    virtual void setInput(QVariant input) override;
    
    void setValue(QVariant value)
    {
        if (m_value == value)
            return;

        m_value = value;
        emit valueChanged(m_value);

        if(configsLoaded()){
            setProcess(true);
        }
    }

    void setAdaptativeBlockSize(QVariant adaptativeBlockSize)
    {
        if (m_adaptativeBlockSize == adaptativeBlockSize)
            return;

        m_adaptativeBlockSize = 2*floor( adaptativeBlockSize.value<int>()/2) + 1;
        emit adaptativeBlockSizeChanged(m_adaptativeBlockSize);

        if(configsLoaded()){
            setProcess(true);
        }
    }

    void setAdaptativeC(QVariant adaptativeC)
    {
        if (m_adaptativeC == adaptativeC)
            return;

        m_adaptativeC =2 * round(adaptativeC.value<int>()/ 2);
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
    void valueChanged(QVariant value);

    void adaptativeBlockSizeChanged(QVariant adaptativeBlockSize);

    void adaptativeCChanged(QVariant adaptativeC);

    void thresholdTypeChanged(ThresholdType thresholdType);

private:

    QVariant m_value=125;

    QVariant m_adaptativeBlockSize=41;

    QVariant m_adaptativeC=2;

    ThresholdType m_thresholdType=Simple;

protected:
    virtual void doProcess() override;
};

#endif // PROCESSINGTHRESHOLDNODE_H
