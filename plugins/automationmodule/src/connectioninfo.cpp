#include "connectioninfo.h"

ConnectionInfo::ConnectionInfo()
{

}

ConnectionInfo::ConnectionInfo(int nodeid, QString portid)
{
    m_nodeID=nodeid;
    m_portID=portid;
}

ConnectionInfo::~ConnectionInfo()
{

}

void ConnectionInfo::Serialize(QJsonObject &json)
{
    JsonSerializable::Serialize(json,this);
}

void ConnectionInfo::DeSerialize(QJsonObject &json)
{
     JsonSerializable::DeSerialize(json,this);
}

QMetaObject::Connection ConnectionInfo::edgeConnection() const
{
    return m_edgeConnection;
}

void ConnectionInfo::setEdgeConnection(const QMetaObject::Connection &edgeConnection)
{
    m_edgeConnection = edgeConnection;
}

QMetaMethod ConnectionInfo::edgeSlot() const
{
    return m_edgeSlot;
}

void ConnectionInfo::setEdgeSlot(const QMetaMethod &edgeSlot)
{
    m_edgeSlot = edgeSlot;
}
