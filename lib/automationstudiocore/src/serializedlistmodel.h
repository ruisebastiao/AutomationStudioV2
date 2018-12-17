#ifndef SERIALIZEDLISTMODEL_H
#define SERIALIZEDLISTMODEL_H

#include "automationstudiocoreglobal.h"
#include "jsonserializable.h"
#include "typedlistmodel.h"
#include <qabstractitemmodel.h>
#include <boost/mpl/clear.hpp>


template<class T>
class AUTOMATIONSTUDIO_CORE_EXPORT SerializedListModel : public TypedListModel<T>, public JsonSerializable
{
    Q_INTERFACES(JsonSerializable)

public:
    SerializedListModel(QObject *parent = nullptr){

    }

    // JsonSerializable interface
public:
    virtual void Serialize(QJsonArray &jsonarray) override
    {
        for (int itemIndex = 0; itemIndex < TypedListModel<T>::m_internalList.length(); ++itemIndex) {
            QJsonObject itemObject;

            T *item= TypedListModel<T>::m_internalList.at(itemIndex);
            item->Serialize(itemObject);

            jsonarray.append(itemObject);

        }
    }
    virtual void DeSerialize(QJsonArray &jsonarray) override
    {
        for (int listIndex = 0; listIndex < jsonarray.size(); ++listIndex) {
            QJsonObject projectObject = jsonarray[listIndex].toObject();

            T *item= new T();
            item->DeSerialize(projectObject);

            TypedListModel<T>::addItem(item);

        }
    }

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent) const override
    {
        return TypedListModel<T>::m_internalList.length();
    }
    virtual QVariant data(const QModelIndex &index, int role) const override
    {

    }

    // JsonSerializable interface
public:
    virtual void Serialize(QJsonObject &json) override
    {

    }
    virtual void DeSerialize(QJsonObject &json) override
    {

    }
};

#endif // SERIALIZEDLISTMODEL_H
