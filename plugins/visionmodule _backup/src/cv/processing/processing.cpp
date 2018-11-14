#include "processing.h"


Processing::Processing(QObject *parent) : QObject(parent)
{

}

QString Processing::visualItem() const
{
    return m_visualItem;
}

void Processing::Serialize(QJsonObject &json)
{
    JsonSerializable::Serialize(json,this);
}

void Processing::DeSerialize(QJsonObject &json)
{
    //const bool wasBlocked = this->blockSignals(true);
    // no signals here

    JsonSerializable::DeSerialize(json,this);
   // this->blockSignals(wasBlocked);

    setLoaded(true);


}

