#ifndef BSVALIDATIONNODE_H
#define BSVALIDATIONNODE_H

#include "automationmodule/flownode.h"
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

    Q_PROPERTY(QVariant bsOK READ bsOK WRITE setBsOK NOTIFY bsOKChanged REVISION 31)

    Q_PROPERTY(QVariant bsNOK READ bsNOK WRITE setBsNOK NOTIFY bsNOKChanged REVISION 31)

    Q_PROPERTY(QVariant datain READ datain WRITE setDatain NOTIFY datainChanged REVISION 30)

    Q_PROPERTY(QVariant lefts READ lefts WRITE setLefts NOTIFY leftsChanged REVISION 31)


public:
    BSValidationNode(QObject* parent=nullptr);
    static  QQmlComponent*      delegate(QQmlEngine& engine) noexcept;
    QVariant  bsOK() const
    {
        return m_bsOK;
    }
    QVariant bsNOK() const
    {
        return m_bsNOK;
    }

private:
    QVariant m_bsOK=QVariant::fromValue(false);
    QVariant m_bsNOK=QVariant::fromValue(false);

    QVariant m_datain=QVariant::fromValue(QString(""));

    QVariant m_lefts=QVariant::fromValue(QString(""));

    void addBSToList(BSValidationInfo* newbs);
    BSValidationInfo* getBSBySerialnumber(QString serialnumber);

    QList<BSValidationInfo*> m_ReadedBSList;


public slots:
    void setBsOK(QVariant bsOK)
    {


        m_bsOK = bsOK;
        emit bsOKChanged(m_bsOK);
    }
    void setBsNOK(QVariant bsNOK)
    {


        m_bsNOK = bsNOK;
        emit bsNOKChanged(m_bsNOK);
    }

    void setDatain(QVariant datain);


    void setLefts(QVariant lefts)
    {


        m_lefts = lefts;
        emit leftsChanged(m_lefts);
    }




signals:
    void bsOKChanged(QVariant bsOK);
    void bsNOKChanged(QVariant bsNOK);

    // FlowNode interface
    void datainChanged(QVariant datain);

    void leftsChanged(QVariant lefts);



public:
//    void write(QJsonObject &json) const override;
//    void read(QJsonObject &json) override;
QVariant datain() const
{
    return m_datain;
}
QVariant lefts() const
{
    return m_lefts;
}



// JsonSerializable interface
public:
void Serialize(QJsonObject &json) override;
void DeSerialize(QJsonObject &json) override;

};

#endif // BSVALIDATIONNODE_H
