TEMPLATE = lib
TARGET = automationmodule
QT += qml quick serialport concurrent
CONFIG += plugin c++14


#TARGET = $$qtLibraryTarget($$TARGET)

DEFINES += AUTOMATIONMODULE_LIB

uri = automationmodule

include(../../module.pri)

# Source

include($$PWD/src/automationmodule.pri)


include($$PWD/include/automationmoduleheaders.pri)
linkLocalPlugin(QuickQanava)
include($$PWD/../QuickQanava/include/quickqanavaheaders.pri)


OTHER_FILES += \
    qml/*.qml \
    qml/qmldir


win32{
LIBS += -luser32
}


RESOURCES += \
    src/automationmodule.qrc


DISTFILES = qml/qmldir

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qml/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}








linkLocalPlugin(QuickQanava)
linkLocalLib(automationstudiocore)
linkLocalLib(CuteLogger)
