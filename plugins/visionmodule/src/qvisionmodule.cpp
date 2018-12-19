#include "qvisionmodule.h"

#include <nodes/filecapturenode.h>
#include <nodes/framebuffernode.h>
#include <nodes/idscapturenode.h>
#include <nodes/visionsystemnode.h>


QVisionModule::QVisionModule(QQuickItem *parent)
{
    m_type=ModuleType::VisionModule;
    m_moduleName="Vision";

}


