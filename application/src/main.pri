INCLUDEPATH += $$PWD

#HEADERS += \
#    $$PWD/livecv.h


SOURCES += \
    $$PWD/main.cpp \
    $$PWD/automationstudio.cpp

HEADERS += \
    $$PWD/automationstudio.h

QMAKE_POST_LINK += $$quote(rm main.o$$escape_expand(\n\t))
