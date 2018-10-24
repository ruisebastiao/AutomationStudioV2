#ifndef APPUPDATER_H
#define APPUPDATER_H

#include "automationstudiocoreglobal.h"

#include "jsonserializable.h"
#include "utilities.h"


#include <QDir>
#include <QNetworkReply>
#include <QObject>
#include <qfile.h>



class AUTOMATIONSTUDIO_CORE_EXPORT AppUpdater: public QObject,public JsonSerializable
{
    Q_OBJECT

    Q_PROPERTY(QString downloadPath READ downloadPath WRITE setDownloadPath NOTIFY downloadPathChanged USER("serialize"))
    Q_PROPERTY(QString serverUrl READ serverUrl WRITE setServerUrl NOTIFY serverUrlChanged USER("serialize"))

    Q_PROPERTY(QString updateStatus READ updateStatus WRITE setUpdateStatus NOTIFY updateStatusChanged)

    Q_PROPERTY(double downloadProgress READ downloadProgress WRITE setDownloadProgress  NOTIFY downloadProgressChanged)

    Q_PROPERTY(bool compressing READ compressing WRITE setCompressing  NOTIFY compressingChanged)




public:
    AppUpdater(QObject *parent=nullptr);

    void doUpdate(QString release);
private:

    QNetworkReply *currentDownload=nullptr;
    QFile m_output;
    QNetworkAccessManager manager;

    as::Utilities* m_utilities=nullptr;

    void doInstall();

    QDir updatedir;



    QString m_downloadPath="";

    QString m_serverUrl="";



    QString m_updateStatus="Waiting";

    double m_downloadProgress=0;

    bool m_compressing=false;


public slots:



    // JsonSerializable interface
    void setDownloadPath(QString downloadPath)
    {
        if (m_downloadPath == downloadPath)
            return;

        m_downloadPath = downloadPath;
        emit downloadPathChanged(m_downloadPath);
    }

    void setServerUrl(QString serverUrl)
    {
        if (m_serverUrl == serverUrl)
            return;

        m_serverUrl = serverUrl;
        emit serverUrlChanged(m_serverUrl);
    }

public:
    virtual void Serialize(QJsonObject &json) override;
    virtual void DeSerialize(QJsonObject &json) override;
    QString downloadPath() const
    {
        return m_downloadPath;
    }
    QString serverUrl() const
    {
        return m_serverUrl;
    }

    QString updateStatus() const
    {
        return m_updateStatus;
    }

    double downloadProgress() const
    {
        return m_downloadProgress;
    }

    bool compressing() const
    {
        return m_compressing;
    }

signals:
    void downloadPathChanged(QString downloadPath);
    void serverUrlChanged(QString serverUrl);
    void updateStart();
    void downloadProgressChanged(double progressChanged);

    void updateDone();

    void updateStatusChanged(QString updateStatus);

    void compressingChanged(bool compressing);

private slots:

    void currentDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void downloadFinished();
    void downloadReadyRead();


public slots:



    void setUpdateStatus(QString updateStatus)
    {
        if (m_updateStatus == updateStatus)
            return;

        m_updateStatus = updateStatus;
        emit updateStatusChanged(m_updateStatus);
    }
    void setDownloadProgress(double downloadProgress)
    {

        m_downloadProgress = downloadProgress;
        emit downloadProgressChanged(m_downloadProgress);
    }
    void setCompressing(bool compressing)
    {
        if (m_compressing == compressing)
            return;

        m_compressing = compressing;
        emit compressingChanged(m_compressing);
    }
};

#endif // APPUPDATER_H
