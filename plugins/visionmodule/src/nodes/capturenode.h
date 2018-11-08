#ifndef CAPTURENODE_H
#define CAPTURENODE_H

#include "flownode.h"
#include "cv/qmat.h"




class CaptureNode : public FlowNode
{
    Q_OBJECT

    Q_PROPERTY(bool newFrame READ newFrame WRITE setNewFrame NOTIFY newFrameChanged)
    Q_PROPERTY(FlowNodePort* newFramePort READ newFramePort WRITE setNewFramePort NOTIFY newFramePortChanged USER("serialize"))

    Q_PROPERTY(bool frameCaptured READ frameCaptured WRITE setFrameCaptured NOTIFY frameCapturedChanged)
    Q_PROPERTY(FlowNodePort* frameCapturedPort READ frameCapturedPort WRITE setFrameCapturedPort NOTIFY frameCapturedPortChanged USER("serialize"))

    Q_PROPERTY(QMat* frameSink READ frameSink WRITE setFrameSink NOTIFY frameSinkChanged)
    Q_PROPERTY(FlowNodePort* frameSinkPort READ frameSinkPort WRITE setFrameSinkPort NOTIFY frameSinkPortChanged USER("serialize"))

    Q_PROPERTY(int sizeX READ sizeX WRITE setSizeX NOTIFY sizeXChanged)
    Q_PROPERTY(int sizeY READ sizeY WRITE setSizeY NOTIFY sizeYChanged)


public:
    CaptureNode();

    bool newFrame() const
    {
        return m_newFrame;
    }


    bool frameCaptured() const
    {
        return m_frameCaptured;
    }


    QMat* frameSink() const
    {

        return m_frameSink;
    }

    FlowNodePort* frameCapturedPort() const
    {
        return m_frameCapturedPort;
    }

    FlowNodePort* frameSinkPort() const
    {
        return m_frameSinkPort;
    }

    FlowNodePort* newFramePort() const
    {
        return m_newFramePort;
    }

    int sizeX() const
    {
        return m_sizeX;
    }

    int sizeY() const
    {
        return m_sizeY;
    }

public slots:
    virtual void setNewFrame(bool newFrame);

    virtual void setFrameCaptured(bool frameCaptured);



    virtual void setFrameSink(QMat* frameSink);


    void setFrameCapturedPort(FlowNodePort* frameCapturedPort)
    {
        if (m_frameCapturedPort == frameCapturedPort)
            return;

        m_frameCapturedPort = frameCapturedPort;
        emit frameCapturedPortChanged(m_frameCapturedPort);
    }

    void setFrameSinkPort(FlowNodePort* frameSinkPort)
    {
        if (m_frameSinkPort == frameSinkPort)
            return;

        m_frameSinkPort = frameSinkPort;
        emit frameSinkPortChanged(m_frameSinkPort);
    }

    void setNewFramePort(FlowNodePort* newFramePort)
    {
        if (m_newFramePort == newFramePort)
            return;

        m_newFramePort = newFramePort;
        emit newFramePortChanged(m_newFramePort);
    }

    void setSizeX(int sizeX)
    {
        if (m_sizeX == sizeX)
            return;

        m_sizeX = sizeX;
        emit sizeXChanged(m_sizeX);
    }

    void setSizeY(int sizeY)
    {
        if (m_sizeY == sizeY)
            return;

        m_sizeY = sizeY;
        emit sizeYChanged(m_sizeY);
    }

signals:

    void newFrameChanged(bool newFrame);


    void frameCapturedChanged(bool frameCaptured);


    void frameSinkChanged(QMat* frameSink);

    void frameCapturedPortChanged(FlowNodePort* frameCapturedPort);

    void frameSinkPortChanged(FlowNodePort* frameSinkPort);

    void newFramePortChanged(FlowNodePort* newFramePort);

    void sizeXChanged(int sizeX);

    void sizeYChanged(int sizeY);

private:
    bool m_newFrame=false;

    bool m_frameCaptured=false;

    FlowNodePort* m_frameCapturedPort=nullptr;
    FlowNodePort* m_frameSinkPort=nullptr;

    // JsonSerializable interface
    FlowNodePort* m_newFramePort=nullptr;

    int m_sizeX=0;

    int m_sizeY=0;

protected:
    QMat* m_frameSink=nullptr;
    virtual void DeSerialize(QJsonObject &json) override;
};

#endif // CAPTURENODE_H
