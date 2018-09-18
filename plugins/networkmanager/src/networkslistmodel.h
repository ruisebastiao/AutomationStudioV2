#ifndef NETWORKSLISTMODEL_H
#define NETWORKSLISTMODEL_H

#include "networkinfo.h"
#include "QDebug"

#include <QAbstractListModel>
#include <QObject>

class NetworksListModel : public QAbstractListModel
{

    Q_OBJECT

public:
    NetworksListModel();

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    void SetNetwork(NetworkInfo* network);
    int getNetworksAvailable();

private:
    QList<NetworkInfo*> m_networks;
    // QAbstractItemModel interface
public:

    void RemoveNetworkSSID(QString ssid);
    NetworkInfo *SetNetwork(QString ssid, QString bssid, NetworkInfo::NetAuth auth, NetworkInfo::NetEncr encr, int signal, bool wpsavailable, bool MarkValid);
    void MarkRemoved();
    void ValidateRemovedNetworks();
    //void RemoveNetworkAt(int pos);
    Q_INVOKABLE NetworkInfo *getAt(int index);
    Q_INVOKABLE NetworkInfo *getBySSID(QString ssid);

    // QAbstractItemModel interface
public:
    bool removeRows(int row, int count, const QModelIndex &parent);
};

#endif // NETWORKSLISTMODEL_H
