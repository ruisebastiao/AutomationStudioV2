#ifndef PROPERTIESNODE_H
#define PROPERTIESNODE_H

#include <flownode.h>
#include <propertyinfolist.h>

class PropertiesNode:public FlowNode
{
    Q_OBJECT


    Q_PROPERTY(PropertyInfoList* properties READ properties WRITE setProperties NOTIFY propertiesChanged USER("serialize"))

    Q_PROPERTY(bool checkOnInput READ checkOnInput WRITE setCheckOnInput NOTIFY checkOnInputChanged USER("serialize"))


    Q_PROPERTY(ProperyInfo* currentPropertyInfo READ currentPropertyInfo WRITE setCurrentPropertyInfo NOTIFY currentPropertyInfoChanged)


    Q_PROPERTY(QVariant checkPropertyInfo READ checkPropertyInfo WRITE setCheckPropertyInfo NOTIFY checkPropertyInfoChanged REVISION 30)
    Q_PROPERTY(QVariant validatePropertyName READ validatePropertyName WRITE setValidatePropertyName NOTIFY validatePropertyNameChanged REVISION 30)
    Q_PROPERTY(QVariant validatePropertyValue READ validatePropertyValue WRITE setValidatePropertyValue NOTIFY validatePropertyValueChanged REVISION 30)

    Q_PROPERTY(QVariant isOK READ isOK WRITE setIsOK NOTIFY isOKChanged REVISION 31)
    Q_PROPERTY(QVariant isNOK READ isNOK WRITE setIsNOK NOTIFY isNOKChanged REVISION 31)

    Q_PROPERTY(QVariant currentPropertyValue READ currentPropertyValue WRITE setCurrentPropertyValue NOTIFY currentPropertyValueChanged REVISION 31)




public:


    PropertiesNode();


    static  QQmlComponent*  delegate(QQmlEngine& engine) noexcept;

    PropertyInfoList* properties()
    {
        return m_properties;
    }

    Q_INVOKABLE void addPropertyInfo(QString name,QString value){
        ProperyInfo* newinfo=new ProperyInfo(name,value);
        m_properties->addItem(newinfo);
    }
    Q_INVOKABLE void updatePropertyInfo(ProperyInfo* info, QString name,QString value){
        info->setPropertyName(name);
        info->setPropertyValue(value);
    }

    QVariant checkPropertyInfo() const
    {
        return m_checkPropertyInfo;
    }

    QVariant validatePropertyName() const
    {
        return m_validatePropertyName;
    }

    QVariant validatePropertyValue() const
    {
        return m_validatePropertyValue;
    }

    QVariant isOK() const
    {
        return m_isOK;
    }

    QVariant isNOK() const
    {
        return m_isNOK;
    }

    ProperyInfo* currentPropertyInfo() const
    {
        return m_currentPropertyInfo;
    }



    bool checkOnInput() const
    {
        return m_checkOnInput;
    }

    QVariant currentPropertyValue() const
    {
        return m_currentPropertyValue;
    }

public slots:
    void setProperties(PropertyInfoList* properties)
    {
        if (m_properties == properties)
            return;

        m_properties = properties;
        emit propertiesChanged(m_properties);
    }

    void setCheckPropertyInfo(QVariant checkPropertyInfo)
    {
        m_checkPropertyInfo = checkPropertyInfo;
        if(m_checkPropertyInfo.value<bool>()){

            doCheckInfo();
        }
        emit checkPropertyInfoChanged(m_checkPropertyInfo);
    }

    void setValidatePropertyName(QVariant validatePropertyName)
    {


        m_validatePropertyName = validatePropertyName;
        emit validatePropertyNameChanged(m_validatePropertyName);

        if(checkPropertyInfo().value<bool>() || m_checkOnInput ){
            doCheckInfo();
        }
        ProperyInfo* info=m_properties->getByName(validatePropertyName.value<QString>());

        if(info){
            setCurrentPropertyValue(info->propertyValue());
        }
        else{
            setCurrentPropertyValue("");
        }
    }

    void setValidatePropertyValue(QVariant validatePropertyValue)
    {


        m_validatePropertyValue = validatePropertyValue;
        emit validatePropertyValueChanged(m_validatePropertyValue);
        if(checkPropertyInfo().value<bool>() || m_checkOnInput){
            doCheckInfo();
        }




    }

    void setIsOK(QVariant isOK)
    {

        m_isOK = isOK;

        emit isOKChanged(m_isOK);

        setIsNOK(!isOK.value<bool>());
    }

    void setIsNOK(QVariant isNOK)
    {

        m_isNOK = isNOK;
        emit isNOKChanged(m_isNOK);
    }




    void setCheckOnInput(bool checkOnInput)
    {
        if (m_checkOnInput == checkOnInput)
            return;

        m_checkOnInput = checkOnInput;
        emit checkOnInputChanged(m_checkOnInput);
    }

    void setCurrentPropertyValue(QVariant currentPropertyValue)
    {


        m_currentPropertyValue = currentPropertyValue;
        emit currentPropertyValueChanged(currentPropertyValue);
    }

    void setCurrentPropertyInfo(ProperyInfo* currentPropertyInfo)
    {
        if (m_currentPropertyInfo == currentPropertyInfo)
            return;

        m_currentPropertyInfo = currentPropertyInfo;
        emit currentPropertyInfoChanged(m_currentPropertyInfo);
    }

signals:
    void propertiesChanged(PropertyInfoList* infos);

    void checkPropertyInfoChanged(QVariant checkInfo);

    void validatePropertyNameChanged(QVariant currentInfoId);

    void currentPropertyValueChanged(QVariant currentPropertyValue);

    void isOKChanged(QVariant infoOK);

    void isNOKChanged(QVariant infoNOK);

    void currentPropertyInfoChanged(ProperyInfo* currentInfo);

    void checkOnInputChanged(bool checkOnInput);

    void validatePropertyValueChanged(QVariant idFromCurrentProject);

private:

    void doCheckInfo(){
        ProperyInfo* info=m_properties->getByName(m_validatePropertyName.value<QString>());

        if(info){
            setIsOK(info->propertyValue()==m_validatePropertyValue);
        }
        else{
            setIsOK(false);
        }

    }
    void setCurrentInfo(ProperyInfo* currentInfo)
    {
        if (m_currentPropertyInfo == currentInfo)
            return;

        m_currentPropertyInfo = currentInfo;
        emit currentPropertyInfoChanged(m_currentPropertyInfo);
    }

    PropertyInfoList *m_properties= new PropertyInfoList();
    QVariant m_checkPropertyInfo=false;
    QVariant m_validatePropertyName=QString("");
    QVariant m_validatePropertyValue=QString("");
    QVariant m_isOK=false;
    QVariant m_isNOK=false;
    ProperyInfo* m_currentPropertyInfo=nullptr;
    QString m_infoTitle="Info Title";
    bool m_checkOnInput=false;
    QVariant m_currentPropertyValue=QString("");
};

#endif // PROPERTIESNODE_H
