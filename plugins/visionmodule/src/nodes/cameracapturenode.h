#ifndef CAMERACAPTURE_H
#define CAMERACAPTURE_H

#include "capturenode.h"



class CameraCaptureNode : public CaptureNode
{
    Q_OBJECT

    Q_PROPERTY(bool cameraOpened READ cameraOpened WRITE setCameraOpened NOTIFY cameraOpenedChanged)


    Q_PROPERTY(bool continuousCapture READ continuousCapture WRITE setContinuousCapture NOTIFY continuousCaptureChanged)


    Q_PROPERTY(bool updatingCamera READ updatingCamera WRITE setUpdatingCamera NOTIFY updatingCameraChanged)




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

    bool updatingCamera() const
    {
        return m_updatingCamera;
    }

public slots:
    virtual void setContinuousCapture(bool continuousCapture);

    virtual void setCameraOpened(bool cameraOpened);

    void setUpdatingCamera(bool updatingCamera)
    {
        if (m_updatingCamera == updatingCamera)
            return;

        m_updatingCamera = updatingCamera;
        emit updatingCameraChanged(m_updatingCamera);
    }

signals:
    void continuousCaptureChanged(bool continuousCapture);

    void cameraOpenedChanged(bool cameraOpened);

    void updatingCameraChanged(bool updatingCamera);

protected:
    bool m_cameraOpened=false;
    bool m_continuousCapture=false;
    bool m_updatingCamera=false;

    virtual void closeCamera();
private:

};

#endif // CAMERACAPTURE_H
