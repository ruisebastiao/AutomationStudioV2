include(config.pri)

defineTest(linkLocalLib){



    win32:LIB_PATH = $$DEPLOY_PATH/dev/$$1/
    else{
        LIB_PATH = $$DEPLOY_PATH/
    }


    LIB_NAME = $$1


    message(link library:$$1)

    LIBS *= -L$$LIB_PATH
    LIBS *= -l$$LIB_NAME

    export(LIBS)

}

defineTest(linkLocalPlugin){



    win32:LIB_PATH = $$DEPLOY_PATH/dev/$$1/
    else{
        LIB_PATH = $$DEPLOY_PATH/
    }

    LIB_NAME = $$1


    message(link plugin:$$1)

    LIBS *= -L$$LIB_PATH
    LIBS *= -l$$LIB_NAME

    export(LIBS)

}


defineReplace(deployFileCommand){
    DEPLOY_FROM = $$shell_path($$shell_quote($$1))
    DEPLOY_TO = $$shell_path($$shell_quote($$2))

    debug(Deploy $$DEPLOY_FROM to $$DEPLOY_TO, 1)

    return($$QMAKE_COPY_FILE $$DEPLOY_FROM $$DEPLOY_TO)
}

