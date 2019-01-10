#ifndef STRINGNODE_H
#define STRINGNODE_H

#include "flownode.h"

#include <QObject>

class StringNode : public FlowNode
{
    Q_OBJECT

    Q_PROPERTY(QVariant stringValue READ stringValue WRITE setStringValue NOTIFY stringValueChanged USER("serialize"))
    Q_PROPERTY(QVariant stringInput READ stringInput WRITE setStringInput NOTIFY stringInputChanged REVISION 30)

    Q_PROPERTY(QVariant stringOutput READ stringOutput WRITE setStringOutput NOTIFY stringOutputChanged REVISION 31)

    Q_PROPERTY(bool prefixFromInput READ prefixFromInput WRITE setPrefixFromInput NOTIFY prefixFromInputChanged USER("serialize") )
    Q_PROPERTY(bool suffixFromInput READ suffixFromInput WRITE setSuffixFromInput NOTIFY suffixFromInputChanged USER("serialize") )
    Q_PROPERTY(bool extractFromInput READ extractFromInput WRITE setExtractFromInput NOTIFY extractFromInputChanged USER("serialize") )
    Q_PROPERTY(bool compareFromInput READ compareFromInput WRITE setCompareFromInput NOTIFY compareFromInputChanged USER("serialize") )




public:
    StringNode();
    static  QQmlComponent*      delegate(QQmlEngine& engine) noexcept;

    QVariant stringValue() const
    {
        return m_stringValue;
    }
public slots:
    void setStringValue(QVariant stringValue)
    {

        if(m_stringValue==stringValue){
            return;
        }

        m_stringValue = stringValue;

        emit stringValueChanged(m_stringValue);

        if(m_suffixFromInput){
            setStringOutput(stringValue.value<QString>()+m_stringInput.value<QString>());
        }
        else if(m_prefixFromInput){
            setStringOutput(m_stringInput.value<QString>()+stringValue.value<QString>());
        }
        else if(m_extractFromInput){
            updateExtract();
        }
        else {
            setStringOutput(QString(""));
        }

    }


    void setPrefixFromInput(bool prefixFromInput)
    {
        if (m_prefixFromInput == prefixFromInput)
            return;

        m_prefixFromInput = prefixFromInput;

        updateinput();


        emit prefixFromInputChanged(m_prefixFromInput);
    }

    void setSuffixFromInput(bool suffixFromInput)
    {
        if (m_suffixFromInput == suffixFromInput)
            return;

        m_suffixFromInput = suffixFromInput;
        updateinput();

        emit suffixFromInputChanged(m_suffixFromInput);
    }

    void setStringInput(QVariant stringInput)
    {

        m_stringInput = stringInput;

        if(m_suffixFromInput){
            setStringOutput(stringValue().value<QString>()+m_stringInput.value<QString>());
        }else if(m_prefixFromInput){
            setStringOutput(m_stringInput.value<QString>()+stringValue().value<QString>());
        }
        else if(m_extractFromInput) {
            updateExtract();

        }
        emit stringInputChanged(m_stringInput);
    }

    void setStringOutput(QVariant stringOutput)
    {
       m_stringOutput = stringOutput;
        emit stringOutputChanged(m_stringOutput);
    }

    void setExtractFromInput(bool extractFromInput)
    {
        if (m_extractFromInput == extractFromInput)
            return;

        m_extractFromInput = extractFromInput;

        updateinput();

        emit extractFromInputChanged(m_extractFromInput);
    }

    void setCompareFromInput(bool compareFromInput)
    {
        m_compareFromInput = compareFromInput;
        emit compareFromInputChanged(m_compareFromInput);
    }

signals:
    void stringValueChanged(QVariant stringValue);



    void prefixFromInputChanged(bool prefixFromInput);

    void suffixFromInputChanged(bool suffixFromInput);

    void stringInputChanged(QVariant stringInput);

    void stringOutputChanged(QVariant stringOutput);

    void extractFromInputChanged(bool extractFromInput);

    void compareFromInputChanged(bool compareFromInput);

private:
    QVariant m_stringValue=QVariant::fromValue(QString(""));


    void updateExtract(){

        QString inputstr=m_stringInput.value<QString>();
        QString regstr=m_stringValue.value<QString>();
        QRegularExpression re(regstr);

        QRegularExpressionMatch match = re.match(inputstr);
        bool hasMatch = match.hasMatch(); // true


        if (hasMatch){
            QString matched = match.captured(1);
            setStringOutput(matched);
        }
        else{
            setStringOutput(QString(""));
        }
    }
    void updateinput(){

        if(configsLoaded()){
            FlowNodePort* inputstringport=getPortFromKey("stringInput");
            if(m_prefixFromInput==false && m_suffixFromInput==false && m_extractFromInput==false && m_compareFromInput==false){


                SceneGraph* graph=qobject_cast<SceneGraph*>(this->getGraph());

                if(inputstringport->getPortItem()->getInEdgeItems().size()>0){

                    qan::EdgeItem* edgeitem=inputstringport->getPortItem()->getInEdgeItems().at(0);
                    graph->deleteEdge(edgeitem->getEdge());
                }

                inputstringport->setHidden(true);
            }
            else{
                inputstringport->setHidden(false);
            }
        }
    }


    bool m_prefixFromInput=false;

    bool m_suffixFromInput=false;

    bool m_extractFromInput=false;

    QVariant m_stringInput=QVariant::fromValue(QString(""));

    QVariant m_stringOutput=QVariant::fromValue(QString(""));



    bool m_compareFromInput;

public:
    void Serialize(QJsonObject &json) override;
    void DeSerialize(QJsonObject &json) override;


    bool prefixFromInput() const
    {
        return m_prefixFromInput;
    }
    bool suffixFromInput() const
    {
        return m_suffixFromInput;
    }
    QVariant stringInput() const
    {
        return m_stringInput;
    }
    QVariant stringOutput() const
    {
        return m_stringOutput;
    }

    // FlowNode interface
public:
    virtual void initializeNode(int id) override;
    bool extractFromInput() const
    {
        return m_extractFromInput;
    }
    bool compareFromInput() const
    {
        return m_compareFromInput;
    }
};

#endif // STRINGNODE_H
