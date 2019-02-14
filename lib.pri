include(config.pri)
CONFIG      += warn_on qt thread c++11
## Destination

win32{
    DESTDIR    = $$DEPLOY_PATH/../dev/$$TARGET/
    DLLDESTDIR = $$DEPLOY_PATH
}

unix{

  DESTDIR = $$DEPLOY_PATH
#  REMOTE-RPI:!DO_PACKAGE{
#    DESTDIR =
#  }
}



include(dump_symbols.pri)


unix {
     QMAKE_LFLAGS += "-Wl,-rpath,\'\$$ORIGIN\'"

    target.path = /usr/lib
    REMOTE-RPI{
        target.path = $$REMOTE_PATH
    }


    !BUILDROOT{
        INSTALLS += target
    }
}

