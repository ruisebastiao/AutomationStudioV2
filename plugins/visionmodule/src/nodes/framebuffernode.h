#ifndef FRAMEBUFFERNODE_H
#define FRAMEBUFFERNODE_H

#include <QObject>
#include <flownode.h>

#include <cv/qmat.h>

class FrameBufferNode : public FlowNode
{
    Q_OBJECT

    Q_PROPERTY(QMat* frameSource READ frameSource WRITE setFrameSource NOTIFY frameSourceChanged )
    Q_PROPERTY(FlowNodePort* frameSourcePort READ frameSourcePort WRITE setFrameSourcePort NOTIFY frameSourcePortChanged USER("serialize"))


    Q_PROPERTY(int numBuffers READ numBuffers WRITE setNumBuffers NOTIFY numBuffersChanged)
    Q_PROPERTY(FlowNodePort* numBuffersPort READ numBuffersPort WRITE setNumBuffersPort NOTIFY numBuffersPortChanged USER("serialize"))


    Q_PROPERTY(QMat* frameSink READ frameSink WRITE setFrameSink NOTIFY frameSinkChanged)
    Q_PROPERTY(FlowNodePort* frameSinkPort READ frameSinkPort WRITE setFrameSinkPort NOTIFY frameSinkPortChanged USER("serialize"))

    Q_PROPERTY(bool frameStored READ frameStored WRITE setFrameStored NOTIFY frameStoredChanged)
    Q_PROPERTY(FlowNodePort* frameStoredPort READ frameStoredPort WRITE setFrameStoredPort NOTIFY frameStoredChanged USER("serialize"))


private:
    int m_numBuffers=1;

    FlowNodePort* m_numBuffersPort=nullptr;

    QMat* m_frameSink=nullptr;

    FlowNodePort* m_frameSinkPort=nullptr;
    QMat* m_frameSource=nullptr;

    FlowNodePort* m_frameSourcePort=nullptr;

    bool m_frameStored=false;

    FlowNodePort* m_frameStoredPort=nullptr;

public:
    FrameBufferNode();

    static  QQmlComponent*      delegate(QQmlEngine& engine) noexcept;

    // JsonSerializable interface
public:
    void Serialize(QJsonObject &json) override;
    void DeSerialize(QJsonObject &json) override;
    int numBuffers() const
    {
        return m_numBuffers;
    }
    FlowNodePort* numBuffersPort() const
    {
        return m_numBuffersPort;
    }

    QMat* frameSink() const
    {
        return m_frameSink;
    }

    FlowNodePort* frameSinkPort() const
    {
        return m_frameSinkPort;
    }

    QMat* frameSource() const
    {
        return m_frameSource;
    }

    FlowNodePort* frameSourcePort() const
    {
        return m_frameSourcePort;
    }

    bool frameStored() const
    {
        return m_frameStored;
    }

    FlowNodePort* frameStoredPort() const
    {
        return m_frameStoredPort;
    }

public slots:
    void setNumBuffers(int numBuffers)
    {
        if (m_numBuffers == numBuffers)
            return;

        m_numBuffers = numBuffers;
        emit numBuffersChanged(m_numBuffers);
    }
    void setNumBuffersPort(FlowNodePort* numBuffersPort)
    {
        if (m_numBuffersPort == numBuffersPort)
            return;

        m_numBuffersPort = numBuffersPort;
        emit numBuffersPortChanged(m_numBuffersPort);
    }

    void setFrameSink(QMat* frameSink)
    {
        if (m_frameSink == frameSink)
            return;

        m_frameSink = frameSink;
        emit frameSinkChanged(m_frameSink);
    }

    void setFrameSinkPort(FlowNodePort* frameSinkPort)
    {
        if (m_frameSinkPort == frameSinkPort)
            return;

        m_frameSinkPort = frameSinkPort;
        emit frameSinkPortChanged(m_frameSinkPort);
    }

    void setFrameSource(QMat* frameSource)
    {
        if (m_frameSource == frameSource)
            return;

        m_frameSource = frameSource;
        emit frameSourceChanged(m_frameSource);
    }

    void setFrameSourcePort(FlowNodePort* frameSourcePort)
    {
        if (m_frameSourcePort == frameSourcePort)
            return;

        m_frameSourcePort = frameSourcePort;
        emit frameSourcePortChanged(m_frameSourcePort);
    }

    void setFrameStored(bool frameStored)
    {
        if (m_frameStored == frameStored)
            return;

        m_frameStored = frameStored;
        emit frameStoredChanged(m_frameStored);
    }

    void setFrameStoredPort(FlowNodePort* frameStoredPort)
    {
        if (m_frameStoredPort == frameStoredPort)
            return;

        m_frameStoredPort = frameStoredPort;
        emit frameStoredChanged(m_frameStoredPort);
    }

signals:
    void numBuffersChanged(int numBuffers);
    void numBuffersPortChanged(FlowNodePort* numBuffersPort);
    void frameSinkChanged(QMat* frameSink);
    void frameSinkPortChanged(FlowNodePort* frameSinkPort);
    void frameSourceChanged(QMat* frameSource);
    void frameSourcePortChanged(FlowNodePort* frameSourcePort);
    void frameStoredChanged(bool frameStored);
};

#endif // FRAMEBUFFERNODE_H
