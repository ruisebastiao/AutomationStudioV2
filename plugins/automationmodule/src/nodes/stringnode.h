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

    Q_PROPERTY(QVariant stringEqual READ stringEqual WRITE setStringEqual NOTIFY stringEqualChanged REVISION 31)
    Q_PROPERTY(QVariant stringNotEqual READ stringNotEqual WRITE setStringNotEqual NOTIFY stringNotEqualChanged REVISION 31)

    Q_PROPERTY(bool noInput READ noInput WRITE setNoInput NOTIFY noInputChanged USER("serialize") )
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



        if(m_suffixFromInput){
            setStringOutput(stringValue.value<QString>()+m_stringInput.value<QString>());
        }
        else if(m_prefixFromInput){
            setStringOutput(m_stringInput.value<QString>()+stringValue.value<QString>());
        }
        else if(m_extractFromInput){
            updateExtract();
        }
        else if(m_compareFromInput){
            compareStrings();
        }
        else {
            setStringOutput(stringValue);
        }

        emit stringValueChanged(m_stringValue);
    }



    void setPrefixFromInput(bool prefixFromInput)
    {
        if (m_prefixFromInput == prefixFromInput)
            return;

        m_prefixFromInput = prefixFromInput;

        updateports();


        emit prefixFromInputChanged(m_prefixFromInput);
    }

    void setSuffixFromInput(bool suffixFromInput)
    {
        if (m_suffixFromInput == suffixFromInput)
            return;

        m_suffixFromInput = suffixFromInput;
        updateports();

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
        else if(m_compareFromInput){
            compareStrings();
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


        updateports();

        emit extractFromInputChanged(m_extractFromInput);
    }

    void setCompareFromInput(bool compareFromInput)
    {
        if (m_compareFromInput == compareFromInput)
            return;
        m_compareFromInput = compareFromInput;

        updateports();
        emit compareFromInputChanged(m_compareFromInput);
    }

    void setNoInput(bool noInput)
    {
        if (m_noInput == noInput)
            return;

        m_noInput = noInput;
        updateports();
        emit noInputChanged(m_noInput);
    }

    void setStringEqual(QVariant stringEqual)
    {


        m_stringEqual = stringEqual;
        emit stringEqualChanged(m_stringEqual);
        setStringNotEqual(!m_stringEqual.value<bool>());
    }

    void setStringNotEqual(QVariant stringNotEqual)
    {


        m_stringNotEqual = stringNotEqual;
        emit stringNotEqualChanged(m_stringNotEqual);
    }

signals:
    void stringValueChanged(QVariant stringValue);



    void prefixFromInputChanged(bool prefixFromInput);

    void suffixFromInputChanged(bool suffixFromInput);

    void stringInputChanged(QVariant stringInput);

    void stringOutputChanged(QVariant stringOutput);

    void extractFromInputChanged(bool extractFromInput);

    void compareFromInputChanged(bool compareFromInput);

    void noInputChanged(bool noInput);

    void stringEqualChanged(QVariant stringEqual);

    void stringNotEqualChanged(QVariant stringNotEqual);

private:
    QVariant m_stringValue=QVariant::fromValue(QString(""));


    void compareStrings(){
        QString inputstr=m_stringInput.value<QString>();
        QString stringvalue=m_stringValue.value<QString>();


        if(inputstr==stringvalue){
            setStringEqual(true);
        }
        else {
            setStringEqual(false);
        }

    }


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
    void updateports(){

        if(configsLoaded()){
            FlowNodePort* inputstringport=getPortFromKey("stringInput");
            if(m_noInput){


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

            FlowNodePort* stringequal=getPortFromKey("stringEqual");
            FlowNodePort* stringnotequal=getPortFromKey("stringNotEqual");

            if(m_compareFromInput==false){

                SceneGraph* graph=qobject_cast<SceneGraph*>(this->getGraph());

                if(stringequal->getPortItem()->getOutEdgeItems().size()>0){

                    for (int var = 0; var < stringequal->getPortItem()->getOutEdgeItems().size(); ++var) {
                        qan::EdgeItem* edgeitem=stringequal->getPortItem()->getOutEdgeItems().at(var);
                        graph->deleteEdge(edgeitem->getEdge());
                    }

                }

                if(stringnotequal->getPortItem()->getOutEdgeItems().size()>0){

                    for (int var = 0; var < stringnotequal->getPortItem()->getOutEdgeItems().size(); ++var) {
                        qan::EdgeItem* edgeitem=stringnotequal->getPortItem()->getOutEdgeItems().at(var);
                        graph->deleteEdge(edgeitem->getEdge());
                    }

                }

                stringequal->setHidden(true);
                stringnotequal->setHidden(true);
            }
            else{
                stringequal->setHidden(false);
                stringnotequal->setHidden(false);
            }

            FlowNodePort* stringoutput=getPortFromKey("stringOutput");

            if(m_compareFromInput){


                SceneGraph* graph=qobject_cast<SceneGraph*>(this->getGraph());

                if(stringoutput->getPortItem()->getOutEdgeItems().size()>0){

                    qan::EdgeItem* edgeitem=stringoutput->getPortItem()->getOutEdgeItems().at(0);
                    graph->deleteEdge(edgeitem->getEdge());
                }

                stringoutput->setHidden(true);
            }
            else{
                stringoutput->setHidden(false);
            }



        }
    }


    bool m_prefixFromInput=false;

    bool m_suffixFromInput=false;

    bool m_extractFromInput=false;

    QVariant m_stringInput=QVariant::fromValue(QString(""));

    QVariant m_stringOutput=QVariant::fromValue(QString(""));



    bool m_compareFromInput=false;

    bool m_noInput=true;

    QVariant m_stringEqual=QVariant::fromValue(false);

    QVariant m_stringNotEqual=QVariant::fromValue(false);

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
    bool noInput() const
    {
        return m_noInput;
    }
    QVariant stringEqual() const
    {
        return m_stringEqual;
    }
    QVariant stringNotEqual() const
    {
        return m_stringNotEqual;
    }
};

#endif // STRINGNODE_H
