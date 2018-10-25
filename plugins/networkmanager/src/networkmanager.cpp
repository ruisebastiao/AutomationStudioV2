#include "networkmanager.h"
#include <cstdio>
#include <unistd.h>
#include "wpa_ctrl.h"
#include "QDebug"
#include "QProcess"
#include "QFile"
#include "qthread.h"

#include <QFile>
#include <dirent.h>
#include <sys/types.h>
#include "Logger.h"


NetworkManager::NetworkManager(QObject *parent) : QObject(parent)
{

//    Q_LOGGING_CATEGORY(driverUsb, "driver.usb")

    ctrl_iface = NULL;
    ctrl_conn = NULL;
    monitor_conn = NULL;
    //check for wlan0

    QFile wlanfile("/sys/class/net/wlan0");
    if(!wlanfile.exists()) {
        qDebug()<<"modprobing brcmfmac";
        QProcess::execute("modprobe brcmfmac");
        QtConcurrent::run(executeProcess, QString("wpa_supplicant -D"+wpaDriver()+" -B -i wlan0 -c /etc/wpa_supplicant.conf"));

    }

    check_timer = new QTimer(this);
    connect(check_timer, SIGNAL(timeout()), SLOT(testWpasupplicant()));
    check_timer->setSingleShot(true);





    waitresults_timer = new QTimer(this);
    connect(waitresults_timer , SIGNAL(timeout()), SLOT(getresults_timeout()));
    waitresults_timer->setSingleShot(true);


    ctrl_iface_dir = strdup("/var/run/wpa_supplicant");

    ctrl_iface = strdup(ifaceName().toStdString().c_str());


    m_availableNetworks=new NetworksListModel();

    // qDebug()<<"Inited ok";
}

void NetworkManager::getresults_timeout(){

    char reply[10];
    size_t reply_len = sizeof(reply);

    qDebug()<<"Results timeout,sending terminate";


    ctrlRequest("TERMINATE", reply, &reply_len);

}

void NetworkManager::getStatus(){
    char buf[2048];
    size_t len;

    QString connected_ip;





    len = sizeof(buf) - 1;
    if (ctrl_conn == NULL || ctrlRequest("STATUS", buf, &len) < 0) {

        qDebug()<<"Could not get status from wpa_supplicant";
    }
    else{
        buf[len] = '\0';




        QString status(buf);

        // qDebug()<<"Status:"<<status;

        QList<QString> status_splited=status.split('\n');

        QString connected_ssid="";

        foreach (QString status_item, status_splited) {

            if(status_item.contains("ip_address=")){

                connected_ip=status_item.split('=')[1];


            }

            if(status_item.contains("ssid=")){

                connected_ssid=status_item.split('=')[1];


            }



            if(status_item.contains("wpa_state")){

                QString wpa_state=status_item.split('=')[1];

                if(wpa_state=="COMPLETED"){



                    setConnectedNetwork(m_availableNetworks->getBySSID(connected_ssid));



                }
                else if(wpa_state=="DISCONNECTED"){
                    //                    setWifiStatus(NetworkManager::STAT_DISCONNECTED);
                    setConnectedNetwork(0);
                }

            }
        }

        if(connectedNetwork()!=nullptr){
            connectedNetwork()->setIp(connected_ip);

        }



    }


}

