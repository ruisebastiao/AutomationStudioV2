#ifndef QBSVALIDATIONMODULE_H
#define QBSVALIDATIONMODULE_H

#include <QQuickItem>
#include <automationmodule/qautomationmodule.h>

class QBSValidationModule : public QAutomationModule
{
    Q_OBJECT

    Q_PROPERTY(QVariant bsOK READ bsOK WRITE setBsOK NOTIFY bsOKChanged REVISION 2)
    Q_PROPERTY(QVariant bsNOK READ bsNOK WRITE setBsNOK NOTIFY bsNOKChanged REVISION 2)
    Q_PROPERTY(QVariant waitingResponse READ waitingResponse WRITE setWaitingResponse NOTIFY waitingResponseChanged REVISION 2)

    Q_PROPERTY(QVariant serialnumber READ serialnumber WRITE setSerialnumber NOTIFY serialnumberChanged REVISION 2)
    Q_PROPERTY(QVariant lefts READ lefts WRITE setLefts NOTIFY leftsChanged REVISION 2)

    Q_PROPERTY(QVariant serverErrorStatus READ serverErrorStatus WRITE setServerErrorStatus NOTIFY serverErrorStatusChanged REVISION 2)


public:
    QBSValidationModule(QQuickItem *parent=nullptr);


    QVariant bsOK() const
    {
        return m_bsOK;
    }


    QVariant serialnumber() const
    {
        return m_serialnumber;
    }

    QVariant waitingResponse() const
    {
        return m_waitingResponse;
    }

    QVariant serverErrorStatus() const
    {
        return m_serverErrorStatus;
    }

    QVariant lefts() const
    {
        return m_lefts;
    }

    QVariant bsNOK() const
    {
        return m_bsNOK;
    }

private:

    QVariant m_bsOK=false;



    QVariant m_serialnumber=QString("");

    QVariant m_waitingResponse=false;

    QVariant m_serverErrorStatus=QString("");

    QVariant m_lefts=QString("");

    QVariant m_bsNOK=false;

    QVariantList getModuleNodeTypes() const;
signals:

void bsOKChanged(QVariant bsOK);



void serialnumberChanged(QVariant serialnumber);

void waitingResponseChanged(QVariant waitingResponse);

void serverErrorStatusChanged(QVariant serverErrorStatus);

void leftsChanged(QVariant lefts);

void bsNOKChanged(QVariant bsNOK);

public slots:

// QAutomationModule interface
void setBsOK(QVariant bsOK)
{


    m_bsOK = bsOK;
    emit bsOKChanged(m_bsOK);
}


void setSerialnumber(QVariant serialnumber)
{


    m_serialnumber = serialnumber;
    emit serialnumberChanged(m_serialnumber);
}

void setWaitingResponse(QVariant waitingResponse)
{


    m_waitingResponse = waitingResponse;
    emit waitingResponseChanged(m_waitingResponse);
}

void setServerErrorStatus(QVariant serverErrorStatus)
{


    m_serverErrorStatus = serverErrorStatus;
    emit serverErrorStatusChanged(m_serverErrorStatus);
}

void setLefts(QVariant lefts)
{

    m_lefts = lefts;
    emit leftsChanged(m_lefts);
}

void setBsNOK(QVariant bsNOK)
{


    m_bsNOK = bsNOK;
    emit bsNOKChanged(m_bsNOK);
}

};

#endif // QBSVALIDATIONMODULE_H
