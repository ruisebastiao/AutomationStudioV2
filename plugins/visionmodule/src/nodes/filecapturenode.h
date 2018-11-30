#ifndef FILECAPTURENODE_H
#define FILECAPTURENODE_H

#include "capturenode.h"



class FileCaptureNode : public CaptureNode
{
    Q_OBJECT

    Q_PROPERTY(QString filePath READ filePath WRITE setFilePath NOTIFY filePathChanged USER("serealize"))
    //    Q_PROPERTY(QString filePrefix READ filePrefix WRITE setFilePrefix NOTIFY filePrefixChanged USER("serealize"))
    Q_PROPERTY(int fileIndex READ fileIndex WRITE setFileIndex NOTIFY fileIndexChanged)
    Q_PROPERTY(bool useSequence READ useSequence WRITE setUseSequence NOTIFY useSequenceChanged USER("serealize"))
    Q_PROPERTY(int sequenceSize READ sequenceSize WRITE setSequenceSize NOTIFY sequenceSizeChanged USER("serealize"))


public:
    FileCaptureNode();
    QString filePath() const
    {
        return m_filePath;
    }
    static  QQmlComponent*      delegate(QQmlEngine& engine) noexcept;



public slots:

    void processFile();
    void setFilePath(QString filePath)
    {
        if (m_filePath == filePath)
            return;

        m_filePath = filePath;
        emit filePathChanged(m_filePath);
    }


    void setUseSequence(bool useSequence)
    {
        if (m_useSequence == useSequence)
            return;

        m_useSequence = useSequence;
        emit useSequenceChanged(m_useSequence);
    }

    void setSequenceSize(int sequenceSize)
    {
        if (m_sequenceSize == sequenceSize)
            return;

        m_sequenceSize = sequenceSize;
        emit sequenceSizeChanged(m_sequenceSize);
    }

    void setFileIndex(int fileIndex)
    {
        if (m_fileIndex == fileIndex)
            return;

        m_fileIndex = fileIndex;
        if(m_fileIndex+1>m_sequenceSize){
            m_fileIndex=0;
        }
        emit fileIndexChanged(m_fileIndex);
    }

signals:
    void filePathChanged(QString filePath);

    void fileIndexChanged(int fileIndex);

    void useSequenceChanged(bool useSequence);

    void sequenceSizeChanged(int sequenceSize);

    void processFileChanged(QString filepath);
private:
    QString m_filePath="";


    // JsonSerializable interface
    int m_fileIndex=0;

    bool m_useSequence=false;

    int m_sequenceSize=0;

protected:
    virtual void DeSerialize(QJsonObject &json) override;

    // FlowNode interface
public:

    int fileIndex() const
    {
        return m_fileIndex;
    }
    bool useSequence() const
    {
        return m_useSequence;
    }
    int sequenceSize() const
    {
        return m_sequenceSize;
    }
};

#endif // FILECAPTURENODE_H