void NetworkManager::testWpasupplicant()
{


    if(wpsStarted()==false){

        if(m_timesToPing<0){
            char buf[10];
            size_t len;

            m_timesToPing=3;

            QFile wpafile("/run/wpa_supplicant");
            if(!wpafile.exists()) {
                setWifiStatus(WIFIStat::STAT_NOTINITED);
                LOG_INFO()<<"WPA Supplicant not running... initializing";

                QtConcurrent::run(executeProcess, QString("wpa_supplicant -D"+wpaDriver()+" -B -i wlan0 -c /etc/wpa_supplicant.conf"));
                check_timer->start(1000);
                return;
                //            QProcess executeprocess(this);
                //            executeprocess.start();
            }


            len = sizeof(buf) - 1;
            if (ctrlRequest("PING", buf, &len) < 0) {
                LOG_INFO()<<"PING failed - trying to reconnect";
                if (openCtrlConnection(ctrl_iface) >= 0) {
                    setConnectedNetwork(0);
                    setWifiStatus(WIFIStat::STAT_DISCONNECTED);
                    LOG_INFO()<<"Reconnected successfully";
                }
                else
                    setWifiStatus(WIFIStat::STAT_NOTINITED);

            }

        }
        else
            m_timesToPing--;

        if(m_timesToUpdate<=0){
            m_timesToUpdate=5;
            if(wpsStarted()==false && wifiStatus()!=STAT_NOTINITED)
                getStatus();

        }
        else
            m_timesToUpdate--;

        if(m_timesToScan<=0){
            if(wifiStatus()==STAT_CONNECTED)
                m_timesToScan=30;
            else
                m_timesToScan=10;

            if(wpsStarted()==false && wifiStatus()!=STAT_CONNECTING && wifiStatus()!=STAT_NOTINITED){

                scan();
            }
        }
        else
            m_timesToScan--;


    }
    check_timer->start(1000);
}



void NetworkManager::start(){
    if (openCtrlConnection(ctrl_iface) < 0) {
        LOG_ERROR()<<"Failed to open control connection to  wpa_supplicant.";
        setWifiStatus(WIFIStat::STAT_NOTINITED);
    }
    else{
        setWifiStatus(WIFIStat::STAT_DISCONNECTED);


    }

    setStarted(true);
    getStatus();
    check_timer->start(1000);


}

int NetworkManager::openCtrlConnection(const char *ifname)
{
    char *cfile;
    int flen;
    char buf[2048], *pos, *pos2;
    size_t len;


    if (ifname) {
        if (ifname != ctrl_iface) {
            free(ctrl_iface);
            ctrl_iface = strdup(ifname);
        }
    } else {


        struct dirent *dent;
        DIR *dir = opendir(ctrl_iface_dir);
        free(ctrl_iface);
        ctrl_iface = NULL;
        if (dir) {
            while ((dent = readdir(dir))) {


                if (strcmp(dent->d_name, ".") == 0 ||
                        strcmp(dent->d_name, "..") == 0)
                    continue;
                LOG_INFO()<<"Selected interface "<<dent->d_name;
                ctrl_iface = strdup(dent->d_name);
                break;
            }
            closedir(dir);
        }

    }

    if (ctrl_iface == NULL) {

        return -1;
    }


    flen = strlen(ctrl_iface_dir) + strlen(ctrl_iface) + 2;
    cfile = (char *) malloc(flen);
    if (cfile == NULL)
        return -1;
    snprintf(cfile, flen, "%s/%s", ctrl_iface_dir, ctrl_iface);

    if (ctrl_conn) {
        wpa_ctrl_close(ctrl_conn);
        ctrl_conn = NULL;
    }

    if (monitor_conn) {
        delete msgNotifier;
        msgNotifier = NULL;
        wpa_ctrl_detach(monitor_conn);
        wpa_ctrl_close(monitor_conn);
        monitor_conn = NULL;
    }

    LOG_INFO()<<"Trying to connect to "<<QString(cfile);
    ctrl_conn = wpa_ctrl_open(cfile);
    if (ctrl_conn == NULL) {
        free(cfile);
        return -1;
    }
    monitor_conn = wpa_ctrl_open(cfile);
    free(cfile);
    if (monitor_conn == NULL) {
        wpa_ctrl_close(ctrl_conn);
        return -1;
    }
    if (wpa_ctrl_attach(monitor_conn)) {
        LOG_INFO()<<"Failed to attach to wpa_supplicant";
        wpa_ctrl_close(monitor_conn);
        monitor_conn = NULL;
        wpa_ctrl_close(ctrl_conn);
        ctrl_conn = NULL;
        return -1;
    }


    msgNotifier = new QSocketNotifier(wpa_ctrl_get_fd(monitor_conn),
                                      QSocketNotifier::Read, this);
    connect(msgNotifier, SIGNAL(activated(int)), SLOT(receiveMsgs()));


    //    adapterSelect->clear();
    //    adapterSelect->addItem(ctrl_iface);
    //    adapterSelect->setCurrentIndex(0);

    len = sizeof(buf) - 1;
    if (wpa_ctrl_request(ctrl_conn, "INTERFACES", 10, buf, &len, NULL) >=
            0) {
        buf[len] = '\0';
        pos = buf;
        while (*pos) {
            pos2 = strchr(pos, '\n');
            if (pos2)
                *pos2 = '\0';
            if (strcmp(pos, ctrl_iface) != 0){
                //   adapterSelect->addItem(pos);
                //qDebug()<<pos;
            }
            if (pos2)
                pos = pos2 + 1;
            else
                break;
        }
    }

    len = sizeof(buf) - 1;
    if (wpa_ctrl_request(ctrl_conn, "GET_CAPABILITY eap", 18, buf, &len,
                         NULL) >= 0) {
        buf[len] = '\0';

        QString res(buf);
        QStringList types = res.split(QChar(' '));
        bool wps = types.contains("WSC");
        if(wps)
            LOG_INFO()<<"WPS supported";
        //actionWPS->setEnabled(wps);
        //wpsTab->setEnabled(wps);
        //wpaguiTab->setTabEnabled(wpaguiTab->indexOf(wpsTab), wps);
    }

    return 0;
}

