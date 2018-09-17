#include "bsvalidationnode.h"

BSValidationNode::BSValidationNode(QObject *parent)
{
    m_type=Type::BSValidationNode;
}




QQmlComponent*  BSValidationNode::delegate(QQmlEngine& engine) noexcept
{
    static std::unique_ptr<QQmlComponent>   delegate;
    if ( !delegate )
        delegate = std::make_unique<QQmlComponent>(&engine, "qrc:///Nodes/BSValidationNodeItem.qml");
    return delegate.get();
}

void BSValidationNode::addBSToList(BSValidationInfo *newbs)
{
    m_ReadedBSList.append(newbs);
    if(m_ReadedBSList.length()>15){
        m_ReadedBSList.removeAt(0);
    }
}

BSValidationInfo *BSValidationNode::getBSBySerialnumber(QString serialnumber)
{


    for (int var = 0; var < m_ReadedBSList.length(); ++var) {
        if(m_ReadedBSList.at(var)->serialnumber()==serialnumber){
            return  m_ReadedBSList.at(var);
        }
    }

    return nullptr;
}

void BSValidationNode::setDatain(QString datain)
{


    m_datain = datain;

    if(m_datain==""){
        return;
    }

    bool isignore=false;
    bool isok=false;
    QString serialnumber="";
    QString lefts="";


    QList<QString> stringParsed=m_datain.split('\n');

    for (int i = 0; i < stringParsed.length(); ++i) {
        QString data=stringParsed[i];
        if(i==0){
            if(data!=""){
                if(data.toLower().contains("notok")){
                    isok=false;
                }
                else{
                    if(data.toLower().contains("ok")){
                        isok=true;
                    }
                    else{
                         isignore=true;
                    }
                }
            }
            else{
                isok=false;
                isignore=true;
            }
        }
        else if(i==1){
            QRegExp rx("(-?\\d+(?:[\\.,]\\d+(?:e\\d+)?)?)");
            QList<QString> list;
            int pos = 0;

            while ((pos = rx.indexIn(data, pos)) != -1) {
                list << rx.cap(1);
                pos += rx.matchedLength();
            }

            if(list.length()>0){
                lefts=list.at(0);
            }
        }
        else if(i==3){
          serialnumber=data;
        }





    }

    if(isignore){
        BSValidationInfo* ignoredbs=getBSBySerialnumber(serialnumber);
        if(ignoredbs){
            isok=ignoredbs->bsOK();
            lefts=ignoredbs->lefts();
        }
        else{
            isok=false;
            lefts="?";
        }
    }
    else{
        addBSToList(new BSValidationInfo(serialnumber,isok,lefts));
    }

    setBsNOK(!isok);
    setBsOK(isok);
    setLefts(lefts);





    emit datainChanged(m_datain);
}

void BSValidationNode::Serialize(QJsonObject &json)
{
    FlowNode::Serialize(json);
}

void BSValidationNode::DeSerialize(QJsonObject &json)
{
    m_datainPort=new FlowNodePort(this,qan::PortItem::Type::In,"datain");

    m_bsOKPort=new FlowNodePort(this,qan::PortItem::Type::Out,"bsOK");
    m_bsNOKPort=new FlowNodePort(this,qan::PortItem::Type::Out,"bsNOK");
    m_leftsPort=new FlowNodePort(this,qan::PortItem::Type::Out,"lefts");


    FlowNode::DeSerialize(json);
}


QString BSValidationInfo::serialnumber() const
{
    return m_serialnumber;
}

bool BSValidationInfo::bsOK() const
{
    return m_bsOK;
}

QString BSValidationInfo::lefts() const
{
    return m_lefts;
}
