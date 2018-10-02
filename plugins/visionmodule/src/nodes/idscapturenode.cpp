#include "idscapturenode.h"





IDSCaptureNode::IDSCaptureNode()
{
    m_type=Type::IDSCaptureNode;



    getAvaibleCameras();

    for (int index = 0; index < m_availableCameras->count(); ++index) {

        IDSCamera* camera=m_availableCameras->getItemAt(index);
        LOG_INFO("Camera detected:"+camera->serialnumber()+"("+QString::number(camera->camID())+")");
    }


    m_checkCamerasTimer= new QTimer(this);



    connect(&watcher, &QFutureWatcher<void>::finished, this, [this](){
        this->m_checkCamerasTimer->start(5000);
    });


    m_checkCamerasTimer->setInterval(1000);


    m_checkCamerasTimer->setSingleShot(true);

    connect(m_checkCamerasTimer, SIGNAL(timeout()), SLOT(onCheckCameras()));


    //m_checkCamerasTimer->start();
}

IDSCaptureNode::~IDSCaptureNode()
{
    closeCamera();
    m_checkCamerasTimer->stop();
    watcher.waitForFinished();
}



void IDSCaptureNode::onCheckCameras()
{
    QFuture<void> future = QtConcurrent::run(this,&IDSCaptureNode::getAvaibleCameras);

    watcher.setFuture(future);



}


QQmlComponent *IDSCaptureNode::delegate(QQmlEngine &engine)noexcept
{


    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/IDSCaptureNodeItem.qml"));
    return delegate.get();

}


void IDSCaptureNode::GetMaxImageSize(INT *pnSizeX, INT *pnSizeY)
{
    // Check if the camera supports an arbitrary AOI
    // Only the ueye xs does not support an arbitrary AOI
    INT nAOISupported = 0;
    BOOL bAOISupported = TRUE;
    if (is_ImageFormat(m_camHandler,
                       IMGFRMT_CMD_GET_ARBITRARY_AOI_SUPPORTED,
                       (void*)&nAOISupported,
                       sizeof(nAOISupported)) == IS_SUCCESS)
    {
        bAOISupported = (nAOISupported != 0);
    }

    if (bAOISupported)
    {
        // All other sensors
        // Get maximum image size
        SENSORINFO sInfo;
        is_GetSensorInfo (m_camHandler, &sInfo);
        *pnSizeX = sInfo.nMaxWidth;
        *pnSizeY = sInfo.nMaxHeight;
    }
    else
    {
        // Only ueye xs
        // Get image size of the current format
        IS_SIZE_2D imageSize;
        is_AOI(m_camHandler, IS_AOI_IMAGE_GET_SIZE, (void*)&imageSize, sizeof(imageSize));

        *pnSizeX = imageSize.s32Width;
        *pnSizeY = imageSize.s32Height;
    }
}


void IDSCaptureNode::GetFrames(){


    int frames=0;

    while(terminateCapture==false){


#ifdef __linux__
        //linux code goes here
#elif _WIN32
        // windows code goes here
        DWORD dwRet = WaitForSingleObject(m_hEvent, 1000);

        if (dwRet == WAIT_TIMEOUT)

        {

            /* wait timed out */

            qDebug()<<"Frame Timeout";

        }

        else if (dwRet == WAIT_OBJECT_0)

        {
            /* event signalled */

            //frame
            mutex.lock();
            qDebug()<<"Frame Captured - "<<frames++;


            memcpy(frameSink()->cvMat()->ptr(), m_pcImageMemory,m_nSizeX * m_nSizeY);

            emit frameSinkChanged(frameSink());
            setFrameCaptured(true);

            frame_processed.wait(&mutex);
            setFrameCaptured(false);
            mutex.unlock();




        }
#else

#endif




    }
    terminateCapture=false;
}

