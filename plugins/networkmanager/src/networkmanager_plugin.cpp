#include "networkmanager.h"
#include "networkmanager_plugin.h"
#include <QQmlEngine>

#include <qqml.h>

void NetworkManagerPlugin::registerTypes(const char *uri)
{
    // @uri networkmanager
    qmlRegisterType<NetworkManager>(uri, 1, 0, "NetworkManager");
    qmlRegisterUncreatableType<NetworkInfo>(uri, 1, 0, "NetworkInfo","Not creatable");

    qDebug()<<"Rgistered types";
}

void NetworkManagerPlugin::initializeEngine(QQmlEngine *engine, const char *uri)
{
    engine->addImportPath("qrc:///");
}

