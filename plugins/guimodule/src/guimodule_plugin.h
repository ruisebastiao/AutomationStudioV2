#pragma once

#include <QQmlExtensionPlugin>

class GuimodulePlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri);
    void initializeEngine(QQmlEngine *engine, const char *uri) Q_DECL_OVERRIDE;
};
