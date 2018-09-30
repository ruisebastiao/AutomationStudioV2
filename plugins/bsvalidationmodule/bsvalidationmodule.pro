TEMPLATE = lib
TARGET = bsvalidationmodule
QT += qml quick
CONFIG += plugin c++14


DEFINES += BSVALIDATIONMODULE_LIB

uri = bsvalidationmodule


include(../../plugin.pri)
include(../../functions.pri)

linkLocalPlugin(automationmodule)
linkLocalLib(CuteLogger)


include($$PWD/src/bsvalidationmodule.pri)

include($$PWD/../../lib/automationstudiocore/include/automationstudiocoreheaders.pri)
include($$PWD/../../lib/CuteLogger/include/cuteloggerheaders.pri)


OTHER_FILES += \
    qml/*.qml \
    qml/qmldir


include($$PWD/../automationmodule/include/automationmoduleheaders.pri)

include($$PWD/../QuickQanava/include/quickqanavaheaders.pri)

RESOURCES += \
    src/bsvalidationmodule.qrc

qmldir.files = qmldir

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qml/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}


