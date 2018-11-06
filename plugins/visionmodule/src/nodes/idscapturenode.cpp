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



    INT nMemID = 0;
    char *pBuffer = nullptr;


    while(terminateCapture==false){


#ifdef __linux__
        //linux code goes here
#elif _WIN32
        // windows code goes here
        DWORD dwRet = WaitForSingleObject(m_hEvent, 2000);

        //        dwRet = WaitForMultipleObjects(m_EvMax,m_hEv, FALSE ,INFINITE );

        if (dwRet == WAIT_TIMEOUT)

        {

            /* wait timed out */

            qDebug()<<"Frame Timeout";

        }

        else if (dwRet == WAIT_OBJECT_0)

        {
            /* event signalled */

            is_LockSeqBuf(m_camHandler,m_nSeqNumId[m_frameBufferCount], m_pcSeqImgMem[m_frameBufferCount]);
            LOG_INFO()<<"Frame stored @ buffer index:"<<m_frameBufferCount++;

            if( m_numBuffers == m_frameBufferCount )
            {

                m_frameBufferCount=0;
                LOG_INFO("Buffer full, lock and processing");


                // find the latest image buffer
                INT nNum;
                char *pcMem, *pcMemLast;
                is_GetActSeqBuf(m_camHandler, &nNum, &pcMem, &pcMemLast);
                for( int i=0 ; i<m_numBuffers ; i++)
                {
                    pcMemLast = m_pcSeqImgMem[i];
                    //frame
                    mutex.lock();



                    memcpy(frameSink()->cvMat()->ptr(), pcMemLast,m_nSizeX * m_nSizeY);
                    is_UnlockSeqBuf( m_camHandler, m_nSeqNumId[i], m_pcSeqImgMem[i] );

                    emit frameSinkChanged(frameSink());
                    setFrameCaptured(true);

                    frame_processed.wait(&mutex);
                    setFrameCaptured(false);
                    mutex.unlock();

                }
                LOG_INFO("All buffers processed");




            }


        }
#else

#endif




    }
    terminateCapture=false;
    LOG_INFO()<<"Frame thread terminating";


}

void IDSCaptureNode::setCamera(bool open)
{




    if(this->selectedCamera()==nullptr){
        return;
    }
    QtConcurrent::run([this,open](){

        setUpdatingCamera(true);

        m_camHandler=this->selectedCamera()->camID();


        if(open){
            INT nRet = is_InitCamera (&m_camHandler, NULL);
            if(nRet==IS_SUCCESS){
                LOG_INFO("Camera Inited ok ("+selectedCamera()->serialnumber()+":"+QString::number(selectedCamera()->camID())+")");

                nRet = is_ParameterSet(m_camHandler, IS_PARAMETERSET_CMD_LOAD_EEPROM, NULL, NULL);
                if(nRet==IS_SUCCESS){
                    LOG_INFO("Camera parameters loaded ok ("+selectedCamera()->serialnumber()+":"+QString::number(selectedCamera()->camID())+")");

                }


                SENSORINFO SensorInfo;
                is_GetSensorInfo(m_camHandler, &SensorInfo );


                CAMINFO CamInfo;
                is_GetCameraInfo(m_camHandler, &CamInfo );

                // setup image size
                //GetMaxImageSize(&m_nSizeX, &m_nSizeY);


                IS_SIZE_2D imageSize;
//                imageSize.s32Width = m_nSizeX;
//                imageSize.s32Height = m_nSizeY;

                is_AOI(m_camHandler, IS_AOI_IMAGE_GET_SIZE, (void*)&imageSize, sizeof(imageSize));

                m_nSizeX=imageSize.s32Width;
                m_nSizeY=imageSize.s32Height;
                // remove when setting AOI in parameters
                //is_AOI(m_camHandler, IS_AOI_IMAGE_SET_SIZE, (void*)&imageSize, sizeof(imageSize));




                INT nAllocSizeX = 0;
                INT nAllocSizeY = 0;

                m_nSizeX = nAllocSizeX = imageSize.s32Width;
                m_nSizeY = nAllocSizeY = imageSize.s32Height;

                UINT nAbsPosX = 0;
                UINT nAbsPosY = 0;

                // absolute pos?
                is_AOI(m_camHandler, IS_AOI_IMAGE_GET_POS_X_ABS, (void*)&nAbsPosX , sizeof(nAbsPosX));
                is_AOI(m_camHandler, IS_AOI_IMAGE_GET_POS_Y_ABS, (void*)&nAbsPosY , sizeof(nAbsPosY));

                if (nAbsPosX)
                {
                    nAllocSizeX = SensorInfo.nMaxWidth;
                }
                if (nAbsPosY)
                {
                    nAllocSizeY = SensorInfo.nMaxHeight;
                }

                // calculate single buffer size
                m_dwSingleBufferSize = nAllocSizeX * nAllocSizeY * m_nBitsPerPixel / 8;


                // alloc seq buffers in a loop
                for( int i=0; i< m_numBuffers  ; i++ )
                {

                    // allocate buffer memory
                    nRet = is_AllocImageMem(m_camHandler,
                                            nAllocSizeX,
                                            nAllocSizeY,
                                            m_nBitsPerPixel,
                                            &m_pcSeqImgMem[i],
                                            &m_lSeqMemId[i]);
                    if( nRet != IS_SUCCESS )
                    {
                        break;  // it makes no sense to continue
                    }

                    // put memory into seq buffer
                    nRet = is_AddToSequence(	m_camHandler, m_pcSeqImgMem[i], m_lSeqMemId[i] );
                    m_nSeqNumId[i] = i+1; // store sequence buffer number Id
                    if( nRet != IS_SUCCESS )
                    {
                        // free latest buffer
                        is_FreeImageMem( m_camHandler, m_pcSeqImgMem[i], m_lSeqMemId[i] );
                        break; // it makes no sense to continue
                    }


                }



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


                }



                if (nRet == IS_SUCCESS){

                }

                setCameraOpened(true);

                updateExternalTrigger(m_externalTrigger);
                updateContinuousCapture(m_continuousCapture);
            }

        }
        else{




            closeCamera();


            setCameraOpened(false);
        }
        setUpdatingCamera(false);

    });


}