void NetworkManager::receiveMsgs()
{
    char buf[256];
    size_t len;

    while (monitor_conn && wpa_ctrl_pending(monitor_conn) > 0) {
        len = sizeof(buf) - 1;
        if (wpa_ctrl_recv(monitor_conn, buf, &len) == 0) {
            buf[len] = '\0';
            processMsg(buf);
        }
    }
}

void NetworkManager::scan(){


    char reply[10];
    size_t reply_len = sizeof(reply);



    qDebug()<<"Scanning..";

    waitresults_timer->start(20000);



    ctrlRequest("SCAN", reply, &reply_len);


}

//int NetworkManager::getNetworksAvailable()
//{

//    return m_availableNetworks->getNetworksAvailable();

//}

void NetworkManager::startWPS()
{

    qDebug()<<"Start wps called";
    char reply[20];
    size_t reply_len = sizeof(reply);

    setWpsStarted(true);
    if (ctrlRequest("WPS_PBC", reply, &reply_len) < 0)
        return;
}

int NetworkManager::setNetworkParam(int id, const char *field,
                                    const char *value, bool quote){
    char reply[10], cmd[256];
    size_t reply_len;
    snprintf(cmd, sizeof(cmd), "SET_NETWORK %d %s %s%s%s",
             id, field, quote ? "\"" : "", value, quote ? "\"" : "");
    reply_len = sizeof(reply);
    ctrlRequest(cmd, reply, &reply_len);
    return strncmp(reply, "OK", 2) == 0 ? 0 : -1;
}

