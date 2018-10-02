
TARGET = bsvalidationmodule
DEFINES += BSVALIDATIONMODULE_LIB
uri = bsvalidationmodule


include(../../module.pri)

include(src/bsvalidationmodule.pri)

linkLocalPlugin(automationmodule)
include($$PWD/../automationmodule/include/automationmoduleheaders.pri)
linkLocalPlugin(QuickQanava)
include($$PWD/../QuickQanava/include/quickqanavaheaders.pri)

RESOURCES += \
    src/bsvalidationmodule.qrc



!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qml/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}


