
INCLUDEPATH += $$PWD/src/

HEADERS += \
    $$PWD/src/crypt.h \
    $$PWD/src/ioapi.h \
    $$PWD/src/mztools.h \
    $$PWD/src/unzip.h \
    $$PWD/src/zip.h

SOURCES += \
    $$PWD/src/ioapi.c \
    $$PWD/src/mztools.c \
    $$PWD/src/unzip.c \
    $$PWD/src/zip.c


win32{

HEADERS += \
    $$PWD/src/iowin32.h \

SOURCES += \
    $$PWD/src/iowin32.c

}
