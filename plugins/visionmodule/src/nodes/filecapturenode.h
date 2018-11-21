#ifndef FILECAPTURENODE_H
#define FILECAPTURENODE_H

#include "capturenode.h"



class FileCaptureNode : public CaptureNode
{
    Q_OBJECT

    Q_PROPERTY(QString filePath READ filePath WRITE setFilePath NOTIFY filePathChanged USER("serealize"))
    Q_PROPERTY(FlowNodePort* filePathPort READ filePathPort WRITE setFilePathPort NOTIFY filePathPortChanged USER("serialize"))


public:
    FileCaptureNode();
    QString filePath() const
    {
        return m_filePath;
    }
    static  QQmlComponent*      delegate(QQmlEngine& engine) noexcept;

    FlowNodePort* filePathPort() const
    {
        return m_filePathPort;
    }

public slots:

    void processFile();
    void setFilePath(QString filePath)
    {
        if (m_filePath == filePath)
            return;

        m_filePath = filePath;
        emit filePathChanged(m_filePath);
    }
    void setFilePathPort(FlowNodePort* filePathPort)
    {
        if (m_filePathPort == filePathPort)
            return;

        m_filePathPort = filePathPort;
        emit filePathPortChanged(m_filePathPort);
    }

signals:
    void filePathChanged(QString filePath);

    void filePathPortChanged(FlowNodePort* filePathPort);

private:
    QString m_filePath="";

    FlowNodePort* m_filePathPort=nullptr;

    // JsonSerializable interface
protected:
    virtual void DeSerialize(QJsonObject &json) override;

    // FlowNode interface
public:
    void initializePorts() override;
};

#endif // FILECAPTURENODE_H