void NetworkManager::connectNetwork(int index)
{
    NetworkInfo* net=m_availableNetworks->getAt(index);




    if(net!=nullptr){
        LOG_INFO()<<"Connecting to SSID:"<<net->ssid();

        if(net->networkStatus()!=NetworkInfo::NET_CONNECTED){
            if(net->isConfigured()==false){

                net->setNetworkStatus(NetworkInfo::NET_CONNECTING);

                int auth = net->auth();

                char reply[10], cmd[256];
                size_t reply_len;
                int id;
                memset(reply, 0, sizeof(reply));
                reply_len = sizeof(reply) - 1;




                int psklen =net->passKey().length();


                qDebug()<<"psk len:"<<psklen;

                if (auth == NetworkInfo::AUTH_WPA_PSK || auth == NetworkInfo::AUTH_WPA2_PSK) {
                    if (psklen < 8 || psklen > 64) {
                        qDebug()<<"WPA-PSK requires a passphrase of 8 to 63 characters or 64 hex digit PSK";
                        return;
                    }
                }

                ctrlRequest("ADD_NETWORK", reply, &reply_len);
                if (reply[0] == 'F') {
                    qDebug()<<"Failed to add network to wpa_supplicant\n configuration.";
                    return;
                }
                id = atoi(reply);
                setNetworkParam(id, "ssid", net->ssid().toLocal8Bit().constData(),true);
                const char *key_mgmt = NULL, *proto = NULL, *pairwise = NULL;
                switch (auth) {
                case NetworkInfo::AUTH_NONE_OPEN:
                case NetworkInfo::AUTH_NONE_WEP:
                case NetworkInfo::AUTH_NONE_WEP_SHARED:
                    key_mgmt = "NONE";
                    break;
                case NetworkInfo::AUTH_IEEE8021X:
                    key_mgmt = "IEEE8021X";
                    break;
                case NetworkInfo::AUTH_WPA_PSK:
                    key_mgmt = "WPA-PSK";
                    proto = "WPA";
                    break;
                case NetworkInfo::AUTH_WPA_EAP:
                    key_mgmt = "WPA-EAP";
                    proto = "WPA";
                    break;
                case NetworkInfo::AUTH_WPA2_PSK:
                    key_mgmt = "WPA-PSK";
                    proto = "WPA2";
                    break;
                case NetworkInfo::AUTH_WPA2_EAP:
                    key_mgmt = "WPA-EAP";
                    proto = "WPA2";
                    break;
                }

                if (auth == NetworkInfo::AUTH_NONE_WEP_SHARED)
                    setNetworkParam(id, "auth_alg", "SHARED", false);
                else
                    setNetworkParam(id, "auth_alg", "OPEN", false);

                if (auth == NetworkInfo::AUTH_WPA_PSK || auth == NetworkInfo::AUTH_WPA_EAP ||
                        auth == NetworkInfo::AUTH_WPA2_PSK || auth == NetworkInfo::AUTH_WPA2_EAP) {
                    //                    int encr = encrSelect->currentIndex();
                    //                    if (encr == 0)
                    //                        pairwise = "TKIP";
                    //                    else
                    //                        pairwise = "CCMP";
                }

                if (auth == NetworkInfo::AUTH_WPA_PSK || auth == NetworkInfo::AUTH_WPA_EAP ||
                        auth == NetworkInfo::AUTH_WPA2_PSK || auth == NetworkInfo::AUTH_WPA2_EAP) {
                    int encr = net->encr();
                    if (encr == NetworkInfo::ENCR_TKIP)
                        pairwise = "TKIP";
                    else
                        pairwise = "CCMP";
                }

                if (proto)
                    setNetworkParam(id, "proto", proto, false);
                if (key_mgmt)
                    setNetworkParam(id, "key_mgmt", key_mgmt, false);
                if (pairwise) {
                    setNetworkParam(id, "pairwise", pairwise, false);
                    setNetworkParam(id, "group", "TKIP CCMP WEP104 WEP40", false);
                }



                if (auth==NetworkInfo::AUTH_WPA_PSK || auth == NetworkInfo::AUTH_WPA2_PSK){

                    setNetworkParam(id, "psk",net->passKey().toLocal8Bit().constData(),psklen != 64);
                }


                //TODO
                setNetworkParam(id, "phase2", "NULL", false);
                setNetworkParam(id, "identity", "NULL", false);
                setNetworkParam(id, "id_str", "NULL", false);
                //setNetworkParam(id, "priority", prio.toLocal8Bit().constData(),false);


                snprintf(cmd, sizeof(cmd), "ENABLE_NETWORK %d", id);
                reply_len = sizeof(reply);
                ctrlRequest(cmd, reply, &reply_len);
                if (strncmp(reply, "OK", 2) != 0) {
                    LOG_ERROR()<<"Failed to enable network in wpa_supplicant configuration.";
                    /* Network was added, so continue anyway */
                }
                ctrlRequest("SAVE_CONFIG", reply, &reply_len);


            }
            else{
                char reply[10], cmd[256];
                size_t reply_len;


                snprintf(cmd, sizeof(cmd), "DISABLE_NETWORK %d", net->networkID());
                reply_len = sizeof(reply);
                ctrlRequest(cmd, reply, &reply_len);

                snprintf(cmd, sizeof(cmd), "ENABLE_NETWORK %d", net->networkID());
                reply_len = sizeof(reply);
                ctrlRequest(cmd, reply, &reply_len);


            }
        }
    }

}


