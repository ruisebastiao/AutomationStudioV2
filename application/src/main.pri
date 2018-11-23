INCLUDEPATH += $$PWD

#HEADERS += \
#    $$PWD/livecv.h


include($$PROJECT_PATH/shared/crashhandler/crash_handler.pri)


SOURCES += \
    $$PWD/main.cpp \
    $$PWD/automationstudio.cpp

HEADERS += \
    $$PWD/automationstudio.h

unix:QMAKE_POST_LINK += $$quote(rm main.o$$escape_expand(\n\t))
win32:CONFIG(release, debug|release): QMAKE_POST_LINK += $$quote(del release\main.obj$$escape_expand(\n\t))
else:win32:CONFIG(debug, debug|release): QMAKE_POST_LINK += $$quote(del debug\main.obj$$escape_expand(\n\t))