void IDSCaptureNode::setCamera(bool open)
{


    if(this->selectedCamera()==nullptr){
        return;
    }


    m_camHandler=this->selectedCamera()->camID();


    if(open){
        INT nRet = is_InitCamera (&m_camHandler, NULL);
        if(nRet==IS_SUCCESS){
            LOG_INFO("Camera Inited ok ("+selectedCamera()->serialnumber()+":"+QString::number(selectedCamera()->camID())+")");

            nRet = is_ParameterSet(m_camHandler, IS_PARAMETERSET_CMD_LOAD_EEPROM, NULL, NULL);
            if(nRet==IS_SUCCESS){
                LOG_INFO("Camera parameters loaded ok ("+selectedCamera()->serialnumber()+":"+QString::number(selectedCamera()->camID())+")");

            }
            if (m_pcImageMemory != NULL)
            {
                is_FreeImageMem( m_camHandler, m_pcImageMemory, m_lMemoryId );
            }

            m_pcImageMemory = NULL;

            SENSORINFO SensorInfo;
            is_GetSensorInfo (m_camHandler, &SensorInfo);

            // init image size to sensor size by default
            GetMaxImageSize(&m_nSizeX, &m_nSizeY);


            is_SetColorMode (m_camHandler, IS_CM_MONO8);

            // memory initialization
            is_AllocImageMem (	m_camHandler,
                                m_nSizeX,
                                m_nSizeY,
                                8,
                                &m_pcImageMemory,
                                &m_lMemoryId);

            is_SetImageMem (m_camHandler, m_pcImageMemory, m_lMemoryId); // set memory active
            selectedCamera()->setFrameAddress(m_pcImageMemory);

            IS_SIZE_2D imageSize;
            imageSize.s32Width = m_nSizeX;
            imageSize.s32Height = m_nSizeY;

            is_AOI(m_camHandler, IS_AOI_IMAGE_SET_SIZE, (void*)&imageSize, sizeof(imageSize));


            nRet=is_SetDisplayMode (m_camHandler, IS_SET_DM_DIB);


            QQmlContext *currentContext = QQmlEngine::contextForObject(this->getItem());
            if(currentContext){
                QQmlEngine *engine = currentContext->engine();
                //                FrameProvider *imageProvider = (FrameProvider*)engine->imageProvider(QLatin1String("FrameProvider"));
                //                if(imageProvider){
                //                    imageProvider->setFrameAddress(m_pcImageMemory);
                //                    imageProvider->setFrameSize(QSize(m_nSizeX,m_nSizeY));
                //                }
            }



            cv::Mat* frameMat=new cv::Mat(m_nSizeY,m_nSizeX, CV_8UC1);
            setFrameSink(new QMat(frameMat));

            //setFrameSink(new IDSFrame(m_pcImageMemory,m_nSizeX,m_nSizeY));

            if(nRet==IS_SUCCESS){


                LOG_INFO("Camera setdisplay mode ok ("+selectedCamera()->serialnumber()+":"+QString::number(selectedCamera()->camID())+")");

                nRet= is_CaptureVideo( m_camHandler, IS_WAIT );

                if (nRet == IS_SUCCESS)

                {
                    qDebug()<<"Video Capture started OK";

                    setCameraOpened(true);

                }

            }
        }

    }
    else{


        closeCamera();


        setCameraOpened(false);
    }
}

void IDSCaptureNode::setContinuousCapture(bool continuousCapture)
{
    if (m_continuousCapture == continuousCapture)
        return;

    m_continuousCapture = continuousCapture;


    if(m_continuousCapture){
#ifdef __linux__
        //linux code goes here
#elif _WIN32
        // windows code goes here
        m_hEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);

        is_InitEvent(m_camHandler, m_hEvent, IS_SET_EVENT_FRAME);
        is_EnableEvent(m_camHandler, IS_SET_EVENT_FRAME);
        QFuture<void> future = QtConcurrent::run(this,&IDSCaptureNode::GetFrames);

        watcher.setFuture(future);
#else

#endif



    }
    else{


#ifdef __linux__
        //linux code goes here
#elif _WIN32
        // windows code goes here
        is_DisableEvent(m_camHandler, IS_SET_EVENT_FRAME);

        is_ExitEvent(m_camHandler, IS_SET_EVENT_FRAME);

        CloseHandle(m_hEvent);
        frame_processed.wakeAll();
        terminateCapture=true;
        watcher.waitForFinished();
#else

#endif


    }

    emit continuousCaptureChanged(m_continuousCapture);
}



void IDSCaptureNode::closeCamera(){

    if(m_selectedCamera==nullptr){
        return;
    }

    setContinuousCapture(false);


    // Stop live video
    is_StopLiveVideo( m_camHandler, IS_WAIT );

    // Free the allocated buffer
    if( m_pcImageMemory != NULL )
        is_FreeImageMem( m_camHandler, m_pcImageMemory, m_lMemoryId );

    m_pcImageMemory = NULL;

    selectedCamera()->setFrameAddress(m_pcImageMemory);

    // Close camera
    is_ExitCamera( m_camHandler );
    m_camHandler = NULL;

    LOG_INFO("Camera "+selectedCamera()->serialnumber()+"("+QString::number(selectedCamera()->camID())+") closed");
}

void IDSCaptureNode::setNewFrame(bool newFrame)
{
    if(newFrame){
        frame_processed.wakeAll();
    }

    CaptureNode::setNewFrame(newFrame);

}

void IDSCaptureNode::getAvaibleCameras()
{
    // At least one camera must be available

    INT nNumCam;

    if(m_cameraOpened){
        return;
    }

    //m_cameras.clear();

    if( is_GetNumberOfCameras( &nNumCam ) == IS_SUCCESS) {

        if( nNumCam >= 1 ) {

            // Create new list with suitable size

            UEYE_CAMERA_LIST* pucl;

            pucl = (UEYE_CAMERA_LIST*) new BYTE [sizeof (DWORD) + nNumCam * sizeof (UEYE_CAMERA_INFO)];

            pucl->dwCount = nNumCam;



            //Retrieve camera info


            if (is_GetCameraList(pucl) == IS_SUCCESS) {



                m_availableCameras->MergeCameras(pucl);


            }



            delete [] pucl;

        }
        else{
            m_availableCameras->clear();
        }

    }


    setSelectedCamera(m_availableCameras->findByID(m_cameraID));

}



void IDSCaptureNode::DeSerialize(QJsonObject &json)
{
    CaptureNode::DeSerialize(json);

    setSelectedCamera(m_availableCameras->findByID(m_cameraID));

    // checkDirect3D();

   setConfigsLoaded(true);
}