void IDSCaptureNode::updateContinuousCapture(bool value){


    setUpdatingCamera(true);
    if(value){
#ifdef __linux__
        //linux code goes here
#elif _WIN32
        // windows code goes here
        LOG_INFO()<<"starting live capture";
        m_hEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);

        is_InitEvent(m_camHandler, m_hEvent, IS_SET_EVENT_FRAME);
        is_EnableEvent(m_camHandler, IS_SET_EVENT_FRAME);
        QFuture<void> future = QtConcurrent::run(this,&IDSCaptureNode::GetFrames);

        watcher.setFuture(future);


#else

#endif



        INT nRet = is_CaptureVideo( m_camHandler, IS_DONT_WAIT );

        if (nRet == IS_SUCCESS)

        {
            LOG_INFO()<<"live capture started OK";



        }

        emit continuousCaptureChanged(m_continuousCapture);
    }
    else{

        QtConcurrent::run([this](){

#ifdef __linux__
            //linux code goes here
#elif _WIN32
            // windows code goes here
            LOG_INFO()<<"stopping live capture";

            if(m_hEvent){
                //       frame_processed.wakeAll();
                terminateCapture=true;


                watcher.waitForFinished();

                LOG_INFO()<<"Frame thread finished";

                is_DisableEvent(m_camHandler, IS_SET_EVENT_FRAME);

                is_ExitEvent(m_camHandler, IS_SET_EVENT_FRAME);

                CloseHandle(m_hEvent);

            }
#else

#endif



            // Stop live video
            is_StopLiveVideo( m_camHandler, IS_WAIT );
            setUpdatingCamera(false);
            emit continuousCaptureChanged(m_continuousCapture);
        });

    }


}

void IDSCaptureNode::setContinuousCapture(bool continuousCapture)
{
    if (m_continuousCapture == continuousCapture)
        return;



    this->setUpdatingCamera(true);

    m_continuousCapture = continuousCapture;

    updateContinuousCapture(continuousCapture);

    this->setUpdatingCamera(false);

}



void IDSCaptureNode::closeCamera(){

    if(m_selectedCamera==nullptr){
        return;
    }

    setContinuousCapture(false);




    // Free the allocated buffer

    is_ClearSequence( m_camHandler );

    // free seq buffers
    int i;
    for( i=(m_numBuffers-1); i>=0   ; i-- )
    {
        // free buffers
        if( is_FreeImageMem( m_camHandler, m_pcSeqImgMem[i], m_lSeqMemId[i] ) != IS_SUCCESS )
        {
            return;
        }


    }

    // Close camera
    is_ExitCamera( m_camHandler );
    m_camHandler = NULL;

    LOG_INFO("Camera "+selectedCamera()->serialnumber()+"("+QString::number(selectedCamera()->camID())+") closed");
}


void IDSCaptureNode::updateExternalTrigger(bool value){

    if(m_cameraOpened==true){

        INT nRet = 0;

        bool wasLive=continuousCapture();

        if(wasLive){
            setContinuousCapture(false);
        }
        if(value){
            nRet=is_SetTimeout(m_camHandler, IS_TRIGGER_TIMEOUT, 12000);

            if (nRet == IS_SUCCESS)
            {




            }
            nRet=is_SetExternalTrigger(m_camHandler, IS_SET_TRIGGER_LO_HI);
            if (nRet == IS_SUCCESS){
                qDebug()<<"Set external trigger OK";
            }
        }
        else{
            nRet=is_SetExternalTrigger(m_camHandler, IS_SET_TRIGGER_OFF);
            if (nRet == IS_SUCCESS){
                qDebug()<<"Disabled external trigger OK";
            }
        }
        if(wasLive){
            setContinuousCapture(true);
        }
    }


}

void IDSCaptureNode::setExternalTrigger(bool externalTrigger)
{
    if(externalTrigger==m_externalTrigger){
        return;
    }


    updateExternalTrigger(externalTrigger);

    CameraCaptureNode::setExternalTrigger(externalTrigger);
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

