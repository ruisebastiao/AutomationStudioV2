BUILD_PATH   = $$shadowed($$PWD)


REMOTE_PATH=/root/AutomationStudio/

DEPLOY_PATH = $$BUILD_PATH/bin

RPI{
    DEPLOY_PATH=$$[QT_SYSROOT]/root/AutomationStudio
}
