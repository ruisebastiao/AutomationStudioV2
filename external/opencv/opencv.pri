INCLUDEPATH += $$PWD/include


#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lopencv_world341
#else:win32:CONFIG(debug, debug|release): LIBS +=-L$$PWD/lib/ -lopencv_world341d
#else:unix: LIBS += -lopencv_core -lopencv_imgproc -lopencv_imgcodecs -L/usr/local/lib/


include($$PROJECT_PATH/functions.pri)



win32:CONFIG(release, debug|release){
 linkExternalLib(opencv/lib,opencv,_core341)
 linkExternalLib(opencv/lib,opencv,_imgproc341)
 linkExternalLib(opencv/lib,opencv,_imgcodecs341)
 linkExternalLib(opencv/lib,opencv,_videoio341)
 linkExternalLib(opencv/lib,tbb)
}
else:win32:CONFIG(debug, debug|release){
 linkExternalLib(opencv/lib,opencv,_core341d)
 linkExternalLib(opencv/lib,opencv,_imgproc341d)
 linkExternalLib(opencv/lib,opencv,_imgcodecs341d)
 linkExternalLib(opencv/lib,opencv,_videoio341d)
 linkExternalLib(opencv/lib,tbb,_debug)
}
else:unix: LIBS += -lopencv_core -lopencv_imgproc -lopencv_videoio -lopencv_imgcodecs -L/usr/local/lib/

