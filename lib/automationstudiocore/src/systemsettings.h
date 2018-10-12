#ifndef SYSTEMSETTINGS_H
#define SYSTEMSETTINGS_H

#include "automationstudiocoreglobal.h"

#include <qobject.h>
#include <qhostaddress.h>
#include <qnetworkinterface.h>
#include <qprocess.h>
#include "QNetworkConfigurationManager"
#include "QNetworkSession"


class AUTOMATIONSTUDIO_CORE_EXPORT SystemSettings:public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(SystemSettings)

    Q_PROPERTY(QString localIP READ localIP NOTIFY localIPChanged)
    Q_PROPERTY(QNetworkSession::State networkState READ networkState NOTIFY networkStateChanged)
    Q_PROPERTY(QString hostname READ hostname WRITE setHostname NOTIFY hostnameChanged)

    Q_PROPERTY(QString sysInfo READ sysInfo NOTIFY sysInfoChanged)

    Q_PROPERTY(QString boardInfo READ boardInfo NOTIFY boardInfoChanged)



private:
    QString m_localIP;
    QNetworkConfigurationManager *manager;

    QNetworkSession::State m_networkState;

    QString m_hostname="?";

    QString m_sysInfo="";

    QString m_boardInfo="N/A";

public:
    SystemSettings(QObject *parent = nullptr);

    Q_INVOKABLE void setNewHostName(QString name);
    QString localIP()
    {
        QList<QHostAddress> list = QNetworkInterface::allAddresses();
        for(int nIter=0; nIter<list.length(); nIter++)
        {
//            qDebug() << list[nIter].toString();

            QString ip=list[nIter].toString();
            if(ip.contains("127.0.0.1")==false && ip.contains(":")==false){
              m_localIP=ip;
              break;
            }
        }
        return m_localIP;
    }

    QNetworkSession::State networkState() const
    {
        return m_networkState;
    }

    QString hostname() const
    {
        return m_hostname;
    }

    QString sysInfo() const
    {
        return m_sysInfo;
    }

    QString boardInfo() const
    {
        return m_boardInfo;
    }

private slots:
    void NetworkChanged(QNetworkSession::State state);
public slots:

    void setHostname(QString hostname)
    {
        if (m_hostname == hostname)
            return;

        m_hostname = hostname;



        emit hostnameChanged(m_hostname);
    }

signals:
    void localIPChanged(QString localIP);
    void networkStateChanged(QNetworkSession::State networkState);
    void hostnameChanged(QString hostname);
    void sysInfoChanged(QString sysInfo);
    void boardInfoChanged(QString boardInfo);
};

#endif // SYSTEMSETTINGS_H
