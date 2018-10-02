#ifndef PROCESSING_H
#define PROCESSING_H

#include <QQuickItem>

#include <jsonserializable.h>

class Processing : public QQuickItem ,public JsonSerializable
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)



public:
    Processing();

    QString name() const
    {
        return m_name;
    }

signals:

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

QString m_name="Processing function";

private:


};

#endif // PROCESSING_H
