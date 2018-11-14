#ifndef WEBCAMCAPTURENODE_H
#define WEBCAMCAPTURENODE_H

#include "cameracapturenode.h"

#include <opencv2/videoio.hpp>


using namespace cv;



class WebCamCaptureNode : public CameraCaptureNode
{
    Q_OBJECT
    Q_PROPERTY(int totalCameras READ totalCameras NOTIFY totalCamerasChanged)
    Q_PROPERTY(int cameraID READ cameraID WRITE setCameraID NOTIFY cameraIDChanged USER("serialize"))

public:
    WebCamCaptureNode();
    ~WebCamCaptureNode() override;




    static  QQmlComponent*  delegate(QQmlEngine& engine) noexcept;


    int countCameras();

    int totalCameras() const
    {
        return m_totalCameras;
    }

    int cameraID() const
    {
        return m_cameraID;
    }

public slots:
    void setTotalCameras(int totalCameras)
    {
        if (m_totalCameras == totalCameras)
            return;

        m_totalCameras = totalCameras;
        emit totalCamerasChanged(m_totalCameras);
    }

signals:
    void totalCamerasChanged(int totalCameras);

    void cameraIDChanged(int cameraID);

protected:
    virtual void DeSerialize(QJsonObject &json) override;

    // CaptureNode interface
public slots:



    void setCameraID(int cameraID)
    {
        if (m_cameraID == cameraID)
            return;

        m_cameraID = cameraID;
        emit cameraIDChanged(m_cameraID);
    }

private:

    int m_totalCameras=0;
    VideoCapture *m_selectedCamera=nullptr;
    // JsonSerializable interface
    int m_cameraID=-1;



    // CameraCaptureNode interface
protected:

    // CameraCaptureNode interface
protected:
    virtual void closeCamera() override;
};

#endif // WEBCAMCAPTURENODE_H
