#include "projectnode.h"

ProjectNode::ProjectNode()
{

}


QQmlComponent*  ProjectNode::delegate(QQmlEngine& engine) noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/ProjectNodeItem.qml"));
    return delegate.get();
}
