include(config.pri)

message(----PLUGIN---)
win32:{
    DESTDIR    = $$DEPLOY_PATH/dev/$$TARGET/lib
    DLLDESTDIR = $$DEPLOY_PATH
}else:DESTDIR = $$DEPLOY_PATH/$$TARGET/

#exists($$DEPLOY_PATH/plugins/$$TARGET/) {
#    message(do exist)
#    } else {
#        message(create)
#          QMAKE_POST_LINK += $$quote(mkdir -r $$DEPLOY_PATH/plugins/$$TARGET/ $$escape_expand(\n\t))
#    }

QMAKE_POST_LINK += $$quote(cp $${OUT_PWD}/qmldir $${DEPLOY_PATH}/$$TARGET/$$escape_expand(\n\t))

QMAKE_POST_LINK += $$quote(ln -s -f $${DEPLOY_PATH}/$${TARGET}/lib$$qtLibraryTarget($$TARGET).so $$[QT_INSTALL_LIBS]/$$escape_expand(\n\t))


#config.commands = ln -s -f $${DEPLOY_PATH}/plugins/lib$$qtLibraryTarget($$TARGET).so $$[QT_INSTALL_LIBS]/
#PRE_TARGETDEPS += config
#QMAKE_EXTRA_TARGETS += config
