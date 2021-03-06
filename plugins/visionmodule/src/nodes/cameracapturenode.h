#ifndef CAMERACAPTURE_H
#define CAMERACAPTURE_H

#include "capturenode.h"



class CameraCaptureNode : public CaptureNode
{
    Q_OBJECT

    Q_PROPERTY(bool cameraOpened READ cameraOpened WRITE setCameraOpened NOTIFY cameraOpenedChanged)

    Q_PROPERTY(bool connectOnInit READ connectOnInit WRITE setConnectOnInit NOTIFY connectOnInitChanged USER("serialize"))

    Q_PROPERTY(bool continuousCapture READ continuousCapture WRITE setContinuousCapture NOTIFY continuousCaptureChanged USER("serialize"))


    Q_PROPERTY(bool updatingCamera READ updatingCamera WRITE setUpdatingCamera NOTIFY updatingCameraChanged)

    Q_PROPERTY(bool externalTrigger READ externalTrigger WRITE setExternalTrigger NOTIFY externalTriggerChanged USER("serialize"))




public:
    CameraCaptureNode();
    ~CameraCaptureNode() override;


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

    bool externalTrigger() const
    {
        return m_externalTrigger;
    }
    bool connectOnInit() const
    {
        return m_connectOnInit;
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

    virtual void setExternalTrigger(bool externalTrigger)
    {
        if (m_externalTrigger == externalTrigger)
            return;

        m_externalTrigger = externalTrigger;
        emit externalTriggerChanged(m_externalTrigger);
    }
    void setConnectOnInit(bool connectOnInit)
    {
        if (m_connectOnInit == connectOnInit)
            return;

        m_connectOnInit = connectOnInit;
        emit connectOnInitChanged(m_connectOnInit);
    }


signals:
    void continuousCaptureChanged(bool continuousCapture);

    void cameraOpenedChanged(bool cameraOpened);

    void updatingCameraChanged(bool updatingCamera);

    void externalTriggerChanged(bool externalTrigger);

    void connectOnInitChanged(bool connectOnInit);

protected:
    bool m_cameraOpened=false;
    bool m_continuousCapture=false;
    bool m_updatingCamera=false;
    bool m_externalTrigger=false;
      bool m_connectOnInit=false;

    virtual void closeCamera();
private:


};

#endif // CAMERACAPTURE_H
