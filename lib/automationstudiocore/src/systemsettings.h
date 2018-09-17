#ifndef SYSTEMSETTINGS_H
#define SYSTEMSETTINGS_H

#include "automationstudiocoreglobal.h"

#include <qobject.h>
#include <qhostaddress.h>
#include <qnetworkinterface.h>
#include "QNetworkConfigurationManager"
#include "QNetworkSession"


class AUTOMATIONSTUDIO_CORE_EXPORT SystemSettings:public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(SystemSettings)

    Q_PROPERTY(QString localIP READ localIP NOTIFY localIPChanged)
    Q_PROPERTY(QNetworkSession::State networkState READ networkState NOTIFY networkStateChanged)
private:
    QString m_localIP;
    QNetworkConfigurationManager *manager;

    QNetworkSession::State m_networkState;

public:
    SystemSettings(QObject *parent = nullptr);

    QString localIP()
    {
        QList<QHostAddress> list = QNetworkInterface::allAddresses();
        for(int nIter=0; nIter<list.count(); nIter++)
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

private slots:
    void NetworkChanged(QNetworkSession::State state);
public slots:

signals:
    void localIPChanged(QString localIP);
    void networkStateChanged(QNetworkSession::State networkState);
};

#endif // SYSTEMSETTINGS_H
