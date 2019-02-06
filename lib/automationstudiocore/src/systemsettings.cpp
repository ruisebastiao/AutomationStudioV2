#include "systemsettings.h"
#include "QDebug"

#include <QHostInfo>



SystemSettings::SystemSettings(QObject *parent):
    QObject(parent)
{


    //    manager= new QNetworkConfigurationManager(this);

    //    qDebug()<<manager->capabilities();

    //    QNetworkConfiguration config =  manager->defaultConfiguration();//manager.configurationFromIdentifier("DefaultNetworkConfiguration");



    //    QNetworkSession *networkSession = new QNetworkSession(config, this);
    //    connect(networkSession,SIGNAL(stateChanged(QNetworkSession::State)),this,SLOT(NetworkChanged(QNetworkSession::State)));
    //    networkSession->open(0);

    setHostname(QHostInfo::localHostName());



#ifdef RPI
    m_boardInfo="RPI";
    emit boardInfoChanged("RPI");
#endif


}

void SystemSettings::setNewHostName(QString name)
{
    if(name!=m_hostname){
#ifdef RPI
        QProcess procWriteProject;

        procWriteProject.setStandardOutputFile("/etc/hostname");
        procWriteProject.start("echo "+name);
        procWriteProject.waitForFinished();

        m_hostname=name;
#endif
    }
    emit hostnameChanged(m_hostname);
}

void SystemSettings::NetworkChanged(QNetworkSession::State state){

    qDebug()<<"Network State changed:"<<state;
    emit networkStateChanged(state);
}
