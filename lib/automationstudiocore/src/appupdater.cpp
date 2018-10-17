#include "appupdater.h"
#include "Logger.h"

#include <QFileInfo>

AppUpdater::AppUpdater(QObject *parent) : QObject(parent)
{

}

void AppUpdater::doUpdate(QString release)
{
    LOG_INFO()<<"Updating::"<<release << "::" << m_downloadPath << "::"<<m_serverUrl;




    QString saveTo="release.tar.gz";

    QFileInfo check_file(saveTo);


    m_output.setFileName(saveTo);

    if (!m_output.open(QIODevice::WriteOnly)) {



        LOG_INFO("Error saving download file");
        m_output.close();
        return;                 // skip this download
    }


    QUrl url("http://"+m_serverUrl+"/"+m_downloadPath+"/"+release);
    LOG_INFO("Downloading from url:"+QString(url.toEncoded()));


    QNetworkRequest request(url);
    currentDownload = manager.get(request);
    connect(currentDownload, SIGNAL(downloadProgress(qint64,qint64)),
            SLOT(downloadProgress(qint64,qint64)));
    connect(currentDownload, SIGNAL(finished()),
            SLOT(downloadFinished()));
    connect(currentDownload, SIGNAL(readyRead()),
            SLOT(downloadReadyRead()));

    // prepare the output



}

void AppUpdater::Serialize(QJsonObject &json)
{
    JsonSerializable::Serialize(json,this);
}

void AppUpdater::DeSerialize(QJsonObject &json)
{
    JsonSerializable::DeSerialize(json,this);

}

void AppUpdater::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    if(bytesTotal<=0) return;
    double progress=((double)bytesReceived/(double)bytesTotal)*100.0;

    qDebug()<<progress;
    emit downloadProgressChanged(progress);

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


        setUpdateStatusChanged("Download finished");


        //qApp->exit(1337);
        emit updateDone();


    }

    currentDownload->deleteLater();

}

void AppUpdater::downloadReadyRead()
{
    m_output.write(currentDownload->readAll());
}
