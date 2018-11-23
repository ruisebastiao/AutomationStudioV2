


win32-msvc* {
    # generate the symbol file
    QMAKE_LFLAGS_RELEASE += /MAP /debug /opt:ref
    QMAKE_CFLAGS_RELEASE += -Zi
    QMAKE_CXXFLAGS_RELEASE += -Zi
}

unix:QMAKE_CFLAGS += -g
unix:QMAKE_CXXFLAGS += -g

# prevent undue optimization, which ruins breakpad's backtrace
QMAKE_CFLAGS_RELEASE -= -O
QMAKE_CFLAGS_RELEASE -= -O1
QMAKE_CFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE -= -O
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2

prefix_sys=

if(isEmpty(SYSTEM)){
   error("No system defined")
}
else{
    for(a, SYSTEM){
        contains( a, VISION ) {
                CONFIG+=SYSTEM_VISION
                prefix_sys+=VISION
        }
        contains( a, BSVALIDATION) {
            CONFIG+=SYSTEM_BSVALIDATION
                prefix_sys+=BSVALIDATION

         }
        contains( a, EPSON) {
            CONFIG+=SYSTEM_EPSON
                prefix_sys+=EPSON

         }


    }
}


APP_ID=$$join(prefix_sys,_,,)


SYSTEM_EPSON{
}

SYSTEM_BSVALIDATION{


    RPI{
        CONFIG+=PLUGIN-NETWORKMANAGER
    }
    CONFIG+=PLUGIN-BSVALIDATION

}


SYSTEM_VISION{


    RPI{
        CONFIG+=PLUGIN-NETWORKMANAGER
    }

    CONFIG+=PLUGIN-VISION

}


RPI{
    DEPLOY_PATH=$$[QT_SYSROOT]/root/AutomationStudio/bin

    RPI_2{
        prefix_platform=_rpi2
    }

    RPI_3{
        prefix_platform=_rpi3
    }
}

DEFINES*=APP_ID="\\\"$$APP_ID"\\\"


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


#DEFINES*=BUILD_ID=asd


include(versioning/version.pri)

