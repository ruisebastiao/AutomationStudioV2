#include "appupdater.h"
#include "Logger.h"
#include "version.h"

#include <QDir>
#include <QFileInfo>
#include <qthread.h>
#include <QtConcurrent>


AppUpdater::AppUpdater(QObject *parent) : QObject(parent)
{
    m_zipper= new ZipManager(this);
    m_utilities=new as::Utilities(this);
}

void AppUpdater::doUpdate(QString release)
{
    LOG_INFO()<<"Updating::"<<release << "::" << m_downloadPath << "::"<<m_serverUrl;



    QString currVersion(RELEASEVERS);

    m_utilities->executeCommand("rm *.zip",true,QDir::currentPath());

    setUpdateStatus("Backup/Compressing current release");
    setCompressing(true);

    as::Utilities::NonBlockingExec([&](){
        m_utilities->executeCommand("zip -r release"+currVersion+".zip ./",true,QDir::currentPath(),true);
    });


    setCompressing(false);

    QString saveDir="release/";

    QDir(saveDir).removeRecursively();

    if(QDir(saveDir).exists()==false){
        QDir().mkdir(saveDir);
    }


    QString saveTo=saveDir+"release.zip";


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

    if (currentDownload->error()) {
        // download failed
        LOG_INFO("Failed to download:"+currentDownload->errorString());
    } else {
        LOG_INFO("Succeeded");
        //TODO download ok proceed to update

        QString saveDir="release/";
        QDir::setCurrent(saveDir);

        setUpdateStatus("Download finished");



        setUpdateStatus("Extracting");

        m_utilities->executeCommand("unzip -l release.zip",true,QDir::currentPath());



        //m_zipper->Unzip("release.zip");

        QFile::remove("release.zip");




        m_utilities->executeCommand("mv * ../",true,QDir::currentPath());

        setUpdateStatus("Done, rebooting");

        emit updateDone();


    }

    currentDownload->deleteLater();

}

void AppUpdater::downloadReadyRead()
{
    m_output.write(currentDownload->readAll());
}
