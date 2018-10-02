TEMPLATE = lib
QT += qml quick
CONFIG += plugin c++14

include(plugin.pri)
include(functions.pri)

linkLocalLib(CuteLogger)
linkLocalPlugin(automationstudiocore)




include(lib/automationstudiocore/include/automationstudiocoreheaders.pri)
include(lib/CuteLogger/include/cuteloggerheaders.pri)


OTHER_FILES += \
    qml/*.qml \
    qml/qmldir
qmldir.files = qmldir

