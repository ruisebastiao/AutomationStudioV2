#ifndef CAPTURENODE_H
#define CAPTURENODE_H

#include "flownode.h"
#include "cv/qmat.h"




class CaptureNode : public FlowNode
{
    Q_OBJECT




    Q_PROPERTY(QVariant newFrame READ newFrame WRITE setNewFrame NOTIFY newFrameChanged REVISION 30)


    Q_PROPERTY(QVariant frameCaptured READ frameCaptured WRITE setFrameCaptured NOTIFY frameCapturedChanged REVISION 31)


    Q_PROPERTY(QVariant frameSink READ frameSink WRITE setFrameSink NOTIFY frameSinkChanged REVISION 31)


    Q_PROPERTY(int sizeX READ sizeX WRITE setSizeX NOTIFY sizeXChanged)
    Q_PROPERTY(int sizeY READ sizeY WRITE setSizeY NOTIFY sizeYChanged)


public:
    CaptureNode();

    QVariant newFrame() const
    {
        return m_newFrame;
    }


    QVariant frameCaptured() const
    {
        return m_frameCaptured;
    }


    QVariant frameSink() const
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
    virtual void setNewFrame(QVariant newFrame);

    virtual void setFrameCaptured(QVariant frameCaptured);



    virtual void setFrameSink(QVariant frameSink);


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

    void newFrameChanged(QVariant newFrame);


    void frameCapturedChanged(QVariant frameCaptured);


    void frameSinkChanged(QVariant frameSink);

    void sizeXChanged(int sizeX);

    void sizeYChanged(int sizeY);



private:
    QVariant m_newFrame=QVariant::fromValue(false);

    QVariant m_frameCaptured=QVariant::fromValue(false);


    int m_sizeX=0;

    int m_sizeY=0;



protected:
    QVariant m_frameSink=QVariant::fromValue(new QMat());
    virtual void DeSerialize(QJsonObject &json) override;



};

#endif // CAPTURENODE_H
