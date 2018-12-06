#include "commandparsernode.h"

CommandParserNode::CommandParserNode()
{
    m_type=Type::CommandParserNode;
}


QQmlComponent *CommandParserNode::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/CommandParserNodeItem.qml"));
    return delegate.get();

}

