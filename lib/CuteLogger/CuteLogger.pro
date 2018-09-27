QT       -= gui

TARGET = CuteLogger
TEMPLATE = lib

DEFINES += CUTELOGGER_LIBRARY

include(../../lib.pri)

INCLUDEPATH += $$PWD/src

SOURCES += src/Logger.cpp \
           src/AbstractAppender.cpp \
           src/AbstractStringAppender.cpp \
           src/ConsoleAppender.cpp \
           src/FileAppender.cpp \
           src/RollingFileAppender.cpp

HEADERS += src/Logger.h \
           src/CuteLogger_global.h \
           src/AbstractAppender.h \
           src/AbstractStringAppender.h \
           src/ConsoleAppender.h \
           src/FileAppender.h \
           src/RollingFileAppender.h

