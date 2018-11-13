#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include <QObject>
#include <jsonserializable.h>
#include <qabstractitemmodel.h>
#include <qsortfilterproxymodel.h>

#include <cv/qmat.h>
#include "opencv2/imgproc.hpp"


class PreProcessing : public QObject,public JsonSerializable
{
    Q_OBJECT
    Q_ENUMS(Type)

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged  USER("serialize"))

    Q_PROPERTY(int position READ position WRITE setPosition NOTIFY positionChanged  USER("serialize"))

    Q_PROPERTY(Type type READ type NOTIFY typeChanged  USER("serialize"))

    Q_PROPERTY(bool loaded READ loaded NOTIFY loadedChanged)



public:
    enum Type {
        PreProcessingThreshold,
        PreProcessingContours

    };
    explicit PreProcessing(QObject *parent = nullptr);

    virtual void apply(cv::Mat& input,cv::Mat& preprocessed,cv::Mat& original)=0;

    bool operator< (const PreProcessing &other) const {
           return position()< other.position();
       }
private:

    int m_position=0;

    bool m_loaded=false;


signals:

    void typeChanged(Type type);

    void nameChanged(QString name);

    void preProcessorConditionChanged();
    void positionChanged(int position);

    void loadedChanged(bool loaded);

public slots:

    void setName(QString name)
    {
        if (m_name == name)
            return;

        m_name = name;
        emit nameChanged(m_name);
    }

    void setPosition(int position)
    {
        if (m_position == position)
            return;

        m_position = position;
        emit positionChanged(m_position);
    }

    void setLoaded(bool loaded)
    {
        if (m_loaded == loaded)
            return;

        m_loaded = loaded;
        emit loadedChanged(m_loaded);
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
    int position() const
    {
        return m_position;
    }
    bool loaded() const
    {
        return m_loaded;
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
        PreProcessorRole,
        PositionRole

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
        if (role == PositionRole){

            return preprocessing->position();
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

        // TODO check for duplicate positions , assign position to last ordered (do this in caller object)
        m_preprocessors.insert(preprocessor->position(),preprocessor);


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


    inline int count(){
        return  m_preprocessors.length();
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


//class PreProcessorFilterProxyModel : public QSortFilterProxyModel
//{
//    Q_OBJECT
//public:

//    PreProcessorFilterProxyModel (QObject* parent = nullptr)
//    {

//    }

//    ~PreProcessorFilterProxyModel ()
//    {

//    }

//    Q_INVOKABLE void setFilterString(QString string)
//    {

//    }

//    Q_INVOKABLE void setSortOrder(bool checked)
//    {

//    }
////    Q_INVOKABLE void setSortRole(bool checked)
////    {

////    }
//};


#endif // PREPROCESSING_H
