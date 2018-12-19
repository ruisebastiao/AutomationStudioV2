#include "qvisionmodule.h"

#include <nodes/filecapturenode.h>
#include <nodes/framebuffernode.h>
#include <nodes/idscapturenode.h>
#include <nodes/visionsystemnode.h>


QVisionModule::QVisionModule(QQuickItem *parent)
{
    m_type=ModuleType::VisionModule;
    m_moduleName="Vision";
    m_moduleNodeTypes.append(getModuleNodeTypes());
}



QVariantList QVisionModule::getModuleNodeTypes() const
{
    QVariantList ret;

    QVariantMap map;

    map.insert(QVariant::fromValue(FlowNode::Type::IDSCaptureNode).value<QString>(),"IDS Camera");
    ret.append(map);
    map.clear();

    map.insert(QVariant::fromValue(FlowNode::Type::FileCaptureNode).value<QString>(),"File Capture");
    ret.append(map);
    map.clear();

    map.insert(QVariant::fromValue(FlowNode::Type::FrameBufferNode).value<QString>(),"Frame Buffer");
    ret.append(map);
    map.clear();

    map.insert(QVariant::fromValue(FlowNode::Type::VisionSystemNode).value<QString>(),"Vision Processing");
    ret.append(map);
    map.clear();

    return ret;
}
