TEMPLATE = lib
CONFIG += qt warn_on c++14
QT -= gui



# The ABI version.

!win32:VERSION = 1.0.0



# This one handles dllimport/dllexport directives.
DEFINES += QUAZIP_BUILD

# Input
include(quazip.pri)

include($$PROJECT_PATH/external/zlib/zlib.pri)

include($$PROJECT_PATH/lib.pri)

include($$PROJECT_PATH/functions.pri)

linkExternalLib(zlib/lib_x64,zlib)


