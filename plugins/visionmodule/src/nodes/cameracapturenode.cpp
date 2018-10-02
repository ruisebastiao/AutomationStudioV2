#include "cameracapturenode.h"

CameraCaptureNode::CameraCaptureNode()
{

}

void CameraCaptureNode::setContinuousCapture(bool continuousCapture)

{
    if (m_continuousCapture == continuousCapture)
        return;

    m_continuousCapture = continuousCapture;
    emit continuousCaptureChanged(m_continuousCapture);
}

void CameraCaptureNode::setCameraOpened(bool cameraOpened)

{
    if (m_cameraOpened == cameraOpened)
        return;

    m_cameraOpened = cameraOpened;
    emit cameraOpenedChanged(m_cameraOpened);
}


void CameraCaptureNode::closeCamera()
{

}
