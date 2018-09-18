#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QQmlListProperty>
#include <QtCore/QSocketNotifier>
#include "wpamsg.h"
//#include "scanresults.h"
#include "QDebug"
#include "networkinfo.h"
#include "networkslistmodel.h"
#include <list>
#include <QTimer>
#include <QProcess>
#include <QFuture>
#include <QtConcurrent>
#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(networkManager)


class NetworkManager : public QObject
{
    Q_OBJECT


public:
    enum WIFIStat{
        STAT_NOTINITED,
        STAT_DISCONNECTED,
        STAT_CONNECTING,
        STAT_CONNECTED
    };
    Q_ENUM(WIFIStat)



    explicit NetworkManager(QObject *parent = 0);

    Q_PROPERTY(bool wpsNetworksAvailable READ wpsNetworksAvailable NOTIFY wpsNetworksAvailableChanged)

    Q_PROPERTY(QString ifaceName READ ifaceName WRITE setIfaceName NOTIFY ifaceNameChanged)
    Q_PROPERTY(QString wpaDriver READ wpaDriver WRITE setWpaDriver NOTIFY wpaDriverChanged)

    Q_PROPERTY(QString lastMessage READ lastMessage WRITE setLastMessage NOTIFY lastMessageChanged)

    Q_PROPERTY(WIFIStat wifiStatus READ wifiStatus NOTIFY wifiStatusChanged)

    Q_PROPERTY(NetworksListModel *availableNetworks READ availableNetworks CONSTANT)

    Q_PROPERTY(NetworkInfo* connectedNetwork READ connectedNetwork   NOTIFY connectedNetworkChanged)

    Q_PROPERTY(bool started READ started WRITE setStarted NOTIFY startedChanged)

    Q_PROPERTY(bool wpsStarted READ wpsStarted WRITE setWpsStarted NOTIFY wpsStartedChanged)


    Q_PROPERTY(bool scanning READ scanning NOTIFY scanningChanged)

    Q_PROPERTY(int networksAvailableCount READ networksAvailableCount NOTIFY networksAvailableCountChanged)




    QString ifaceName() const
    {
        return m_ifaceName;
    }

    QString lastMessage() const
    {
        return m_lastMessage;
    }



    Q_INVOKABLE void start();

    //Q_INVOKABLE int getNetworksAvailable();

    Q_INVOKABLE void startWPS();

    Q_INVOKABLE void connectNetwork(int index);


    bool started() const
    {
        return m_started;
    }




    NetworksListModel * availableNetworks() const
    {
        return m_availableNetworks;
    }


    WIFIStat wifiStatus() const
    {
        return m_wifiStatus;
    }

    NetworkInfo* connectedNetwork() const
    {
        return m_connectedNetwork;
    }

    QString wpaDriver() const
    {
        return m_wpaDriver;
    }

    bool wpsNetworksAvailable() const
    {
        return m_wpsNetworksAvailable;
    }

    bool wpsStarted() const
    {
        return m_wpsStarted;
    }

    int networksAvailableCount() const
    {
        return m_networksAvailableCount;
    }

    Q_INVOKABLE void removeNetwork(int index);
    bool scanning() const
    {
        return m_scanning;
    }

private:
    char *ctrl_iface;
    struct wpa_ctrl *ctrl_conn;
    char *ctrl_iface_dir;
    struct wpa_ctrl *monitor_conn;
    QTimer *waitresults_timer;

    int m_timesToUpdate=1;

    int m_timesToPing=2;
    int m_timesToScan=1;

    static void executeProcess(QString cmd){
        QProcess::execute(cmd);
    }

    int openCtrlConnection(const char *ifname);
    QSocketNotifier *msgNotifier;

    int ctrlRequest(const char *cmd, char *buf, size_t *buflen);

    void setWifiStatus(WIFIStat wifiStatus)
    {
        if (m_wifiStatus == wifiStatus)
            return;

        m_wifiStatus = wifiStatus;

//        qCDebug(networkManager)<<"Status Changed:"<<m_wifiStatus;

        if(m_wifiStatus==STAT_CONNECTED){
            QtConcurrent::run(executeProcess, QString("udhcpc -i wlan0 -q"));


        }

        emit wifiStatusChanged(m_wifiStatus);
    }

