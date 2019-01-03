#ifndef PROCESSINGENDNODE_H
#define PROCESSINGENDNODE_H

#include "processingnode.h"



class ProcessingEndNode : public ProcessingNode
{
    Q_OBJECT

    Q_PROPERTY(QVariant processingResults READ processingResults WRITE setProcessingResults NOTIFY processingResultsChanged REVISION 30)


private:
    QVariant m_processingResults=QVariant::fromValue(QString(""));

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
signals:
    void processingResultsChanged(QVariant processingResults);
};

#endif // PROCESSINGENDNODE_H