void NetworkManager::removeNetwork(int index)
{
    char reply[10], cmd[256];
    size_t reply_len;

    NetworkInfo* net=m_availableNetworks->getAt(index);

    if(net!=nullptr){

        net->setIsConfigured(false);
        net->setNetworkStatus(NetworkInfo::NET_DISCONNECTED);
        qDebug()<<"Removing net id:"<<net->networkID();
        snprintf(cmd, sizeof(cmd), "REMOVE_NETWORK %d", net->networkID());
        reply_len = sizeof(reply);
        ctrlRequest(cmd, reply, &reply_len);
        if (strncmp(reply, "OK", 2) != 0) {
            qDebug()<<"Failed to remove network from wpa_supplicant configuration.";
        } else {
            ctrlRequest("SAVE_CONFIG", reply, &reply_len);
            getStatus();
        }

    }
}




int NetworkManager::ctrlRequest(const char *cmd, char *buf, size_t *buflen)
{
    int ret;

    if (ctrl_conn == NULL)
        return -3;
    ret = wpa_ctrl_request(ctrl_conn, cmd, strlen(cmd), buf, buflen, NULL);
    if (ret == -2)
        LOG_ERROR()<<cmd<<"command timed out.";
    else if (ret < 0)
        LOG_ERROR()<<cmd<< "command failed -"<<ret;

    return ret;
}



static int str_match(const char *a, const char *b)
{
    return strncmp(a, b, strlen(b)) == 0;
}




//bool NetworkManager::addNetwork(QString bssid,QString ssid){

//    for (int i = 0; i < m_networks.length(); ++i) {
//        if(m_networks.at(i)->ssid()==ssid){
//            return false;
//        }
//    }



//    m_networks.append(new NetworkInfo(this,bssid,ssid));

//    return true;

//}


bool exists (QString first, QString second)
{ return ( first==second); }

template <typename T>
T getAt(std::list<T> getlist,int pos){
    typename  std::list<T>::iterator it = getlist.begin();
    std::advance(it, pos);
    return *it;
}


static int key_value_isset(const char *reply, size_t reply_len)
{
    return reply_len > 0 && (reply_len < 4 || memcmp(reply, "FAIL", 4) != 0);
}

void NetworkManager::getConfiguratedNetworks(){
    char buf[2048];
    size_t len;

    if(wpsStarted()) return;
    QString connected_ip;



    len = sizeof(buf) - 1;
    if (ctrl_conn == NULL || ctrlRequest("LIST_NETWORKS", buf, &len) < 0) {

        LOG_ERROR()<<"Could not get list_networks from wpa_supplicant";
    }
    else{
        buf[len] = '\0';

        QString networks(buf);

        QList<QString> networks_splited=networks.split('\n');

        for (int i = 1; i < networks_splited.length(); ++i) {

            QString network_info=networks_splited.at(i);

            QList<QString> info_splited=network_info.split('\t');

            //            for (int j = 0; j < info_splited.length(); ++j) {
            //  qDebug()<<info_splited;
            //            }

            if(info_splited.length()>2){
                int net_id=info_splited.at(0).toInt();

                QString netssid=info_splited.at(1);

                NetworkInfo* net=availableNetworks()->getBySSID(netssid);
                if(net!=nullptr){
                    net->setIsConfigured(true);
                    net->setNetworkID(net_id);

                    char reply[1024], cmd[256], *pos;
                    size_t reply_len;
                    int res;

                    snprintf(cmd, sizeof(cmd), "GET_NETWORK %d psk", net_id);
                    reply_len = sizeof(reply) - 1;
                    res=ctrlRequest(cmd, reply, &reply_len);

                    reply[reply_len] = '\0';


                    if (res >= 0 && reply_len >= 2 && reply[0] == '"') {
                        reply[reply_len] = '\0';
                        pos = strchr(reply + 1, '"');
                        if (pos)
                            *pos = '\0';
                        //net->setStoredKey(reply + 1);


                    } else if (res >= 0 && key_value_isset(reply, reply_len)) {
                        //net->setStoredKey("");

                    }
                }
            }
        }


    }
}

