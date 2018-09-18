#ifndef NETWORKINFO_H
#define NETWORKINFO_H

#include <QObject>
#include <math.h>


class NetworkInfo : public QObject
{
    Q_OBJECT






public:
    enum NetAuth{
        AUTH_NONE_OPEN,
        AUTH_NONE_WEP,
        AUTH_NONE_WEP_SHARED,
        AUTH_IEEE8021X,
        AUTH_WPA_PSK,
        AUTH_WPA_EAP,
        AUTH_WPA2_PSK,
        AUTH_WPA2_EAP
    };
    Q_ENUM(NetAuth)


    enum NetEncr{
        ENCR_TKIP,
        ENCR_CCMP

    };
    Q_ENUM(NetEncr)


    enum NetStatus{
        NET_CONNECTED,
        NET_CONNECTING,
        NET_REJECTED,
        NET_DISCONNECTED,


    };

    Q_ENUM(NetStatus)

    enum RejectReason{
        REJECT_CONNFAILED,
        REJECT_WRONGKEY
    };


    Q_ENUM(RejectReason)



    explicit NetworkInfo(QObject *parent = nullptr, QString _bssid="", QString _ssid="", NetAuth _auth=AUTH_NONE_OPEN, NetEncr _encr=ENCR_TKIP, int _networkSignal=-95, bool wpsavailable=false);

    Q_PROPERTY(QString ssid READ ssid WRITE setSsid NOTIFY ssidChanged)
    Q_PROPERTY(QString bssid READ bssid WRITE setBssid NOTIFY bssidChanged)
    Q_PROPERTY(int networkSignal READ networkSignal WRITE setNetworkSignal NOTIFY networkSignalChanged)
    Q_PROPERTY(bool wpsAvailable READ wpsAvailable NOTIFY wpsAvailableChanged)
    Q_PROPERTY(int signalLevel READ signalLevel WRITE setSignalLevel NOTIFY signalLevelChanged)
    Q_PROPERTY(bool removed READ removed WRITE setRemoved NOTIFY removedChanged)
    Q_PROPERTY(NetAuth auth READ auth WRITE setAuth NOTIFY authChanged)
    Q_PROPERTY(NetEncr encr READ encr WRITE setEncr NOTIFY encrChanged)

    Q_PROPERTY(NetStatus networkStatus READ networkStatus WRITE setNetworkStatus NOTIFY networkStatusChanged)
    Q_PROPERTY(RejectReason networkRejectReason READ networkRejectReason WRITE setNetworkRejectReason NOTIFY networkRejectReasonChanged)

    Q_PROPERTY(QString ip READ ip WRITE setIp NOTIFY ipChanged)
    Q_PROPERTY(bool isConfigured READ isConfigured WRITE setIsConfigured NOTIFY isConfiguredChanged)

    Q_PROPERTY(int networkID READ networkID  NOTIFY networkIDChanged)




    Q_PROPERTY(QString passKey READ passKey WRITE setPassKey NOTIFY passKeyChanged)



    QString ssid() const
    {
        return m_ssid;
    }

    QString bssid() const
    {
        return m_bssid;
    }

    int networkSignal() const
    {
        return m_networkSignal;
    }

//    bool m_removed=false;

    bool operator == (NetworkInfo *d) {
       return d->ssid()==ssid();
    }

    bool removed() const
    {
        return m_removed;
    }

    void setRemoved(bool removed)
    {
        if (m_removed == removed)
            return;

        m_removed = removed;
        emit removedChanged(m_removed);
    }


    NetAuth auth() const
    {
        return m_auth;
    }

    int signalLevel() const
    {
        return m_signalLevel;
    }

    bool wpsAvailable() const
    {
        return m_wpsAvailable;
    }

    bool connected() const
    {
        return m_connected;
    }

    QString ip() const
    {
        return m_ip;
    }

    bool isConfigured() const
    {
        return m_isConfigured;
    }


    QString passKey() const
    {
        return m_passKey;
    }

    NetEncr encr() const
    {
        return m_encr;
    }



    NetStatus networkStatus() const
    {
        return m_networkStatus;
    }

    RejectReason networkRejectReason() const
    {
        return m_networkRejectReason;
    }

