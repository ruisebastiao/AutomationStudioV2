TEMPLATE = lib
TARGET = networkmanager
QT += qml quick concurrent
CONFIG += plugin c++14
PLUGIN_NAME = networkmanager
PLUGIN_PATH = networkmanager

# PLUGIN_NAME and PLUGIN_PATH must be set up prior to including this config file
include($$getGlobalFile(plugin.pri))

TARGET = $$qtLibraryTarget($$TARGET)
uri = networkmanager


RESOURCES += \
    src/networkmanager.qrc


OTHER_FILES += \
    qml/*.qml \
    qml/qmldir

DISTFILES = qmldir \
    qml/plugins.qmltypes \

include($$PWD/src/networkmanager.pri)

#qmldir.files = qmldir

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qml/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}


#unix {
#    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
#    qmldir.path = $$installPath
#    target.path = $$installPath
#    INSTALLS += target qmldir
#}
