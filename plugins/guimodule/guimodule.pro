TARGET = guimodule
uri = guimodule

DEFINES += GUIMODULE_LIBRARY

include(../../module.pri)


include($$PWD/src/guimodule.pri)

RESOURCES += \
    src/guimodule.qrc


!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qml/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

DISTFILES += \
    src/qml/Utils.js