    int networkID() const
    {
        return m_networkID;
    }

private:
    QString m_ssid="";

    QString m_bssid="";



    int m_networkSignal=-95;
    bool m_removed=false;

    NetAuth m_auth;

    int m_signalLevel;

    bool m_wpsAvailable;

    bool m_connected=false;

    QString m_ip="";

    bool m_isConfigured=false;



    QString m_passKey;

    NetEncr m_encr=ENCR_TKIP;



    NetStatus m_networkStatus=NET_DISCONNECTED;

    RejectReason m_networkRejectReason=REJECT_CONNFAILED;

    int m_networkID;

signals:

    void ssidChanged(QString ssid);

    void bssidChanged(QString bssid);

    void networkSignalChanged(int networkSignal);

    void removedChanged(bool removed);

    void authChanged(NetAuth auth);

    void signalLevelChanged(int signalLevel);

    void wpsAvailableChanged(bool wpsAvailable);

    void connectedChanged(bool connected);

    void ipChanged(QString ip);

    void isConfiguredChanged(bool isConfigured);



    void passKeyChanged(QString passKey);

    void encrChanged(NetEncr encr);



    void networkStatusChanged(NetStatus networkStatus);

    void networkRejectReasonChanged(RejectReason networkRejectReason);

    void networkIDChanged(int networkID);

public slots:
    void setSsid(QString ssid)
    {
        if (m_ssid == ssid)
            return;

        m_ssid = ssid;
        emit ssidChanged(m_ssid);
    }
    void setBssid(QString bssid)
    {
        if (m_bssid == bssid)
            return;

        m_bssid = bssid;
        emit bssidChanged(m_bssid);
    }
    void setNetworkSignal(int networkSignal)
    {

        setSignalLevel(networkSignal);

        if(networkSignal<-95) networkSignal=-95;
        if(networkSignal>-35) networkSignal=-35;

        networkSignal=-95-networkSignal;

        networkSignal=abs(networkSignal*100/60);


        if (m_networkSignal == networkSignal)
            return;

        m_networkSignal = networkSignal;
        emit networkSignalChanged(m_networkSignal);
    }

    void setAuth(NetAuth auth)
    {
        if (m_auth == auth)
            return;

        m_auth = auth;
        emit authChanged(m_auth);
    }
    void setSignalLevel(int signalLevel)
    {
        if (m_signalLevel == signalLevel)
            return;

        m_signalLevel = signalLevel;
        emit signalLevelChanged(m_signalLevel);
    }
    void setWpsAvailable(bool wpsAvailable)
    {
        if (m_wpsAvailable == wpsAvailable)
            return;

        m_wpsAvailable = wpsAvailable;
        emit wpsAvailableChanged(m_wpsAvailable);
    }



    void setIp(QString ip)
    {
        if (m_ip == ip)
            return;

        m_ip = ip;
        emit ipChanged(m_ip);
    }
    void setIsConfigured(bool isConfigured)
    {
        if (m_isConfigured == isConfigured)
            return;

        m_isConfigured = isConfigured;
        emit isConfiguredChanged(m_isConfigured);
    }


    void setPassKey(QString passKey)
    {
        if (m_passKey == passKey)
            return;

        m_passKey = passKey;
        emit passKeyChanged(m_passKey);
    }
    void setEncr(NetEncr encr)
    {
        if (m_encr == encr)
            return;

        m_encr = encr;
        emit encrChanged(m_encr);
    }

    void setNetworkStatus(NetStatus networkStatus)
    {
        if (m_networkStatus == networkStatus)
            return;

        m_networkStatus = networkStatus;
        emit networkStatusChanged(m_networkStatus);
    }
    void setNetworkRejectReason(RejectReason networkRejectReason)
    {
        if (m_networkRejectReason == networkRejectReason)
            return;

        m_networkRejectReason = networkRejectReason;
        emit networkRejectReasonChanged(m_networkRejectReason);
    }
    void setNetworkID(int networkID)
    {
        if (m_networkID == networkID)
            return;

        m_networkID = networkID;
        emit networkIDChanged(m_networkID);
    }
};

#endif // NETWORKINFO_H
