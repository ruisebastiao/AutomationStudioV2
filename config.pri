

SYSTEM_BSVALIDATION{
    message("BSValidaton System")
    RPI{
        CONFIG+=PLUGIN-NETWORKMANAGER
    }
    CONFIG+=PLUGIN-BSVALIDATION

}


RPI{
    DEPLOY_PATH=$$[QT_SYSROOT]/root/AutomationStudio
}


include(versioning/version.pri)
