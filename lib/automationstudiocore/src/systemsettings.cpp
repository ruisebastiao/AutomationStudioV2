#include "systemsettings.h"
#include "QDebug"



SystemSettings::SystemSettings(QObject *parent):
    QObject(parent)
{


//    manager= new QNetworkConfigurationManager(this);

//    qDebug()<<manager->capabilities();

//    QNetworkConfiguration config =  manager->defaultConfiguration();//manager.configurationFromIdentifier("DefaultNetworkConfiguration");



//    QNetworkSession *networkSession = new QNetworkSession(config, this);
//    connect(networkSession,SIGNAL(stateChanged(QNetworkSession::State)),this,SLOT(NetworkChanged(QNetworkSession::State)));
//    networkSession->open(0);


}

void SystemSettings::NetworkChanged(QNetworkSession::State state){

    qDebug()<<"Network State changed:"<<state;
    emit networkStateChanged(state);
}
