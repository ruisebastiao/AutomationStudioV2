BUILD_PATH   = $$shadowed($$PWD)


message(:$$QT_INSTALL_PREFIX)

DEPLOY_PATH = $$BUILD_PATH/bin

RPI{
    #DEPLOY_PATH=$$[QT_SYSROOT]/root/AutomationStudio
    DEPLOY_PATH=/root/AutomationStudio
}
