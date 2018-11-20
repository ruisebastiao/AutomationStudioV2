#ifndef PROCESSINGMASKNODE_H
#define PROCESSINGMASKNODE_H

#include "processingnode.h"



class ProcessingMaskNode : public ProcessingNode
{
    Q_OBJECT

    Q_PROPERTY(MaskType maskType READ maskType WRITE setMaskType NOTIFY maskTypeChanged USER("serialize"))



public:
    ProcessingMaskNode();

    enum MaskType {
        MaskCircleRadius=0
    };
    Q_ENUM(MaskType)

    static  QQmlComponent *delegate(QQmlEngine &engine)noexcept;

    // JsonSerializable interface
private:
    MaskType m_maskType=MaskCircleRadius;

public:
    void DeSerialize(QJsonObject &json) override;

    // ProcessingNode interface
    MaskType maskType() const
    {
        return m_maskType;
    }

public slots:
    void setInput(QMat *input) override;

    void setMaskType(MaskType maskType)
    {
        if (m_maskType == maskType)
            return;

        m_maskType = maskType;
        emit maskTypeChanged(m_maskType);
    }

signals:
    void maskTypeChanged(MaskType maskType);

protected:
    void doProcess() override;
};

#endif // PROCESSINGMASKNODE_H
