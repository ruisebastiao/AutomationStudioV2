#include "qepsonmodule.h"
#include "flownode.h"

#include <nodes/commandparsernode.h>
#include <nodes/commandsendernode.h>
#include <nodes/epsonnode.h>


QEpsonModule::QEpsonModule(QQuickItem *parent)
{

    m_type=EpsonModule;
    m_moduleName="Epson";
}



