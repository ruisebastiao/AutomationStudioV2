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
