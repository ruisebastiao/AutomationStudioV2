#include "appupdater.h"
#include "Logger.h"
#include "version.h"

#include <QFileInfo>
#include <qthread.h>
#include <QtConcurrent>
#include <QCoreApplication>
#include <JlCompress.h>

#include "quazip.h"


AppUpdater::AppUpdater(QObject *parent) : QObject(parent)
{

    m_utilities=new as::Utilities(this);

    updatedir=QDir(QCoreApplication::applicationDirPath());


    updatedir.cdUp();
    if(updatedir.exists("releases")==false){
        updatedir.mkdir("releases");
    }
    updatedir.cd("releases");
    if(updatedir.exists("newrelease")==false){
        updatedir.mkdir("newrelease");
    }

#ifdef Q_OS_WIN

    QDir appdir(QCoreApplication::applicationDirPath());

    appdir.setPath(QCoreApplication::applicationDirPath());

    QStringList filters;
    filters << "*.old";
    appdir.setNameFilters(filters);

    QFileInfoList appfileslist=appdir.entryInfoList(QDir::AllEntries|QDir::NoDotAndDotDot);
    foreach (QFileInfo toremove, appfileslist) {
         if(toremove.isDir()){
             QDir dirtoremove(toremove.filePath());
             dirtoremove.removeRecursively();
         }
         else {

             QFile filetoremove(toremove.filePath());
             filetoremove.remove();
         }
    }
#endif

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

        return;
    } else {
        LOG_INFO("Download succeeded");
        //TODO download ok proceed to update

        setCompressing(true);

        updatedir.setPath(QCoreApplication::applicationDirPath());


        updatedir.cdUp();
        if(updatedir.exists("backups")==false){
            updatedir.mkdir("backups");
        }
        updatedir.cd("backups");

        setUpdateStatus("Backup current release");


        QDir::setCurrent(updatedir.path());

        //        as::Utilities::NonBlockingExec([&](){
        //            JlCompress backup;

        //            connect(&backup,&JlCompress::fileCompressed,[&](QString file){
        //                LOG_INFO("Adding file:"+file);
        //                setUpdateStatus("Compressing:" file);
        //            });
        //            backup.compressDir("backup.zip",QCoreApplication::applicationDirPath());
        //        });

        updatedir.cdUp();
        updatedir.cd("releases");

        as::Utilities::NonBlockingExec([&](){
            JlCompress newrelease;

            //            connect(&backup,&JlCompress::fileCompressed,[&](QString file){
            //                LOG_INFO("Adding file:"+file);
            //                setUpdateStatus(file);
            //            });

            QDir::setCurrent(updatedir.path());
            QuaZip releasezip("newrelease.zip");
            updatedir.cd("newrelease");
            newrelease.extractDir(releasezip,updatedir.path());
        });



        QDir appdir(QCoreApplication::applicationDirPath());

        appdir.setPath(QCoreApplication::applicationDirPath());

#ifdef Q_OS_WIN
        QFileInfoList appfileslist=appdir.entryInfoList(QDir::AllEntries|QDir::NoDotAndDotDot);

        foreach (QFileInfo torename, appfileslist) {


            if(torename.completeSuffix().contains("json")==false && torename.completeSuffix().contains("log")==false){

                setUpdateStatus("Removing current release files:| "+torename.fileName());
                LOG_INFO("Removing current release files: | "+torename.filePath());

                QFile renamefile(torename.filePath());
                if(!renamefile.rename(torename.filePath()+".old")){
                    LOG_ERROR("Error renaming file:"+renamefile.fileName());
                }


            }
        }

#endif

#ifdef Q_OS_LINUX

        QFileInfoList appfileslist=appdir.entryInfoList(QDir::AllEntries|QDir::NoDotAndDotDot);

        foreach (QFileInfo todelete, appfileslist) {

            if(todelete.isDir()){
                QDir dirtoremove(todelete.filePath());
                setUpdateStatus("Removing current release files: | "+todelete.path());
                LOG_INFO("Removing current release files: | "+todelete.filePath());

                if(!dirtoremove.removeRecursively()){
                    LOG_ERROR("Error deleting file:"+QFileInfo(todelete).fileName());
                }
            }
            else if(todelete.completeSuffix().contains("json")==false && todelete.completeSuffix().contains("log")==false){

                setUpdateStatus("Removing current release files:| "+todelete.fileName());
                LOG_INFO("Removing current release files: | "+todelete.fileName());

                QFile deletefile(todelete.filePath());
                if(!deletefile.remove()){
                    LOG_ERROR("Error deleting file:"+QFileInfo(todelete).filePath());
                }


            }
        }

#endif


        updatedir.cd("bin");

        QFileInfoList newreleasefilelist = updatedir.entryInfoList(QDir::AllEntries|QDir::NoDotAndDotDot);

        foreach (QFileInfo tomove, newreleasefilelist ) {

            if(tomove.isDir()){

                setUpdateStatus("Updating  to new release | "+tomove.filePath());
                LOG_INFO("Updating to new release | "+tomove.fileName());

                QString targetdir=appdir.path()+"/"+tomove.baseName();

                QDir dirtomove;
                if(!dirtomove.rename(tomove.filePath(),targetdir)){
                    LOG_ERROR("Error deleting file:"+QFileInfo(targetdir).fileName());
                }
            }
            else if(tomove.completeSuffix().contains("json")==false && tomove.completeSuffix().contains("log")==false){




                setUpdateStatus("Updating to new release | "+tomove.fileName());
                LOG_INFO("Updating to new release | "+tomove.fileName());

                QString targetfile=appdir.path()+"/"+tomove.fileName();


                QFile filetomove(tomove.filePath());
                if(!filetomove.rename(targetfile)){
                    LOG_ERROR("Error deleting file:"+QFileInfo(targetfile).fileName());
                }


            }
        }



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
