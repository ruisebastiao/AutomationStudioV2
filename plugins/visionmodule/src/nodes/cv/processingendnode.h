#ifndef PROCESSINGENDNODE_H
#define PROCESSINGENDNODE_H

#include "processingnode.h"



class ProcessingEndNode : public ProcessingNode
{
    Q_OBJECT

    Q_PROPERTY(bool processOnResults READ processOnResults WRITE setProcessOnResults NOTIFY processOnResultsChanged USER("serialize"))
    Q_PROPERTY(QVariant processingResults READ processingResults WRITE setProcessingResults NOTIFY processingResultsChanged REVISION 30)


private:
    QVariant m_processingResults=QVariant::fromValue(QString(""));

    bool m_processOnResults=false;

public:
    ProcessingEndNode();

    // ProcessingNode interface
    static QQmlComponent *delegate(QQmlEngine &engine) noexcept;
public slots:
    virtual void setInput(QVariant input) override;

    void setProcessingResults(QVariant processingResults)
    {


        m_processingResults = processingResults;
        emit processingResultsChanged(m_processingResults);
        if(m_processOnResults){
            doProcess();
        }
    }

    void setProcessOnResults(bool processOnResults)
    {
        if (m_processOnResults == processOnResults)
            return;

        m_processOnResults = processOnResults;
        emit processOnResultsChanged(m_processOnResults);
    }

protected:
    virtual void doProcess() override;

    // JsonSerializable interface
public:
    virtual void DeSerialize(QJsonObject &json) override;
    QVariant processingResults() const
    {
        return m_processingResults;
    }
    bool processOnResults() const
    {
        return m_processOnResults;
    }

signals:
    void processingResultsChanged(QVariant processingResults);
    void processOnResultsChanged(bool processOnResults);
};

#endif // PROCESSINGENDNODE_H
