#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include "automationstudiocoreglobal.h"
#include "jsonserializable.h"

class AUTOMATIONSTUDIO_CORE_EXPORT TCPClient : public QObject, public JsonSerializable
{
    Q_OBJECT

    Q_PROPERTY(QString host READ host WRITE setHost NOTIFY hostChanged USER("seriablizable"))
    Q_PROPERTY(uint port READ port WRITE setPort NOTIFY portChanged)

public:
    explicit TCPClient(QObject *parent = nullptr);

signals:

    void hostChanged(QString host);

    void portChanged(uint port);

public slots:

    // JsonSerializable interface
    void setHost(QString host)
    {
        if (m_host == host)
            return;

        m_host = host;
        emit hostChanged(m_host);
    }

    void setPort(uint port)
{
    if (m_port == port)
    return;

m_port = port;
emit portChanged(m_port);
}

public:
    virtual void Serialize(QJsonObject &json) override;
    virtual void DeSerialize(QJsonObject &json) override;

    QString host() const
    {
        return m_host;
    }

    uint port() const
    {
        return m_port;
    }

private:

    QString m_host="";
    uint m_port=9601;
};


#endif // TCPCLIENT_H
