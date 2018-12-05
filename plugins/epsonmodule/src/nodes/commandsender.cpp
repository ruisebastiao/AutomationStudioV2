#include "commandsender.h"

CommandSender::CommandSender()
{
    m_type=Type::CommandSender;
}


QQmlComponent *CommandSender::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/CommandSenderNodeItem.qml"));
    return delegate.get();

}

