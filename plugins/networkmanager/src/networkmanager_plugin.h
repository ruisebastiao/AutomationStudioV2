#pragma once

#include <QQmlExtensionPlugin>

class NetworkManagerPlugin: public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri);

    // QQmlExtensionInterface interface
public:
    virtual void initializeEngine(QQmlEngine *engine, const char *uri) override;
};
