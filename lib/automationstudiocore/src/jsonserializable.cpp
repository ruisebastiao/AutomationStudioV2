#include "jsonserializable.h"
#include <QMetaProperty>
#include <QVariant>
#include <qabstractitemmodel.h>
#include <qdebug.h>


void JsonSerializable::Serialize(QJsonObject &json, QObject *target)
{
    if(target!=nullptr){
        for (int i = 0; i < target->metaObject()->propertyCount(); i++)
        {
            QMetaProperty property = target->metaObject()->property(i);
            const char* propName=property.name();

            QString classname=target->metaObject()->className();
            QString superclassname=target->metaObject()->superClass()->className();

            if(property.isReadable() && property.isUser()){

                QVariant value = target->property(propName);
                if(property.isEnumType()){

                    QMetaEnum en = property.enumerator();
                    json[propName]= en.key(target->property(propName).toInt());
                }
                else{

                    auto isobject=value.canConvert<QObject*>();
                    if(isobject){
                        QObject* propvalue=value.value<QObject*>();
                        JsonSerializable *serializable = qobject_cast<JsonSerializable*>(propvalue);


                        if(serializable){


                            auto isabstractlist=value.canConvert<QAbstractListModel*>();
                            if(isabstractlist){

                                QJsonArray propArray=json[propName].toArray();
                                serializable->Serialize(propArray);
                                json[propName]=propArray;
                            }
                            else {
                                QJsonObject propJson;
                                propJson=json[propName].toObject();
                                serializable->Serialize(propJson);
                                json[propName]=propJson;
                            }



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


                QVariant value = target->property(propName);

                auto isobject=value.canConvert<QObject*>();
                if(isobject){

                    if(value.isNull()==true || value.isValid()==false){
                        continue;
                    }

                    QObject* propvalue=value.value<QObject*>();
                    JsonSerializable *serializable = qobject_cast<JsonSerializable*>(propvalue);


                    if(serializable){



                        if(json[propName].isArray()){

                            QJsonArray propJson=json[propName].toArray();
                            serializable->DeSerialize(propJson);
                        }
                        else if(json[propName].isObject()) {
                          QJsonObject propJson=json[propName].toObject();
                           serializable->DeSerialize(propJson);
                        }


                        target->setProperty(propName,value);
                    }

                }
                else{
                    QVariant value=json[propName].toVariant();
                    target->setProperty(propName,value);

                }

            }

        }
    }
    m_deserialized=true;
}

void JsonSerializable::Serialize(QJsonArray &jsonarray)
{

}

void JsonSerializable::DeSerialize(QJsonArray &jsonarray)
{


}


