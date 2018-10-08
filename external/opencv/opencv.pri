INCLUDEPATH += $$PWD/include


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lopencv_world341
else:win32:CONFIG(debug, debug|release): LIBS +=-L$$PWD/lib/ -lopencv_world341d
else:unix: LIBS += -lopencv_core -lopencv_imgproc -lopencv_imgcodecs -L/usr/local/lib/

#win32{
# QMAKE_POST_LINK += $$quote(cp $$_PRO_FILE_PWD_/external/qmldir $$DEPLOY_PATH/$$TARGET/$$escape_expand(\n\t))
#}
