

SYSTEM_BSVALIDATION{


    RPI{
        CONFIG+=PLUGIN-NETWORKMANAGER
    }
    CONFIG+=PLUGIN-BSVALIDATION

}


RPI{
    DEPLOY_PATH=$$[QT_SYSROOT]/root/AutomationStudio


    RPI_2{
        prefix_platform=_rpi2
    }

    RPI_3{
        prefix_platform=_rpi3
    }
}



SYSTEM_BSVALIDATION{
    prefix_sys=BSVALIDATION
}

SYSTEM_VISION{
    prefix_sys=VISION
}





DEFINES*=APP_ID="\\\"$$prefix_sys"\\\"


win32:{
    prefix_os=win32_

}

unix:{
    prefix_os=linux_

}
#TARGET_ABI=$${QT_BUILDABI}


TARGET_ABI=$${QT_ARCH}


BUILD_ID=$${prefix_os}$${TARGET_ABI}$${prefix_platform}

DEFINES*=BUILD_ID="\\\"$$BUILD_ID"\\\"



include(versioning/version.pri)
