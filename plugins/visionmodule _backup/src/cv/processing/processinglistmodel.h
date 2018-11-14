#ifndef PROCESSINGLISTMODEL_H
#define PROCESSINGLISTMODEL_H

#include "processing.h"

#include <jsonserializable.h>
#include <qabstractitemmodel.h>



class ProcessingListModel : public QAbstractListModel,public JsonSerializable
{
    Q_OBJECT
    Q_INTERFACES(JsonSerializable)

    Q_ENUMS(ProcessingRoles)
public:
    enum ProcessingRoles {
        VisualItemRole = Qt::UserRole + 1,
        ProcessorRole,
        PositionRole

    };

    ProcessingListModel(QObject* parent=nullptr):QAbstractListModel(parent)
    {


    }


    void indexDataChanged(int itemindex)
    {
        emit dataChanged(index(itemindex),index(itemindex));
    }




    inline QHash<int, QByteArray> roleNames() const

    {
        return {

            { ProcessorRole, "processor" },
            { VisualItemRole, "visualItem" }

        };
    }


    inline QVariant data(const QModelIndex &index, int role) const
    {

        //std::lock_guard<decltype(mainQueueMutex)> lg(mainQueueMutex);

        //    qDebug()<<" Data asked for "<<index.row()<<" and role "<<role;
        if (index.row()<0 || index.row()>=m_processors.size())
        {
            return QVariant();
        }

        int idx=index.row();
        Processing* processing = getItemAt(idx);
        if(!processing){
            return QVariant();
        }
        if (role == ProcessorRole){

            return QVariant::fromValue(processing);
        }
        if (role == VisualItemRole){

            return processing->visualItem();
        }
        if (role == PositionRole){

            return processing->position();
        }


        return QVariant();
    }


    inline Processing *getItemAt(int index) const
    {
        if(index>=m_processors.length()){
            return nullptr;
        }
        return m_processors.at(index);
    }

    inline void addProcessor(Processing* processor)
    {
        beginInsertRows(QModelIndex(), rowCount(QModelIndex()), rowCount(QModelIndex()));   // kindly provided by superclass

        // TODO check for duplicate positions , assign position to last ordered (do this in caller object)
        m_processors.insert(processor->position(),processor);


        endInsertRows();
    }



    inline void removeProcessorAt(int idx)
    {
        if(idx<=m_processors.length())
            return;

        beginRemoveRows(QModelIndex(), idx, idx);   // kindly provided by superclass

        Processing* processor= m_processors.at(idx);
        processor->deleteLater();

        m_processors.removeAt(idx);

        endRemoveRows();
    }


    inline int count(){
        return  m_processors.length();
    }




private:

    QList<Processing*> m_processors;

    // JsonSerializable interface
public:
    virtual void Serialize(QJsonObject &json) override;
    virtual void DeSerialize(QJsonObject &json) override;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
};


#endif // PROCESSINGLISTMODEL_H
