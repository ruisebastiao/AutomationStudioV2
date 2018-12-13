#ifndef JSONSERIALIZABLE_H
#define JSONSERIALIZABLE_H

#include "automationstudiocoreglobal.h"
#include <qvariant.h>
#include <QJsonObject>
#include <qjsonarray.h>
#include <QObject>



class AUTOMATIONSTUDIO_CORE_EXPORT JsonSerializable
{
    //    Q_OBJECT

public:



    virtual void Serialize(QJsonObject &json,QObject* target);
    virtual void DeSerialize(QJsonObject &json,QObject* target);

    virtual void Serialize(QJsonArray &jsonarray);
    virtual void DeSerialize(QJsonArray &jsonarray);

    virtual void Serialize(QJsonObject &json)=0;
    virtual void DeSerialize(QJsonObject &json)=0;

protected:

    bool m_deserialized=false;
};
Q_DECLARE_METATYPE(QVariant*);
Q_DECLARE_INTERFACE(JsonSerializable, "JsonSerializable")
#endif // JSONSERIALIZABLE_H
