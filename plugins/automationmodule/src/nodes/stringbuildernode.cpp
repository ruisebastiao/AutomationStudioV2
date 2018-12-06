#include "stringbuildernode.h"

StringBuilderNode::StringBuilderNode()
{
    m_type=Type::StringBuilderNode;
}


QQmlComponent *StringBuilderNode::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/StringBuilderNodeItem.qml"));
    return delegate.get();

}

