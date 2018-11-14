#include "webcamcapturenode.h"

WebCamCaptureNode::WebCamCaptureNode()
{

}

WebCamCaptureNode::~WebCamCaptureNode()
{
    // VideoCapture
}

QQmlComponent *WebCamCaptureNode::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:/components/nodes/WebCamCaptureNode.qml"));
    return delegate.get();
}

int WebCamCaptureNode::countCameras()
{
   VideoCapture temp_camera;
   int maxTested = 10;
   for (int i = 0; i < maxTested; i++){
     cv::VideoCapture temp_camera(i);
     bool res = (!temp_camera.isOpened());
     temp_camera.release();
     if (res)
     {
       return i;
     }
   }
   return maxTested;
}

void WebCamCaptureNode::DeSerialize(QJsonObject &json)
{
    CaptureNode::DeSerialize(json);

    if(cameraID()>-1){
        m_selectedCamera= new VideoCapture(cameraID());

    }
    //    setCameraID()
}

void WebCamCaptureNode::closeCamera()
{

    if(m_selectedCamera){
        m_selectedCamera->release();
    }
}


