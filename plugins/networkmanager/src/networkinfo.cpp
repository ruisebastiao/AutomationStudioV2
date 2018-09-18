#include "networkinfo.h"

NetworkInfo::NetworkInfo(QObject *parent, QString _bssid, QString _ssid, NetAuth _auth,NetEncr _encr, int _networkSignal, bool wpsavailable) : QObject(parent)
{
    setBssid(_bssid);
    setSsid(_ssid);
    setNetworkSignal(_networkSignal);
    setAuth(_auth);
    setEncr(_encr);
    setWpsAvailable(wpsavailable);
}
