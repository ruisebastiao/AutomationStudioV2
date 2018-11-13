#include "jsonserializable.h"
#include <QMetaProperty>
#include <QVariant>
#include <qdebug.h>


void JsonSerializable::Serialize(QJsonObject &json, QObject *target)
{
    if(target!=nullptr){
        for (int i = 0; i < target->metaObject()->propertyCount(); i++)
        {
            QMetaProperty property = target->metaObject()->property(i);

            QString classname=target->metaObject()->className();
            QString superclassname=target->metaObject()->superClass()->className();

            if(property.isReadable() && property.isUser()){

                QVariant value = target->property(property.name());
                if(property.isEnumType()){

                    QMetaEnum en = property.enumerator();
                    json[property.name()]= en.key(target->property(property.name()).toInt());
                }
                else{

                    auto isobject=value.canConvert<QObject*>();
                    if(isobject){
                        QObject* propvalue=value.value<QObject*>();
                        JsonSerializable *serializable = qobject_cast<JsonSerializable*>(propvalue);


                        if(serializable){
                            QJsonObject propjson;
                            serializable->Serialize(propjson);
                            json[property.name()]=propjson;
                        }
                    }
                    else{

                        json[property.name()] = value.toJsonValue();

                    }
                }
            }

        }
    }

}

void JsonSerializable::DeSerialize(QJsonObject &json, QObject *target)
{
    if(target!=nullptr){
        for (int i = 0; i < target->metaObject()->propertyCount(); i++)
        {

            QMetaProperty property = target->metaObject()->property(i);
            const char* propName=property.name();

            QString classname=target->metaObject()->className();
            QString superclassname=target->metaObject()->superClass()->className();


            if(property.isReadable() && property.isWritable() && property.isUser()){


                QVariant value = target->property(property.name());

                auto isobject=value.canConvert<QObject*>();
                if(isobject){

                    QObject* propvalue=value.value<QObject*>();
                    JsonSerializable *serializable = qobject_cast<JsonSerializable*>(propvalue);


                    if(serializable){
                        QJsonObject propJson=json[propName].toObject();
                        serializable->DeSerialize(propJson);
                    }

                }
                else{
                    QVariant value=json[propName].toVariant();
                    target->setProperty(propName,value);

                }

            }

        }
    }
}