void NetworkManager::updateResults(){


    char reply[2048];
    size_t reply_len;
    int index;
    char cmd[20];

    index = 0;


    bool globalwpsavailable=false;

    m_availableNetworks->MarkRemoved();
//qDebug()<<"getting results";



    while (true) {
        bool wpsavailable=false;
        snprintf(cmd, sizeof(cmd), "BSS %d", index++);
        if (index > 1000)
            break;

        reply_len = sizeof(reply) - 1;

        if (ctrlRequest(cmd, reply, &reply_len) < 0)
            break;
        reply[reply_len] = '\0';


        QString bss(reply);
        if (bss.isEmpty() || bss.startsWith("FAIL"))
            break;

        QString ssid, bssid, freq, signal, flags;



        QStringList lines = bss.split(QRegExp("\\n"));

        for (QStringList::Iterator it = lines.begin();
             it != lines.end(); it++) {
            int pos = (*it).indexOf('=') + 1;
            if (pos < 1)
                continue;


            if ((*it).startsWith("bssid="))
                bssid = (*it).mid(pos);
            else if ((*it).startsWith("freq="))
                freq = (*it).mid(pos);
            else if ((*it).startsWith("level="))
                signal = (*it).mid(pos);
            else if ((*it).startsWith("flags="))
                flags = (*it).mid(pos);
            else if ((*it).startsWith("ssid="))
                ssid = (*it).mid(pos);
        }


        if(ssid!="\\x00"){
            NetworkInfo::NetAuth auth;
            NetworkInfo::NetEncr encr;

            if (flags.indexOf("[WPA2-EAP") >= 0)
                auth = NetworkInfo::NetAuth::AUTH_WPA2_EAP;
            else if (flags.indexOf("[WPA-EAP") >= 0)
                auth = NetworkInfo::NetAuth::AUTH_WPA_EAP;
            else if (flags.indexOf("[WPA2-PSK") >= 0)
                auth = NetworkInfo::NetAuth::AUTH_WPA2_PSK;
            else if (flags.indexOf("[WPA-PSK") >= 0)
                auth = NetworkInfo::NetAuth::AUTH_WPA_PSK;
            else
                auth = NetworkInfo::NetAuth::AUTH_NONE_OPEN;


            if (flags.indexOf("WEP") >= 0) {

                if (auth == NetworkInfo::NetAuth::AUTH_NONE_OPEN)
                    auth = NetworkInfo::NetAuth::AUTH_NONE_WEP;
            }

            if (flags.indexOf("WPS") >= 0) {

                wpsavailable=true;
                globalwpsavailable=true;
            }

            if (flags.indexOf("-CCMP") >= 0)
                encr = NetworkInfo::ENCR_CCMP;
            else if (flags.indexOf("-TKIP") >= 0)
                encr = NetworkInfo::ENCR_TKIP;
            else if (flags.indexOf("WEP") >= 0) {
                encr = NetworkInfo::ENCR_CCMP;

            } else
                encr = NetworkInfo::ENCR_TKIP;


            //if(m_availableNetworks->getBySSID("ssid")->networkSignal())
            NetworkInfo* net= m_availableNetworks->SetNetwork(ssid,bssid,auth,encr,signal.toInt(),wpsavailable,true);

            //            char buf[2048];
            //            size_t len;
            //            len = sizeof(buf) - 1;
            //            QString cmd("bssid "+net->ssid()+" "+net->bssid());
            //            if (ctrl_conn == NULL || ctrlRequest(cmd.toStdString().c_str(), buf, &len) < 0) {

            //                qDebug()<<"Could not set bssid ";
            //            }
            //            else{

            //            }


        }

        if (bssid.isEmpty())
            break;



    }




    getConfiguratedNetworks();

    setWpsNetworksAvailable(globalwpsavailable);

    m_availableNetworks->ValidateRemovedNetworks();
    setNetworksAvailableCount(m_availableNetworks->rowCount(QModelIndex()));

}



