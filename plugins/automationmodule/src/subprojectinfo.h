#ifndef SUBPROJECTINFO_H
#define SUBPROJECTINFO_H

#include <QObject>
#include <jsonserializable.h>



class SubProjectInfo:public QObject, public JsonSerializable
{
    Q_OBJECT
    Q_INTERFACES(JsonSerializable)


    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged USER("serialize"))
    Q_PROPERTY(QString projectName READ projectName WRITE setProjectName NOTIFY projectNameChanged USER("serialize"))

public:
    SubProjectInfo();
    SubProjectInfo(QString id,QString projectname);

    QString id() const
    {
        return m_id;
    }

    QString projectName() const
    {
        return m_projectName;
    }

public slots:
    void setId(QString id)
    {
        if (m_id == id)
            return;

        m_id = id;
        emit idChanged(m_id);
    }

    void setProjectName(QString projectName)
    {
        if (m_projectName == projectName)
            return;

        m_projectName = projectName;
        emit projectNameChanged(m_projectName);
    }

signals:
    void idChanged(QString id);

    void projectNameChanged(QString projectName);

private:

    QString m_id="";
    QString m_projectName="";

    // JsonSerializable interface
public:
    void Serialize(QJsonObject &json) override;
    void DeSerialize(QJsonObject &json) override;
};

#endif // SUBPROJECTINFO_H
