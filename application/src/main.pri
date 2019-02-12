INCLUDEPATH += $$PWD

#HEADERS += \
#    $$PWD/livecv.h


include($$PROJECT_PATH/shared/crashhandler/crash_handler.pri)


SOURCES += \
    $$PWD/main.cpp \
    $$PWD/automationstudio.cpp \
    $$PWD/settings.cpp

HEADERS += \
    $$PWD/automationstudio.h \
    $$PWD/settings.h

unix:QMAKE_POST_LINK += $$quote(rm main.o automationstudio.o$$escape_expand(\n\t))
win32:CONFIG(release, debug|release): QMAKE_POST_LINK += $$quote(del release\main.obj release\automationstudio.obj$$escape_expand(\n\t))
else:win32:CONFIG(debug, debug|release): QMAKE_POST_LINK += $$quote(del debug\main.obj debug\automationstudio.obj$$escape_expand(\n\t))
