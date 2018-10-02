#ifndef IDSCAPTURE_H
#define IDSCAPTURE_H

#include "cameracapturenode.h"
#include "idscameralistmodel.h"
#include <uEye.h>
#include <QtConcurrent>
#include <QObject>





class IDSCaptureNode : public CameraCaptureNode
{
    Q_OBJECT


    Q_PROPERTY(IDSCameraListModel* availableCameras READ availableCameras WRITE setAvailableCameras NOTIFY availableCamerasChanged)

    Q_PROPERTY(int cameraID READ cameraID WRITE setCameraID NOTIFY cameraIDChanged USER("serialize"))

    Q_PROPERTY(IDSCamera* selectedCamera READ selectedCamera WRITE setSelectedCamera NOTIFY selectedCameraChanged)

    Q_PROPERTY(bool cameraAvailable READ cameraAvailable NOTIFY cameraAvailableChanged)

    Q_PROPERTY(bool softwareTrigger READ softwareTrigger WRITE setSoftwareTrigger NOTIFY softwareTriggerChanged)





public:
    IDSCaptureNode();
    ~IDSCaptureNode() override;


    static  QQmlComponent*      delegate(QQmlEngine& engine) noexcept;



    bool cameraAvailable() const
    {
        return m_IscameraAvailable;
    }


    IDSCameraListModel* availableCameras() const
    {
        return m_availableCameras;
    }

    int cameraID() const
    {
        return m_cameraID;
    }




    bool softwareTrigger() const
    {
        return m_softwareTrigger;
    }


    void DeSerialize(QJsonObject &json) override;

public slots:


    void setCamera(bool open);



    void setSelectedCamera(IDSCamera* selectedCamera)
    {
        if (m_selectedCamera == selectedCamera)
            return;

        m_selectedCamera = selectedCamera;

        setCameraAvailable(m_selectedCamera!=nullptr);

        if(m_selectedCamera){

        }

        emit selectedCameraChanged(m_selectedCamera);
    }

    IDSCamera* selectedCamera() const
    {
        return m_selectedCamera;
    }
    void setAvailableCameras(IDSCameraListModel* availableCameras)
    {
        if (m_availableCameras == availableCameras)
            return;

        m_availableCameras = availableCameras;
        emit availableCamerasChanged(m_availableCameras);
    }

    void setCameraID(int cameraID)
    {
        if (m_cameraID == cameraID)
            return;

        m_cameraID = cameraID;
        emit cameraIDChanged(m_cameraID);
    }



    void setContinuousCapture(bool continuousCapture) override;

    void setSoftwareTrigger(bool softwareTrigger)
    {
        if (m_softwareTrigger == softwareTrigger)
            return;

        m_softwareTrigger = softwareTrigger;
        emit softwareTriggerChanged(m_softwareTrigger);
    }


private slots:

    void onCheckCameras();

signals:
    void cameraSerialNumberChanged(QString cameraSerialNumber);


    void cameraAvailableChanged(bool cameraAvailable);




    void cameraIDChanged(int cameraID);

    void selectedCameraChanged(IDSCamera* selectedCamera);

    void availableCamerasChanged(IDSCameraListModel* availableCameras);



    void continuousCaptureChanged(bool continuousCapture);

    void softwareTriggerChanged(bool softwareTrigger);


private:

    void setCameraAvailable(bool cameraAvailable)
    {
        if (m_IscameraAvailable == cameraAvailable)
            return;

        m_IscameraAvailable = cameraAvailable;
        if(m_IscameraAvailable){
            LOG_INFO("Camera:"+QString::number(m_cameraID)+" Available");
        }
        else {
            LOG_INFO("Camera:"+QString::number(m_cameraID)+" NOT Available");
            setCameraOpened(false);
        }


        emit cameraAvailableChanged(m_IscameraAvailable);
    }

    void getAvaibleCameras();


    // JsonSerializable interface
    bool m_IscameraAvailable;

    QTimer *m_checkCamerasTimer;
    QFutureWatcher<void> watcher;
    QWaitCondition frame_processed;
    QMutex mutex;
    bool terminateCapture=false;
    HANDLE m_hEvent;



    IDSCamera* m_selectedCamera=nullptr;

    HIDS m_camHandler=0;
    INT		m_nSizeX;			// width of image
    INT		m_nSizeY;			// height of image
    INT		m_nPosX;			// left offset of image
    INT		m_nPosY;			// right offset of image
    INT		m_lMemoryId;		// camera memory - buffer ID
    char*	m_pcImageMemory=nullptr;	// camera memory - pointer to buffer


    //   QImage m_lastframe;
    IDSCameraListModel* m_availableCameras = new IDSCameraListModel();
    int m_cameraID;

    void GetMaxImageSize(INT *pnSizeX, INT *pnSizeY);
    void GetFrames();


    bool m_softwareTrigger=false;


    // CaptureNode interface
public slots:
    void setNewFrame(bool newFrame) override;
protected:

    // CameraCaptureNode interface
protected:
    virtual void closeCamera() override;
};

#endif // IDSCAPTURE_H
