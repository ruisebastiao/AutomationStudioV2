#ifndef TYPEDLISTMODEL_H
#define TYPEDLISTMODEL_H

#include <qabstractitemmodel.h>
#include "automationstudiocoreglobal.h"

template<class T>
class AUTOMATIONSTUDIO_CORE_EXPORT TypedListModel : public QAbstractListModel
{
public:
    TypedListModel(QObject *parent = nullptr){

    }

    virtual void AddItem(T* item){
        beginInsertRows(QModelIndex(), rowCount(QModelIndex()), rowCount(QModelIndex()));   // kindly provided by superclass

        m_internalList.append(item);

        endInsertRows();
    }
    virtual void RemoveItem(T* item){
        int itemIndex=m_internalList.indexOf(item);

        if(itemIndex>=0){
            beginRemoveRows(QModelIndex(), static_cast<int>(itemIndex), static_cast<int>(itemIndex));   // kindly provided by superclass

            m_internalList.removeAt(itemIndex);



            endRemoveRows();


        }
    }
    virtual void clear(){
        if(m_internalList.length()>0){

            beginRemoveRows(QModelIndex(), 0,m_internalList.length()-1);   // kindly provided by superclass

            foreach (T* item, m_internalList) {
                item->deleteLater();
            }

            m_internalList.clear();

            endRemoveRows();

        }
    }
    virtual T* at(int index){
        if(index>=0 && index<m_internalList.length()){
            return m_internalList.at(index);
        }

        return nullptr;
    }

    int length() const{
        return m_internalList.length();
    }



protected:
    QList<T*> m_internalList;

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent) const override{
        return this->length();
    }



    // QAbstractItemModel interface
public:
    virtual QVariant data(const QModelIndex &index, int role) const override
    {

    }


};

#endif // TYPEDLISTMODEL_H
