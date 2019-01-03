#include "roinode.h"
#include "visionsystemnode.h"

VisionSystemNode::VisionSystemNode()
{


    m_type=Type::VisionSystemNode;




}

VisionSystemNode::~VisionSystemNode()
{



}

QQmlComponent *VisionSystemNode::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/VisionSystemNodeItem.qml"));
    return delegate.get();
}

void VisionSystemNode::setFrameBufferSource(QVariant frameBufferSource)
{

    m_frameBufferSource = frameBufferSource;
    emit frameBufferSourceChanged(m_frameBufferSource);

}




void VisionSystemNode::Serialize(QJsonObject &json)
{
    FlowNode::Serialize(json);


}

void VisionSystemNode::DeSerialize(QJsonObject &json)
{


    FlowNode::DeSerialize(json);

}
