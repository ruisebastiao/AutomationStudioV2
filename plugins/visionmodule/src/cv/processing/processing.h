#ifndef PROCESSING_H
#define PROCESSING_H

#include <QObject>
#include <jsonserializable.h>
#include <qabstractitemmodel.h>
#include <qsortfilterproxymodel.h>

#include <cv/qmat.h>
#include "opencv2/imgproc.hpp"


class Processing : public QObject,public JsonSerializable
{
    Q_OBJECT

    Q_ENUMS(Type)

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged  USER("serialize"))

    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged USER("serialize"))

    Q_PROPERTY(int position READ position WRITE setPosition NOTIFY positionChanged  USER("serialize"))

    Q_PROPERTY(Type type READ type NOTIFY typeChanged  USER("serialize"))

    Q_PROPERTY(bool loaded READ loaded NOTIFY loadedChanged)

public:
    explicit Processing(QObject *parent = nullptr);
    enum Type {
        PreProcessingThreshold,
        PreProcessingMask,

        PostProcessingContours

    };

    virtual void apply(cv::Mat& input,cv::Mat& preprocessed,cv::Mat& original)=0;

    bool operator< (const Processing &other) const {
           return position()< other.position();
       }
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
    bool enabled() const
    {
        return m_enabled;
    }
signals:
    void typeChanged(Type type);

    void nameChanged(QString name);

    void processorConditionChanged();
    void positionChanged(int position);

    void loadedChanged(bool loaded);

    void enabledChanged(bool enabled);

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

    void setEnabled(bool enabled)
    {
        if (m_enabled == enabled)
            return;

        m_enabled = enabled;
        emit enabledChanged(m_enabled);
        if(loaded()){
            emit processorConditionChanged();
        }
    }


protected:

    Type m_type;
    QString m_visualItem;
    QString m_name="";



private:

    int m_position=0;

    bool m_loaded=false;


    bool m_enabled=true;


};

#endif // PROCESSING_H
