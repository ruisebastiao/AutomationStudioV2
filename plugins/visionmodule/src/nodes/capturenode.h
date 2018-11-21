#ifndef CAPTURENODE_H
#define CAPTURENODE_H

#include "flownode.h"
#include "cv/qmat.h"




class CaptureNode : public FlowNode
{
    Q_OBJECT

    Q_PROPERTY(bool newFrame READ newFrame WRITE setNewFrame NOTIFY newFrameChanged REVISION 30)


    Q_PROPERTY(bool frameCaptured READ frameCaptured WRITE setFrameCaptured NOTIFY frameCapturedChanged REVISION 31)


    Q_PROPERTY(QMat* frameSink READ frameSink WRITE setFrameSink NOTIFY frameSinkChanged REVISION 31)


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

    void sizeXChanged(int sizeX);

    void sizeYChanged(int sizeY);

private:
    bool m_newFrame=false;

    bool m_frameCaptured=false;


    int m_sizeX=0;

    int m_sizeY=0;

protected:
    QMat* m_frameSink=nullptr;
    virtual void DeSerialize(QJsonObject &json) override;

    // FlowNode interface
public:
    
};

#endif // CAPTURENODE_H
