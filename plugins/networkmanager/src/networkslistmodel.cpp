#include "networkslistmodel.h"

NetworksListModel::NetworksListModel()
{

}




void NetworksListModel::MarkRemoved(){
    for (int i = 0; i < m_networks.length(); ++i) {
        m_networks.at(i)->setRemoved(true);
        m_networks.at(i)->setIsConfigured(false);
    }


}


void NetworksListModel::ValidateRemovedNetworks(){


    foreach (NetworkInfo* network, m_networks) {


        if(network->removed()){

            int postoremove=m_networks.indexOf(network);

            if(postoremove>=0 && postoremove<m_networks.length()){
                removeRows(postoremove,1,QModelIndex());
            }
        }
    }
    //    QMutableListIterator<NetworkInfo *> i(m_networks);
    //    while (i.hasNext()) {
    //        NetworkInfo* network=i.next();
    //        if(network->removed()){
    //            int pos=m_networks.indexOf(network);
    //            RemoveNetwork(network,pos);
    //        }
    //    }

    //    QList<int> positions_to_remove;

    //    for (int i = 0; i < m_networks.length(); ++i) {
    //        if(m_networks.at(i)->removed()){
    //            positions_to_remove.append(i);
    //        }
    //    }

    //    for (int i = 0; i < positions_to_remove.length(); ++i) {
    //        RemoveNetwork(0,positions_to_remove.at(i));
    //    }


    //m_networks.toStdList().remove_if()

}


//void NetworksListModel::RemoveNetworkAt(int pos)
//{




//    beginRemoveRows(QModelIndex(),pos,pos);   // kindly provided by superclass
//    // object creation based on params...


//    m_networks.removeAt(pos);

//    qDebug()<<"Removing at pos:"<<pos;

//    endRemoveRows();    // kindly provided by superclass

//}


void NetworksListModel::SetNetwork(NetworkInfo *network)
{


    beginInsertRows(QModelIndex(), rowCount(QModelIndex()),rowCount(QModelIndex()));   // kindly provided by superclass
    // object creation based on params...
    m_networks.append(network);
    endInsertRows();                                          // kindly provided by superclass

}

int NetworksListModel::getNetworksAvailable()
{

    return m_networks.length();

}






NetworkInfo* NetworksListModel::SetNetwork(QString ssid,QString bssid,NetworkInfo::NetAuth auth,NetworkInfo::NetEncr encr, int signal,bool wpsavailable,bool MarkValid)
{

    for (int i = 0; i < m_networks.length(); ++i) {
        NetworkInfo* net=m_networks.at(i);
        if(net->ssid()==ssid){

            if(net->signalLevel()<signal){
                net->setNetworkSignal(signal);
                net->setBssid(bssid);
            }
            qDebug()<<net->ssid()<<": Signal:"<<net->signalLevel();
            if(MarkValid)
                net->setRemoved(false);

            return net;
        }
    }
    beginInsertRows(QModelIndex(), rowCount(QModelIndex()),rowCount(QModelIndex()));   // kindly provided by superclass
    // object creation based on params...
    NetworkInfo* newnetwork=new NetworkInfo(this,bssid,ssid,auth,encr,signal,wpsavailable);
    m_networks.append(newnetwork);
    endInsertRows();                                          // kindly provided by superclass

    qDebug()<<"Network added:"<<ssid;

    return newnetwork;
}

void NetworksListModel::RemoveNetworkSSID(QString ssid)
{
    beginRemoveRows(QModelIndex(), 2,2);   // kindly provided by superclass
    // object creation based on params...
    m_networks.removeAt(2);
    endRemoveRows();                                          // kindly provided by superclass


}

int NetworksListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_networks.count();
}


NetworkInfo* NetworksListModel::getAt(int index){
    if(index>=0 && index<m_networks.length())
        return m_networks.at(index);

    return nullptr;
}

QVariant NetworksListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();


    if (index.row() >= m_networks.size())
        return QVariant();

    if (role == Qt::DisplayRole){
        NetworkInfo* network=m_networks.at(index.row());
        return QVariant::fromValue(network);
    }
    //    else if(role==10){
    //        NetworkInfo* network=m_networks.at(index.row());
    //        retutn

    //    }
    else
        return QVariant();
}


NetworkInfo* NetworksListModel::getBySSID(QString ssid){

    foreach (NetworkInfo* network, m_networks) {

        if(network->ssid()==ssid){
            return network;
        }
    }


    return nullptr;


}

bool NetworksListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(QModelIndex(), row, count+row-1);

    NetworkInfo* net=m_networks.takeAt(row);

    qDebug()<<"Removing network:"+net->ssid()<<" at pos:"<<row;
    if(net)
        net->deleteLater();

    endRemoveRows();


    return true;
}
