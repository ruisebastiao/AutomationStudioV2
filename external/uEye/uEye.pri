INCLUDEPATH += $$PWD/include



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib -luEye_api_64
else:win32:CONFIG(debug, debug|release): LIBS +=-L$$PWD/lib -luEye_api_64
else:unix: LIBS += -lueye_api -L/usr/local/lib

