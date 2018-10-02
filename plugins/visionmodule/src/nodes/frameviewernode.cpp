#include "frameviewernode.h"

FrameViewerNode::FrameViewerNode()
{
    m_type=Type::FrameViewerNode;
}

QQmlComponent *FrameViewerNode::delegate(QQmlEngine &engine)
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:/components/nodes/FrameViewerNode.qml"));
    return delegate.get();

}
