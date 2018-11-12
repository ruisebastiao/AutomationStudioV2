#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include <QObject>
#include <jsonserializable.h>
#include <qabstractitemmodel.h>



class PreProcessing : public QObject,public JsonSerializable
{
    Q_OBJECT
    Q_ENUMS(Type)

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged  USER("serialize"))


    Q_PROPERTY(Type type READ type NOTIFY typeChanged  USER("serialize"))


public:
    enum Type {
        PreProcessingThreshold

    };
    explicit PreProcessing(QObject *parent = nullptr);

signals:

    void typeChanged(Type type);

    void nameChanged(QString name);

public slots:

    void setName(QString name)
    {
        if (m_name == name)
            return;

        m_name = name;
        emit nameChanged(m_name);
    }

protected:

    Type m_type;
    QString m_visualItem;
    QString m_name="";



    // JsonSerializable interface
public:
    virtual void Serialize(QJsonObject &json) override;
    virtual void DeSerialize(QJsonObject &json) override;
    Type type() const
    {
        return m_type;
    }
    QString visualItem() const;
    QString name() const
    {
        return m_name;
    }
};


class PreProcessingListModel : public QAbstractListModel,public JsonSerializable
{
    Q_OBJECT
    Q_INTERFACES(JsonSerializable)

    Q_ENUMS(PreProcessingRoles)
public:
    enum PreProcessingRoles {
        VisualItemRole = Qt::UserRole + 1,
        PreProcessorRole

    };

    PreProcessingListModel(QObject* parent=nullptr):QAbstractListModel(parent)
    {


    }

    void indexDataChanged(int itemindex)
    {
        emit dataChanged(index(itemindex),index(itemindex));
    }




    inline QHash<int, QByteArray> roleNames() const

    {
        return {

            { PreProcessorRole, "preProcessor" },
            { VisualItemRole, "visualItem" }

        };
    }


    inline QVariant data(const QModelIndex &index, int role) const
    {

        //std::lock_guard<decltype(mainQueueMutex)> lg(mainQueueMutex);

        //    qDebug()<<" Data asked for "<<index.row()<<" and role "<<role;
        if (index.row()<0 || index.row()>=m_preprocessors.size())
        {
            return QVariant();
        }

        int idx=index.row();
        PreProcessing* preprocessing = getItemAt(idx);
        if(!preprocessing){
            return QVariant();
        }
        if (role == PreProcessorRole){

            return QVariant::fromValue(preprocessing);
        }
        if (role == VisualItemRole){

            return preprocessing->visualItem();
        }


        return QVariant();
    }


    inline PreProcessing *getItemAt(int index) const
    {
        if(index>=m_preprocessors.length()){
            return nullptr;
        }
        return m_preprocessors.at(index);
    }

    inline void addPreprocessor(PreProcessing* preprocessor)
    {
        beginInsertRows(QModelIndex(), rowCount(QModelIndex()), rowCount(QModelIndex()));   // kindly provided by superclass

        m_preprocessors.append(preprocessor);

        endInsertRows();
    }



    inline void removePreprocessorAt(int idx)
    {
        if(idx<=m_preprocessors.length())
            return;

        beginRemoveRows(QModelIndex(), idx, idx);   // kindly provided by superclass

        PreProcessing* preprocessor= m_preprocessors.at(idx);
        preprocessor->deleteLater();

        m_preprocessors.removeAt(idx);

        endRemoveRows();
    }




private:

    QList<PreProcessing*> m_preprocessors;

    // JsonSerializable interface
public:
    virtual void Serialize(QJsonObject &json) override;
    virtual void DeSerialize(QJsonObject &json) override;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
};

#endif // PREPROCESSING_H