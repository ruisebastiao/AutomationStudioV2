BUILD_PATH   = $$shadowed($$PWD)



DEPLOY_PATH = $$BUILD_PATH/bin

RPI{
    DEPLOY_PATH=$$[QT_SYSROOT]/root/AutomationStudio
}
