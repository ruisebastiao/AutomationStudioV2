#ifndef BSVALIDATIONVISUALNODE_H
#define BSVALIDATIONVISUALNODE_H

#include <QObject>
#include <visualnode.h>


class BSValidationVisualNode : public VisualNode
{
    Q_OBJECT

    Q_PROPERTY(QString serialnumber READ serialnumber WRITE setSerialnumber NOTIFY serialnumberChanged)
    Q_PROPERTY(FlowNodePort* serialnumberPort READ serialnumberPort WRITE setSerialnumberPort NOTIFY serialnumberPortChanged USER("serialize"))


    Q_PROPERTY(bool BSOK READ BSOK WRITE setBSOK NOTIFY BSOKChanged)
    Q_PROPERTY(FlowNodePort* BSOKPort READ BSOKPort WRITE setBSOKPort NOTIFY BSOKPortChanged USER("serialize"))

    Q_PROPERTY(bool BSNOK READ BSNOK WRITE setBSNOK NOTIFY BSNOKChanged)
    Q_PROPERTY(FlowNodePort* BSNOKPort READ BSNOKPort WRITE setBSNOKPort NOTIFY BSNOKPortChanged USER("serialize"))

    Q_PROPERTY(QString lefts READ lefts WRITE setLefts NOTIFY leftsChanged)
    Q_PROPERTY(FlowNodePort* leftsPort READ leftsPort WRITE setLeftsPort NOTIFY leftsPortChanged USER("serialize"))


    Q_PROPERTY(bool WaitResults READ WaitResults WRITE setWaitResults NOTIFY WaitResultsChanged)
    Q_PROPERTY(FlowNodePort* WaitResultsPort READ WaitResultsPort WRITE setWaitResultsPort NOTIFY WaitResultsPortChanged USER("serialize"))



    Q_PROPERTY(QString Status READ Status WRITE setStatus NOTIFY StatusChanged)
    Q_PROPERTY(QString BSInfo READ BSInfo WRITE setBSInfo NOTIFY BSInfoChanged)




public:
    BSValidationVisualNode();
    static  QQmlComponent*      delegate(QQmlEngine& engine) noexcept;


public slots:


    void setSerialnumber(QString serialnumber)
    {


        m_serialnumber = serialnumber;
        emit serialnumberChanged(m_serialnumber);
    }

    void setSerialnumberPort(FlowNodePort* serialnumberPort)
    {


        m_serialnumberPort = serialnumberPort;
        emit serialnumberPortChanged(m_serialnumberPort);
    }

    void setBSOK(bool BSOK)
    {


        m_BSOK = BSOK;
        emit BSOKChanged(m_BSOK);
    }

    void setBSOKPort(FlowNodePort* BSOKPort)
    {


        m_BSOKPort = BSOKPort;
        emit BSOKPortChanged(m_BSOKPort);
    }

    void setBSNOK(bool BSNOK)
    {


        m_BSNOK = BSNOK;
        emit BSNOKChanged(m_BSNOK);
    }

    void setBSNOKPort(FlowNodePort* BSNOKPort)
    {


        m_BSNOKPort = BSNOKPort;
        emit BSNOKPortChanged(m_BSNOKPort);
    }

    void setWaitResults(bool WaitResults)
    {



        m_WaitResults = WaitResults;

        if(m_WaitResults){
            setStatus("Aguarda resposta do servidor");
        }
        else{
            setStatus("Aguarda leitura de BS");
        }

        emit WaitResultsChanged(m_WaitResults);
    }

    void setWaitResultsPort(FlowNodePort* WaitResultsPort)
    {

        m_WaitResultsPort = WaitResultsPort;
        emit WaitResultsPortChanged(m_WaitResultsPort);
    }

    void setStatus(QString Status)
    {



        m_Status = Status;
        emit StatusChanged(m_Status);
    }

    void setLefts(QString lefts)
    {

        m_lefts = lefts;

        if(m_lefts.contains('?') || m_lefts.isEmpty()){
            setBSInfo("Sem informação de passagens");
        }
        else{
             setBSInfo("Faltam "+lefts+" passagens");
        }

        emit leftsChanged(m_lefts);
    }

    void setLeftsPort(FlowNodePort* leftsPort)
    {
        if (m_leftsPort == leftsPort)
            return;

        m_leftsPort = leftsPort;
        emit leftsPortChanged(m_leftsPort);
    }

    void setBSInfo(QString BSInfo)
    {


        m_BSInfo = BSInfo;


        emit BSInfoChanged(m_BSInfo);
    }

signals:


    void serialnumberChanged(QString serialnumber);

    void serialnumberPortChanged(FlowNodePort* serialnumberPort);

    void BSOKChanged(bool BSOK);

    void BSOKPortChanged(FlowNodePort* BSOKPort);

    void BSNOKChanged(bool BSNOK);

    void BSNOKPortChanged(FlowNodePort* BSNOKPort);


    void StatusChanged(QString Status);

    void WaitResultsChanged(bool WaitResults);



    void WaitResultsPortChanged(FlowNodePort* WaitResultsPort);

    void leftsPortChanged(FlowNodePort* leftsPort);

    void leftsChanged(QString lefts);

    void BSInfoChanged(QString BSInfo);

private:

    QString m_serialnumber="";
    bool m_BSOK=false;
    bool m_BSNOK=false;
    bool m_WaitResults=false;
    QString m_Status="Aguarda Leitura de BS";

    // JsonSerializable interface
    FlowNodePort* m_serialnumberPort=nullptr;

    FlowNodePort* m_BSOKPort=nullptr;

    FlowNodePort* m_BSNOKPort=nullptr;

    FlowNodePort* m_WaitResultsPort=nullptr;

    QString m_lefts="";

    FlowNodePort* m_leftsPort=nullptr;

    QString m_BSInfo="Dados indisponiveis";

public:
    void DeSerialize(QJsonObject &json) override;

    QString serialnumber() const
    {
        return m_serialnumber;
    }
    FlowNodePort* serialnumberPort() const
    {
        return m_serialnumberPort;
    }
    bool BSOK() const
    {
        return m_BSOK;
    }
    FlowNodePort* BSOKPort() const
    {
        return m_BSOKPort;
    }
    bool BSNOK() const
    {
        return m_BSNOK;
    }
    FlowNodePort* BSNOKPort() const
    {
        return m_BSNOKPort;
    }
    bool WaitResults() const
    {
        return m_WaitResults;
    }
    FlowNodePort* WaitResultsPort() const
    {
        return m_WaitResultsPort;
    }
    QString Status() const
    {
        return m_Status;
    }

    // JsonSerializable interface
public:
    void Serialize(QJsonObject &json) override;
    QString lefts() const
    {
        return m_lefts;
    }
    FlowNodePort* leftsPort() const
    {
        return m_leftsPort;
    }
    QString BSInfo() const
    {
        return m_BSInfo;
    }
};


#endif // BSVALIDATIONVISUALNODE_H
