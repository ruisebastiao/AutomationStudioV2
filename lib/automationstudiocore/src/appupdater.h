#ifndef APPUPDATER_H
#define APPUPDATER_H

#include "automationstudiocoreglobal.h"

#include "jsonserializable.h"

#include <QNetworkReply>
#include <QObject>
#include <qfile.h>

class AUTOMATIONSTUDIO_CORE_EXPORT AppUpdater: public QObject,public JsonSerializable
{
    Q_OBJECT

    Q_PROPERTY(QString downloadPath READ downloadPath WRITE setDownloadPath NOTIFY downloadPathChanged USER("serialize"))
    Q_PROPERTY(QString serverUrl READ serverUrl WRITE setServerUrl NOTIFY serverUrlChanged USER("serialize"))


public:
    AppUpdater(QObject *parent=nullptr);

    void doUpdate(QString release);
private:

    QNetworkReply *currentDownload=nullptr;
    QFile m_output;
    QNetworkAccessManager manager;

    void doInstall();
    QString m_updateStatusChanged;



    QString m_downloadPath="";

    QString m_serverUrl="";

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

signals:
    void downloadPathChanged(QString downloadPath);
    void serverUrlChanged(QString serverUrl);
    void updateStart();
    void downloadProgressChanged(double progressChanged);
    void updateStatusChangedChanged(QString updateStatusChanged);

    void updateDone();




private slots:

    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void downloadFinished();
    void downloadReadyRead();


public slots:


    void setUpdateStatusChanged(QString updateStatusChanged)
    {
        if (m_updateStatusChanged == updateStatusChanged)
            return;

        m_updateStatusChanged = updateStatusChanged;
        emit updateStatusChangedChanged(m_updateStatusChanged);
    }



};

#endif // APPUPDATER_H