void NetworkManager::processMsg(char *msg)
{


    char *pos = msg, *pos2;
    int priority = 2;

    //   bool wpsavailable=false;

    if (*pos == '<') {
        /* skip priority */
        pos++;
        priority = atoi(pos);
        pos = strchr(pos, '>');
        if (pos)
            pos++;
        else
            pos = msg;
    }


    //qDebug()<<"Proceesing message:"<<msg;

    // WpaMsg wm(pos, priority);
    //    if (eh)
    //        eh->addEvent(wm);
    //    if (peers)
    //        peers->event_notify(wm);
    //    msgs.append(wm);
    //    while (msgs.count() > 100)
    //        msgs.pop_front();

    /* Update last message with truncated version of the event */
    if (strncmp(pos, "CTRL-", 5) == 0) {
        pos2 = strchr(pos, str_match(pos, WPA_CTRL_REQ) ? ':' : ' ');
        if (pos2)
            pos2++;
        else
            pos2 = pos;
    } else
        pos2 = pos;
    QString lastmsg = pos2;
    lastmsg.truncate(40);
    // textLastMessage->setText(lastmsg);

    //pingsToStatusUpdate = 0;
    //networkMayHaveChanged = true;

    /*if (str_match(pos, WPA_CTRL_REQ))
        processCtrlReq(pos + strlen(WPA_CTRL_REQ));
    else */if (str_match(pos, WPA_EVENT_SCAN_RESULTS)){
        waitresults_timer->stop();
        updateResults();
        setScanning(false);
    }
    else if (str_match(pos, WPA_EVENT_NETWORK_NOT_FOUND)) {
        setWifiStatus(WIFIStat::STAT_DISCONNECTED);
    }
    else if (str_match(pos, WPS_EVENT_AP_AVAILABLE)) {

        //        wpsavailable=true;

    }
    else if (str_match(pos, WPA_EVENT_SCAN_STARTED)) {
        qDebug()<<"scan started";
        setScanning(true);

        waitresults_timer->start();

        //waitresults_timer->stop();
    }
    else if (str_match(pos, WPA_EVENT_SCAN_FAILED)) {
        qDebug()<<"scan failed";

        setScanning(false);
    }
    else if (str_match(pos, WPA_EVENT_DISCONNECTED)){
        setWifiStatus(NetworkManager::STAT_DISCONNECTED);
        setConnectedNetwork(0);
    }
    else if (str_match(pos, WPA_EVENT_CONNECTED)) {
        //        showTrayMessage(QSystemTrayIcon::Information, 3,
        //                tr("Connection to network established."));
        //        QTimer::singleShot(5 * 1000, this, SLOT(showTrayStatus()));
        //        stopWpsRun(true);
        setWpsStarted(false);
        getStatus();


        qDebug()<<"Wifi connected";
    } else if (str_match(pos, WPS_EVENT_AP_AVAILABLE_PBC)) {
        //        wpsStatusText->setText(tr("WPS AP in active PBC mode found"));
        //        if (textStatus->text() == "INACTIVE" ||
        //            textStatus->text() == "DISCONNECTED")
        //            wpaguiTab->setCurrentWidget(wpsTab);
        qDebug()<<"WPS AP active... Press the PBC button on the ";

    } else if (str_match(pos, WPS_EVENT_AP_AVAILABLE_PIN)) {
        //        wpsStatusText->setText(tr("WPS AP with recently selected "
        //                      "registrar"));
        //        if (textStatus->text() == "INACTIVE" ||
        //            textStatus->text() == "DISCONNECTED")
        //            wpaguiTab->setCurrentWidget(wpsTab);
    } else if (str_match(pos, WPS_EVENT_AP_AVAILABLE_AUTH)) {
        //        showTrayMessage(QSystemTrayIcon::Information, 3,
        qDebug()<<"Wi-Fi Protected Setup (WPS) AP\n indicating this client is authorized.";
        //        wpsStatusText->setText("WPS AP indicating this client is "
        //                       "authorized");
        //        if (textStatus->text() == "INACTIVE" ||
        //            textStatus->text() == "DISCONNECTED")
        //            wpaguiTab->setCurrentWidget(wpsTab);
    } else if (str_match(pos, WPS_EVENT_AP_AVAILABLE)) {
        qDebug()<<"WPS AP detected";
    } else if (str_match(pos, WPS_EVENT_OVERLAP)) {
        qDebug()<<"PBC mode overlap detected";
        //        wpsInstructions->setText(tr("More than one AP is currently in "
        //                        "active WPS PBC mode. Wait couple "
        //                        "of minutes and try again"));
        //        wpaguiTab->setCurrentWidget(wpsTab);
    } else if (str_match(pos, WPS_EVENT_CRED_RECEIVED)) {
        qDebug()<<"Network configuration received";
        //        wpaguiTab->setCurrentWidget(wpsTab);
    } else if (str_match(pos, WPA_EVENT_EAP_METHOD)) {
        if (strstr(pos, "(WSC)"))
            qDebug()<<"Registration started";
    } else if (str_match(pos, WPS_EVENT_M2D)) {
        //        wpsStatusText->setText(tr("Registrar does not yet know PIN"));
    } else if (str_match(pos, WPS_EVENT_FAIL) || str_match(pos, WPS_EVENT_TIMEOUT)) {
        qDebug()<<"Registration failed";
        setWpsStarted(false);

    } else if (str_match(pos, WPS_EVENT_ACTIVE)) {
        qDebug()<<"WPS Initied";
        setWpsStarted(false);
        waitresults_timer->stop();

    } else if (str_match(pos, WPS_EVENT_SUCCESS)) {
        qDebug()<<"Registration succeeded";
        setWpsStarted(false);
    }
    else if (str_match(pos, WPA_EVENT_TEMP_DISABLED)) {

        QList<QString> statusSplited=QString(pos).split(' ');

        QString ssid;
        QString failureReason="";

        foreach (QString status, statusSplited) {
            if(status.contains("ssid=")){
                ssid=status.split('=').at(1);
                ssid=ssid.replace("\"","");

            }

            if(status.contains("reason=")){
                failureReason=status.split('=').at(1);
                failureReason=failureReason.replace("\"","");
            }

        }



        NetworkInfo* net =m_availableNetworks->getBySSID(ssid);

        qDebug()<<"net:"<<net;

        if(net!=nullptr){
            if(failureReason=="WRONG_KEY"){
                net->setNetworkRejectReason(NetworkInfo::REJECT_WRONGKEY);

            }
            if(failureReason=="CONN_FAILED"){
                net->setNetworkRejectReason(NetworkInfo::REJECT_CONNFAILED);

            }
            // TODO: do some actions to reconnect
            net->setNetworkStatus(NetworkInfo::NET_REJECTED);
        }




    }

    else if (str_match(pos, WPA_EVENT_REENABLED)) {

        QList<QString> statusSplited=QString(pos).split(' ');

        QString ssid;


        foreach (QString status, statusSplited) {

        }

        // qDebug()<<"WPA_EVENT_REENABLED"<<pos;

    }

}
