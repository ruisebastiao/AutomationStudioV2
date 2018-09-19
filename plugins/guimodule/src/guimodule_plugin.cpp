#include "guimodule_plugin.h"


#include <qqml.h>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>

void GuimodulePlugin::registerTypes(const char *uri)
{
    // @uri guimodule
    // qmlRegisterType<GuiModule>(uri, 1, 0, "GuiModule");
}

void GuimodulePlugin::initializeEngine(QQmlEngine *engine, const char *uri)
{
    engine->addImportPath("qrc:///");
}

