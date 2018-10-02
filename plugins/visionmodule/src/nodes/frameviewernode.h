#ifndef FRAMEVIEWERNODE_H
#define FRAMEVIEWERNODE_H

#include "flownode.h"

#include <src/cv/qmat.h>



class FrameViewerNode : public FlowNode
{
    Q_OBJECT

    Q_PROPERTY(QMat* frameSource READ frameSource WRITE setFrameSource NOTIFY frameSourceChanged)

    Q_PROPERTY(bool processFrame READ processFrame WRITE setProcessFrame NOTIFY processFrameChanged)


    Q_PROPERTY(bool frameProcessed READ frameProcessed WRITE setFrameProcessed NOTIFY frameProcessedChanged)

public:
    FrameViewerNode();

    static  QQmlComponent*      delegate(QQmlEngine& engine);


    bool frameProcessed() const
    {
        return m_frameProcessed;
    }


    QMat* frameSource() const
    {
        return m_frameSource;
    }

    bool processFrame() const
    {
        return m_processFrame;
    }

public slots:

    void setFrameProcessed(bool frameProcessed)
    {


        m_frameProcessed = frameProcessed;
        emit frameProcessedChanged(m_frameProcessed);
        m_frameProcessed=false;
    }





    void setFrameSource(QMat* frameSource)
    {

        m_frameSource = frameSource;
        emit frameSourceChanged(m_frameSource);
    }

    void setProcessFrame(bool processFrame)
    {


        m_processFrame = processFrame;
        emit processFrameChanged(m_processFrame);
    }

signals:

    void frameProcessedChanged(bool frameProcessed);


    void frameSourceChanged(QMat* frameSource);

    void processFrameChanged(bool processFrame);

private:

    bool m_frameProcessed=false;



    QMat* m_frameSource=0;
    bool m_processFrame=false;
};

#endif // FRAMEVIEWERNODE_H
