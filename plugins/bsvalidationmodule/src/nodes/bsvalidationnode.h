#ifndef BSVALIDATIONNODE_H
#define BSVALIDATIONNODE_H

#include "flownode.h"
#include <QObject>



class BSValidationInfo{

public:
    BSValidationInfo(QString serialnumber,bool bsOK,QString lefts){
        m_serialnumber=serialnumber;
        m_bsOK=bsOK;
        m_lefts=lefts;
    }

    QString serialnumber() const;

    bool bsOK() const;

    QString lefts() const;

private:

    QString m_serialnumber="";
    bool m_bsOK=false;
    QString m_lefts="";

};

class BSValidationNode : public FlowNode
{
    Q_OBJECT

    Q_PROPERTY(bool bsOK READ bsOK WRITE setBsOK NOTIFY bsOKChanged)
    Q_PROPERTY(FlowNodePort* bsOKPort READ bsOKPort WRITE setBsOKPort NOTIFY bsOKPortChanged USER("serialize"))

    Q_PROPERTY(bool bsNOK READ bsNOK WRITE setBsNOK NOTIFY bsNOKChanged )
    Q_PROPERTY(FlowNodePort* bsNOKPort READ bsNOKPort WRITE setBsNOKPort NOTIFY bsNOKPortChanged USER("serialize"))


    Q_PROPERTY(QString datain READ datain WRITE setDatain NOTIFY datainChanged)
    Q_PROPERTY(FlowNodePort* datainPort READ datainPort WRITE setDatainPort NOTIFY datainPortChanged USER("serialize"))

    Q_PROPERTY(QString lefts READ lefts WRITE setLefts NOTIFY leftsChanged)
    Q_PROPERTY(FlowNodePort* leftsPort READ leftsPort WRITE setLeftsPort NOTIFY leftsPortChanged USER("serialize"))


public:
    BSValidationNode(QObject* parent=nullptr);
    static  QQmlComponent*      delegate(QQmlEngine& engine) noexcept;
    bool bsOK() const
    {
        return m_bsOK;
    }
    bool bsNOK() const
    {
        return m_bsNOK;
    }

private:
    bool m_bsOK=false;
    bool m_bsNOK=false;

    QString m_datain;

    QString m_lefts;

    void addBSToList(BSValidationInfo* newbs);
    BSValidationInfo* getBSBySerialnumber(QString serialnumber);

    QList<BSValidationInfo*> m_ReadedBSList;

    FlowNodePort* m_datainPort=nullptr;

    FlowNodePort* m_bsOKPort=nullptr;

    FlowNodePort* m_bsNOKPort=nullptr;

    FlowNodePort* m_leftsPort=nullptr;

public slots:
    void setBsOK(bool bsOK)
    {


        m_bsOK = bsOK;
        emit bsOKChanged(m_bsOK);
    }
    void setBsNOK(bool bsNOK)
    {


        m_bsNOK = bsNOK;
        emit bsNOKChanged(m_bsNOK);
    }

    void setDatain(QString datain);


    void setLefts(QString lefts)
    {


        m_lefts = lefts;
        emit leftsChanged(m_lefts);
    }

    void setDatainPort(FlowNodePort* datainPort)
    {
        if (m_datainPort == datainPort)
            return;

        m_datainPort = datainPort;
        emit datainPortChanged(m_datainPort);
    }

    void setBsOKPort(FlowNodePort* bsOKPort)
    {
        if (m_bsOKPort == bsOKPort)
            return;

        m_bsOKPort = bsOKPort;
        emit bsOKPortChanged(m_bsOKPort);
    }

    void setBsNOKPort(FlowNodePort* bsNOKPort)
{
    if (m_bsNOKPort == bsNOKPort)
    return;

m_bsNOKPort = bsNOKPort;
emit bsNOKPortChanged(m_bsNOKPort);
}

    void setLeftsPort(FlowNodePort* leftsPort)
    {
        if (m_leftsPort == leftsPort)
            return;

        m_leftsPort = leftsPort;
        emit leftsPortChanged(m_leftsPort);
    }

signals:
    void bsOKChanged(bool bsOK);
    void bsNOKChanged(bool bsNOK);

    // FlowNode interface
    void datainChanged(QString datain);

    void leftsChanged(QString lefts);

    void datainPortChanged(FlowNodePort* datainPort);

    void bsOKPortChanged(FlowNodePort* bsOKPort);

    void bsNOKPortChanged(FlowNodePort* bsNOKPort);

    void leftsPortChanged(FlowNodePort* leftsPort);

public:
//    void write(QJsonObject &json) const override;
//    void read(QJsonObject &json) override;
QString datain() const
{
    return m_datain;
}
QString lefts() const
{
    return m_lefts;
}
FlowNodePort* datainPort() const
{
    return m_datainPort;
}


// JsonSerializable interface
public:
void Serialize(QJsonObject &json) override;
void DeSerialize(QJsonObject &json) override;
FlowNodePort* bsOKPort() const
{
    return m_bsOKPort;
}
FlowNodePort* bsNOKPort() const
{
    return m_bsNOKPort;
}
FlowNodePort* leftsPort() const
{
    return m_leftsPort;
}
};

#endif // BSVALIDATIONNODE_H
