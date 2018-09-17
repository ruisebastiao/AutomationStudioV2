TEMPLATE = lib
TARGET = guimodule
QT += qml quick
CONFIG += plugin c++14
PLUGIN_NAME = guimodule
PLUGIN_PATH = guimodule

# PLUGIN_NAME and PLUGIN_PATH must be set up prior to including this config file
include($$getGlobalFile(plugin.pri))

TARGET = $$qtLibraryTarget($$TARGET)
uri = guimodule


OTHER_FILES += \
    qml/*.qml \
    qml/qmldir

# Input
SOURCES += \
        guimodule_plugin.cpp

HEADERS += \
        guimodule_plugin.h

DISTFILES = qmldir \
    qml/plugins.qmltypes \
    qml/TextScroller.qml \
    qml/Blink.qml \
    qml/UserSettingsView.qml \
    qml/PaneHeader.qml \
    qml/LanguageItem.qml \
    qml/MaterialPlaceHolder.qml \
    qml/DockingLayout.qml \
    qml/DockingItem.qml

qmldir.files = qmldir

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qml/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}


unix {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}
