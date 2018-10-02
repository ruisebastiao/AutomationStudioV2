#ifndef CAMERACAPTURE_H
#define CAMERACAPTURE_H

#include "capturenode.h"



class CameraCaptureNode : public CaptureNode
{
    Q_OBJECT

    Q_PROPERTY(bool cameraOpened READ cameraOpened WRITE setCameraOpened NOTIFY cameraOpenedChanged)


    Q_PROPERTY(bool continuousCapture READ continuousCapture WRITE setContinuousCapture NOTIFY continuousCaptureChanged)


public:
    CameraCaptureNode();


    bool continuousCapture() const
    {
        return m_continuousCapture;
    }

    bool cameraOpened() const
    {
        return m_cameraOpened;
    }

public slots:
    virtual void setContinuousCapture(bool continuousCapture);

    virtual void setCameraOpened(bool cameraOpened);

signals:
    void continuousCaptureChanged(bool continuousCapture);

    void cameraOpenedChanged(bool cameraOpened);

protected:
    bool m_cameraOpened=false;
    bool m_continuousCapture=false;


    virtual void closeCamera();

};

#endif // CAMERACAPTURE_H
