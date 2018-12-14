#ifndef QBSVALIDATIONMODULE_H
#define QBSVALIDATIONMODULE_H

#include <QQuickItem>
#include <automationmodule/qautomationmodule.h>

class QBSValidationModule : public QAutomationModule
{
    Q_OBJECT
    Q_PROPERTY(bool bsOK READ bsOK WRITE setBsOK NOTIFY bsOKChanged REVISION 2)
    Q_PROPERTY(bool bsNOK READ bsNOK WRITE setBsNOK NOTIFY bsNOKChanged REVISION 2)
    Q_PROPERTY(bool waitingResponse READ waitingResponse WRITE setWaitingResponse NOTIFY waitingResponseChanged REVISION 2)

    Q_PROPERTY(QString serialnumber READ serialnumber WRITE setSerialnumber NOTIFY serialnumberChanged REVISION 2)
    Q_PROPERTY(QString lefts READ lefts WRITE setLefts NOTIFY leftsChanged REVISION 2)

    Q_PROPERTY(QString serverErrorStatus READ serverErrorStatus WRITE setServerErrorStatus NOTIFY serverErrorStatusChanged REVISION 2)


public:
    QBSValidationModule(QQuickItem *parent=nullptr);


    bool bsOK() const
    {
        return m_bsOK;
    }


    QString serialnumber() const
    {
        return m_serialnumber;
    }

    bool waitingResponse() const
    {
        return m_waitingResponse;
    }

    QString serverErrorStatus() const
    {
        return m_serverErrorStatus;
    }

    QString lefts() const
    {
        return m_lefts;
    }

    bool bsNOK() const
    {
        return m_bsNOK;
    }

private:

    bool m_bsOK=false;



    QString m_serialnumber="";

    bool m_waitingResponse=false;

    QString m_serverErrorStatus="";

    QString m_lefts="";

    bool m_bsNOK=false;

    QVariantList getModuleNodeTypes() const;
signals:

void bsOKChanged(bool bsOK);



void serialnumberChanged(QString serialnumber);

void waitingResponseChanged(bool waitingResponse);

void serverErrorStatusChanged(QString serverErrorStatus);

void leftsChanged(QString lefts);

void bsNOKChanged(bool bsNOK);

public slots:

// QAutomationModule interface
void setBsOK(bool bsOK)
{


    m_bsOK = bsOK;
    emit bsOKChanged(m_bsOK);
}


void setSerialnumber(QString serialnumber)
{


    m_serialnumber = serialnumber;
    emit serialnumberChanged(m_serialnumber);
}

void setWaitingResponse(bool waitingResponse)
{


    m_waitingResponse = waitingResponse;
    emit waitingResponseChanged(m_waitingResponse);
}

void setServerErrorStatus(QString serverErrorStatus)
{


    m_serverErrorStatus = serverErrorStatus;
    emit serverErrorStatusChanged(m_serverErrorStatus);
}

void setLefts(QString lefts)
{

    m_lefts = lefts;
    emit leftsChanged(m_lefts);
}

void setBsNOK(bool bsNOK)
{
    if (m_bsNOK == bsNOK)
        return;

    m_bsNOK = bsNOK;
    emit bsNOKChanged(m_bsNOK);
}

//protected:
//    void loadModuleSettings(QString path) override;

//    // QAutomationModule interface
//protected:
//    void save() override;

    // QAutomationModule interface
public:
    virtual FlowNode *createModuleNode(QString nodetype) override;
};

#endif // QBSVALIDATIONMODULE_H
