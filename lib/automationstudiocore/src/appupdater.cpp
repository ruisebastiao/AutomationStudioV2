#include "appupdater.h"
#include "Logger.h"
#include "version.h"

#include <QFileInfo>
#include <qthread.h>
#include <QtConcurrent>


AppUpdater::AppUpdater(QObject *parent) : QObject(parent)
{

    m_utilities=new as::Utilities(this);

    updatedir=QDir(QDir::currentPath());


    updatedir.cdUp();
    if(updatedir.exists("releases")==false){
        updatedir.mkdir("releases");
    }
    updatedir.cd("releases");
    if(updatedir.exists("newrelease")==false){
        updatedir.mkdir("newrelease");
    }

    


}

void AppUpdater::doUpdate(QString release)
{
    LOG_INFO()<<"Updating::"<<release << "::" << m_downloadPath << "::"<<m_serverUrl;

    QString currVersion(RELEASEVERS);


    //    setUpdateStatus("Backup/Compressing current release");
    //    setCompressing(true);

    ////    QDir::setCurrent(targetdir.absolutePath());

    ////    as::Utilities::NonBlockingExec([&](){
    ////        QString currVersion(RELEASEVERS);
    ////        as::Utilities utils;
    ////        QString cmd("zip -r "+updatedir.absolutePath()+"/release-"+currVersion+".zip ./*");

    ////        utils.executeCommand(cmd,true,targetdir.absolutePath(),true,false);
    ////    });


    ////    QThread::msleep(500);
    //    setCompressing(false);


    QString saveTo=updatedir.absolutePath()+"/newrelease.zip";


    m_output.setFileName(saveTo);

    if (!m_output.open(QIODevice::WriteOnly)) {



        LOG_INFO("Error saving download file");
        m_output.close();
        return;                 // skip this download
    }


    QUrl url(m_serverUrl+"/"+m_downloadPath+"/"+release);
    LOG_INFO("Downloading from url:"+QString(url.toEncoded()));

    setUpdateStatus("Downloading update:"+release);

    QNetworkRequest request(url);
    currentDownload = manager.get(request);
    connect(currentDownload, SIGNAL(downloadProgress(qint64,qint64)),
            SLOT(currentDownloadProgress(qint64,qint64)));
    connect(currentDownload, SIGNAL(finished()),
            SLOT(downloadFinished()));
    connect(currentDownload, SIGNAL(readyRead()),
            SLOT(downloadReadyRead()));




}

void AppUpdater::Serialize(QJsonObject &json)
{
    JsonSerializable::Serialize(json,this);
}

void AppUpdater::DeSerialize(QJsonObject &json)
{
    JsonSerializable::DeSerialize(json,this);

}

void AppUpdater::currentDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    if(bytesTotal<=0) return;
    double progress=(double)bytesReceived/(double)bytesTotal;

    qDebug()<<progress*100;
    setDownloadProgress(progress);

}

void AppUpdater::downloadFinished()
{
    //    progressBar.clear();
    m_output.close();

    setUpdateStatus("Download finished");

    if (currentDownload->error()) {
        // download failed
        LOG_INFO("Failed to download:"+currentDownload->errorString());
    } else {
        LOG_INFO("Download succeeded");
        //TODO download ok proceed to update



        updatedir.cd("newrelease");


        updatedir.removeRecursively();

        updatedir.cdUp();


        setUpdateStatus("Extracting release");

        QDir::setCurrent(updatedir.absolutePath());
        as::Utilities utils;

        utils.executeCommand("unzip newrelease.zip -d newrelease",true,updatedir.absolutePath(),true,false);



        //        m_utilities->executeCommand("mv * "+targetdir.absolutePath(),true,updatedir.absolutePath()+"newrelease",true,true);

        //        setUpdateStatus("Done, rebooting");

        //        emit updateDone();




        setUpdateStatus("Starting update");

        setCompressing(true);
        updatedir.cd("newrelease");
        QDir::setCurrent(updatedir.absolutePath());


        as::Utilities::NonBlockingExec([&](){
            QString currVersion(RELEASEVERS);
            as::Utilities utils;
            QString cmd("./installer.sh");

            utils.executeCommand(cmd,true,updatedir.absolutePath(),true,false,[&](QString out){
                setUpdateStatus(out);
            }
            );
        });

        setCompressing(false);
        setUpdateStatus("Finished update, restarting");
        emit updateDone();
    }

    currentDownload->deleteLater();

}

void AppUpdater::downloadReadyRead()
{
    m_output.write(currentDownload->readAll());
}
