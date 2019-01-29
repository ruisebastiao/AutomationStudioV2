#ifndef IDSCAPTURE_H
#define IDSCAPTURE_H

#include "cameracapturenode.h"
#include "idscameralistmodel.h"
#include <uEye.h>
#include <QtConcurrent>
#include <QObject>



#define MAX_SEQ_BUFFERS 30


class IDSCaptureNode : public CameraCaptureNode
{
    Q_OBJECT


    Q_PROPERTY(IDSCameraListModel* availableCameras READ availableCameras WRITE setAvailableCameras NOTIFY availableCamerasChanged)

    Q_PROPERTY(int cameraID READ cameraID WRITE setCameraID NOTIFY cameraIDChanged USER("serialize"))

    Q_PROPERTY(QString cameraParametersPath READ cameraParametersPath WRITE setCameraParametersPath NOTIFY cameraParametersPathChanged  USER("serialize"))

    Q_PROPERTY(bool useCameraParameters READ useCameraParameters WRITE setUseCameraParameters NOTIFY useCameraParametersChanged  USER("serialize"))



    Q_PROPERTY(IDSCamera* selectedCamera READ selectedCamera WRITE setSelectedCamera NOTIFY selectedCameraChanged)

    Q_PROPERTY(bool cameraAvailable READ cameraAvailable NOTIFY cameraAvailableChanged)

    Q_PROPERTY(int numBuffers READ numBuffers WRITE setNumBuffers NOTIFY numBuffersChanged  USER("serialize"))






public:
    IDSCaptureNode();
    ~IDSCaptureNode() override;


    static  QQmlComponent*      delegate(QQmlEngine& engine) noexcept;


    //Q_INVOKABLE void updateContinuousCapture(bool continuous);

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




    void DeSerialize(QJsonObject &json) override;

    void updateExternalTrigger(bool value);
    Q_INVOKABLE void updateContinuousCapture(bool value);

    Q_INVOKABLE void snapShot();

    int numBuffers() const
    {
        return m_numBuffers;
    }

    bool useCameraParameters() const
    {
        return m_useCameraParameters;
    }

    QString cameraParametersPath() const
    {
        return m_cameraParametersPath;
    }

public slots:


    void setCamera(bool open);



    void setSelectedCamera(IDSCamera* selectedCamera)
    {
        if (m_selectedCamera == selectedCamera)
            return;

        m_selectedCamera = selectedCamera;

        setCameraAvailable(m_selectedCamera!=nullptr);

        if(m_selectedCamera){
            setCameraID(m_selectedCamera->camID());
        }
        else{
            setCameraID(-1);
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


    void numBuffersChanged(int numBuffers);

    void useCameraParametersChanged(bool useCameraParameters);

    void cameraParametersPathChanged(QString cameraParametersPath);

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
    HANDLE m_hEvent=nullptr;



    IDSCamera* m_selectedCamera=nullptr;

    HIDS m_camHandler=0;
//    INT		m_nSizeX=0;			// width of image
//    INT		m_nSizeY=0;			// height of image
    INT		m_nPosX=0;			// left offset of image
    INT		m_nPosY=0;			// right offset of image
    //    INT		m_lMemoryId;		// camera memory - buffer ID
    //    char*	m_pcImageMemory=nullptr;	// camera memory - pointer to buffer

    INT		m_lSeqMemId[MAX_SEQ_BUFFERS];	// camera memory - buffer ID
    char*	m_pcSeqImgMem[MAX_SEQ_BUFFERS];	// camera memory - pointer to buffer
    int		m_nSeqNumId[MAX_SEQ_BUFFERS];	// varibale to hold the number of the sequence buffer Id

    int m_dwSingleBufferSize;
    int m_nBitsPerPixel=8; // mono8

    //   QImage m_lastframe;
    IDSCameraListModel* m_availableCameras = new IDSCameraListModel();
    int m_cameraID=-1;

    void GetMaxImageSize(INT *pnSizeX, INT *pnSizeY);
    void GetFrames();


    int m_frameBufferCount=0;
    // CaptureNode interface
    int m_numBuffers=1;

    int m_isContinuousCapture=false;

    bool m_useCameraParameters=true;

    QString m_cameraParametersPath="";

public slots:
    void setNewFrame(QVariant newFrame) override;
protected:

    // CameraCaptureNode interface
protected:
    virtual void closeCamera() override;

    // CameraCaptureNode interface
public slots:
    void setExternalTrigger(bool externalTrigger) override;
    void setNumBuffers(int numBuffers)
    {
        if (m_numBuffers == numBuffers)
            return;

        m_numBuffers = numBuffers;
        emit numBuffersChanged(m_numBuffers);
    }
    void setUseCameraParameters(bool useCameraParameters)
    {
        if (m_useCameraParameters == useCameraParameters)
            return;


        m_useCameraParameters = useCameraParameters;
        emit useCameraParametersChanged(m_useCameraParameters);
    }
    void setCameraParametersPath(QString cameraParametersPath)
    {
        if (m_cameraParametersPath == cameraParametersPath)
            return;



        QUrl fileurl(cameraParametersPath);

        QString fileloc=cameraParametersPath;
        if(fileurl.isLocalFile()){
            fileloc=fileurl.toLocalFile();
        }

      //     m_cameraParametersPath=cameraParametersPath;


        QDir basedir=QCoreApplication::applicationDirPath();


        m_cameraParametersPath=basedir.relativeFilePath(fileloc);
        emit cameraParametersPathChanged(m_cameraParametersPath);
    }
};

#endif // IDSCAPTURE_H
