#include "bsvalidationnode.h"

BSValidationNode::BSValidationNode(QObject *parent)
{
    m_type=Type::BSValidationNode;
}




QQmlComponent*  BSValidationNode::delegate(QQmlEngine& engine) noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/BSValidationNodeItem.qml"));
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

void BSValidationNode::setDatain(QVariant datain)
{

    m_datain = datain;
    QString v_datain=datain.value<QString>();

    if(v_datain==""){
        qDebug()<<"Empty data";
        return;
    }

    bool isignore=false;
    bool isok=false;
    QString serialnumber="";
    QString lefts="";


    QList<QString> stringParsed=v_datain.split('\n');

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
            else{
                lefts=data;
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
