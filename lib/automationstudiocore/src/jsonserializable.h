#ifndef JSONSERIALIZABLE_H
#define JSONSERIALIZABLE_H

#include "automationstudiocore/automationstudiocoreglobal.h"

#include <QJsonObject>
#include <QObject>



class AUTOMATIONSTUDIO_CORE_EXPORT JsonSerializable
{
//    Q_OBJECT

protected:



     virtual void Serialize(QJsonObject &json,QObject* target);
     virtual void DeSerialize(QJsonObject &json,QObject* target);

      virtual void Serialize(QJsonObject &json)=0;
      virtual void DeSerialize(QJsonObject &json)=0;




};
Q_DECLARE_INTERFACE(JsonSerializable, "JsonSerializable")
#endif // JSONSERIALIZABLE_H
