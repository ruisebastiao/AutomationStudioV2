#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include <QQmlEngine>
#include <QQmlContext>
#include <jsonserializable.h>

#include "opencv2/imgproc.hpp"

#include "processing.h"



class PreProcessing : public Processing
{
    Q_OBJECT


    Q_PROPERTY(ProcessingType type READ getType CONSTANT FINAL USER("serialize"))


    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged USER("serialize"))

    Q_PROPERTY(bool showResult READ showResult WRITE setShowResult NOTIFY showResultChanged)


private:

    QJsonObject m_storedSettings;

    bool m_expanded=false;

    int m_processinOrder=0;

    bool m_enabled=true;

    bool m_showResult=true;

public:
    explicit PreProcessing(QQuickItem *parent = nullptr);
    enum class ProcessingType {
        PreProcNone,
        PreProcThreshold,
        PreProcGaussian

    };
    Q_ENUM(ProcessingType)

    ProcessingType getType() const
    {
        return m_type;
    }


    virtual void applyPreProcessing(cv::Mat &in,cv::Mat &out);
protected:
    cv::Mat m_processedMat;
signals:

    void storedSettingsChanged(QJsonObject storedSettings);

    void expandedChanged(bool expanded);

    void itemValueChanged();

    void processinOrderChanged(int processinOrder);

    void enabledChanged(bool enabled);

    void showResultChanged(bool showResult);

public slots:

    // JsonSerializable interface


    void setStoredSettings(QJsonObject storedSettings)
    {
        if (m_storedSettings == storedSettings)
            return;

        m_storedSettings = storedSettings;

        DeSerialize(m_storedSettings);
        emit storedSettingsChanged(m_storedSettings);
    }

    void setExpanded(bool expanded)
    {
        if (m_expanded == expanded)
            return;

        m_expanded = expanded;
        emit expandedChanged(m_expanded);
    }

    void setProcessinOrder(int processinOrder)
    {
        if (m_processinOrder == processinOrder)
            return;

        m_processinOrder = processinOrder;
        emit processinOrderChanged(m_processinOrder);
    }

    void setEnabled(bool enabled)
    {
        if (m_enabled == enabled)
            return;

        m_enabled = enabled;
        emit enabledChanged(m_enabled);
    }

    void setShowResult(bool showResult)
    {
        if (m_showResult == showResult)
            return;

        m_showResult = showResult;
        emit showResultChanged(m_showResult);
    }

protected:

    ProcessingType m_type=ProcessingType::PreProcNone;

public:
    void Serialize(QJsonObject &json);
    void DeSerialize(QJsonObject &json);
    QJsonObject storedSettings() const
    {
        return m_storedSettings;
    }
    bool expanded() const
    {
        return m_expanded;
    }
    int processinOrder() const
    {
        return m_processinOrder;
    }
    bool enabled() const
    {
        return m_enabled;
    }
    cv::Mat getProcessedMat() const;
    bool showResult() const
    {
        return m_showResult;
    }
};

#endif // PREPROCESSING_H
