include(config.pri)


defineReplace(deployFileCommand){
    DEPLOY_FROM = $$shell_path($$shell_quote($$1))
    DEPLOY_TO = $$shell_path($$shell_quote($$2))

    debug(Deploy $$DEPLOY_FROM to $$DEPLOY_TO, 1)

    return($$QMAKE_COPY_FILE $$DEPLOY_FROM $$DEPLOY_TO)
}


defineTest(linkLocalLib){



    win32:LIB_PATH = $$DEPLOY_PATH/../dev/$$1/
    else{
        LIB_PATH = $$DEPLOY_PATH/
    }


    LIB_NAME = $$1

    LIBS *= -L$$LIB_PATH
    LIBS *= -l$$LIB_NAME

    export(LIBS)

}


defineTest(linkExternalLib){

#$$1  relative lib path
#$$2  libname
#$$3  libname extended


win32{

        LIB_PATH = $$PROJECT_PATH/external/$$1/
        LIB_NAME = $$2$$3

        message(Linking external lib: $$LIB_NAME in path:$$LIB_PATH )

        LIBS *= -L$$LIB_PATH
        LIBS *= -l$$LIB_NAME

        DEPLOY_FROM = $$shell_path($$shell_quote($${LIB_PATH}$${LIB_NAME}.dll))
        DEPLOY_TO = $$shell_path($$shell_quote($$DEPLOY_PATH/))

        QMAKE_POST_LINK +=$$quote($$QMAKE_COPY_FILE $$DEPLOY_FROM $$DEPLOY_TO $$escape_expand(\n\t))
        export(QMAKE_POST_LINK )
        export(LIBS)
    }







}

defineTest(linkLocalPlugin){



    win32:LIB_PATH = $$DEPLOY_PATH/../dev/$$1/
    else{
        LIB_PATH = $$DEPLOY_PATH/
    }

    LIB_NAME = $$1


    LIBS *= -L$$LIB_PATH
    LIBS *= -l$$LIB_NAME

    export(LIBS)

}




# Checks the qt version
#
# Args: (major, minor)
# Returns: true if version major is the same and version minor is the same or higher
#
defineTest(qtVersionCheck) {
    maj = $$1
    min = $$2
    isEqual(QT_MAJOR_VERSION, $$maj){
        isEqual(QT_MINOR_VERSION, $$min):return(true)
        greaterThan(QT_MINOR_VERSION, $$min):return(true)
    }
    return(false)
}