    void updateResults();

    QTimer *check_timer = 0;

    QString m_ifaceName="wlan0";

    QString m_lastMessage;


    bool m_started=false;
    std::list<QString> m_ssids;



    NetworksListModel * m_availableNetworks;

    WIFIStat m_wifiStatus=WIFIStat::STAT_NOTINITED;

    NetworkInfo* m_connectedNetwork=0;

    QString m_wpaDriver="nl80211";

    bool m_wpsNetworksAvailable;

    bool m_wpsStarted=false;

    void getConfiguratedNetworks();
    int setNetworkParam(int id, const char *field, const char *value, bool quote);
    void getStatus();
    int m_networksAvailableCount=0;

    bool m_scanning;

signals:

    void ifaceNameChanged(QString ifaceName);

    void lastMessageChanged(QString lastMessage);


    void startedChanged(bool started);

    void wifiStatusChanged(WIFIStat wifiStatus);

    void connectedNetworkChanged(NetworkInfo* connectedNetwork);

    void wpaDriverChanged(QString wpaDriver);

    void wpsNetworksAvailableChanged(bool wpsNetworksAvailable);

    void wpsStartedChanged(bool wpsStarted);

    void networksAvailableCountChanged(int networksAvailableCount);

    void scanningChanged(bool scanning);

private slots:
    void testWpasupplicant();
    void getresults_timeout();

public slots:
    virtual void receiveMsgs();
    virtual void processMsg(char *msg);

    void scan();

    void setIfaceName(QString ifaceName)
    {
        if (m_ifaceName == ifaceName)
            return;



        m_ifaceName = ifaceName;
        ctrl_iface = strdup(ifaceName.toStdString().c_str());


        emit ifaceNameChanged(m_ifaceName);
    }
    void setLastMessage(QString lastMessage)
    {
        if (m_lastMessage == lastMessage)
            return;

        m_lastMessage = lastMessage;
        emit lastMessageChanged(m_lastMessage);
    }
    void setStarted(bool isstarted)
    {


        if (m_started == isstarted)
            return;


        m_started = isstarted;
        emit startedChanged(m_started);
    }



    void setConnectedNetwork(NetworkInfo* connectedNetwork)
    {
        if (m_connectedNetwork == connectedNetwork)
            return;

        if(m_connectedNetwork!=0)
            m_connectedNetwork->setNetworkStatus(NetworkInfo::NET_DISCONNECTED);

        m_connectedNetwork = connectedNetwork;

        if(m_connectedNetwork!=0)
            m_connectedNetwork->setNetworkStatus(NetworkInfo::NET_CONNECTED);

        emit connectedNetworkChanged(m_connectedNetwork);

        if(m_connectedNetwork==nullptr)
            setWifiStatus(NetworkManager::STAT_DISCONNECTED);
        else
            setWifiStatus(NetworkManager::STAT_CONNECTED);


    }
    void setWpaDriver(QString wpaDriver)
    {
        if (m_wpaDriver == wpaDriver)
            return;

        m_wpaDriver = wpaDriver;
        emit wpaDriverChanged(m_wpaDriver);
    }
    void setWpsNetworksAvailable(bool wpsNetworksAvailable)
    {
        if (m_wpsNetworksAvailable == wpsNetworksAvailable)
            return;

        m_wpsNetworksAvailable = wpsNetworksAvailable;
        emit wpsNetworksAvailableChanged(m_wpsNetworksAvailable);
    }
    void setWpsStarted(bool wpsStarted)
    {
        if (m_wpsStarted == wpsStarted)
            return;


        m_wpsStarted = wpsStarted;
        emit wpsStartedChanged(m_wpsStarted);
    }
    void setNetworksAvailableCount(int networksAvailableCount)
    {
        if (m_networksAvailableCount == networksAvailableCount)
            return;


        m_networksAvailableCount = networksAvailableCount;
        emit networksAvailableCountChanged(m_networksAvailableCount);
    }
    void setScanning(bool scanning)
    {
        if (m_scanning == scanning)
            return;

        m_scanning = scanning;
        emit scanningChanged(m_scanning);
    }
};

#endif // NETWORKMANAGER_H
