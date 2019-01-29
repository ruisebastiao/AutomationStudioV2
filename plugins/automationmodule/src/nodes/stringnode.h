#ifndef STRINGNODE_H
#define STRINGNODE_H

#include "flownode.h"

#include <QObject>

class StringNode : public FlowNode
{
    Q_OBJECT


    Q_PROPERTY(QVariant stringValue READ stringValue WRITE setStringValue NOTIFY stringValueChanged USER("serialize"))
    Q_PROPERTY(QVariant stringInput READ stringInput WRITE setStringInput NOTIFY stringInputChanged REVISION 30)
    Q_PROPERTY(QVariant stringInput2 READ stringInput2 WRITE setStringInput2 NOTIFY stringInput2Changed REVISION 30)

    Q_PROPERTY(QVariant stringOutput READ stringOutput WRITE setStringOutput NOTIFY stringOutputChanged REVISION 31)

    Q_PROPERTY(QVariant stringEqual READ stringEqual WRITE setStringEqual NOTIFY stringEqualChanged REVISION 31)
    Q_PROPERTY(QVariant stringNotEqual READ stringNotEqual WRITE setStringNotEqual NOTIFY stringNotEqualChanged REVISION 31)

    Q_PROPERTY(InputType inputType READ inputType WRITE setInputType NOTIFY inputTypeChanged USER("serialize"))





public:

    enum class InputType {

        InputNone,
        InputPrefix,
        InputSuffix,
        InputExtract,
        InputCompare,
        InputJoin


    };
    Q_ENUM(InputType)

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



        if(inputType()==InputType::InputPrefix){
            setStringOutput(stringValue.value<QString>()+m_stringInput.value<QString>());
        }
        else if(inputType()==InputType::InputSuffix){
            setStringOutput(m_stringInput.value<QString>()+stringValue.value<QString>());
        }
        else if(inputType()==InputType::InputExtract){
            updateExtract();
        }
        else if(inputType()==InputType::InputCompare){
            compareStrings();
        }
        else {
            setStringOutput(stringValue);
        }

        emit stringValueChanged(m_stringValue);
    }


    void setStringInput(QVariant stringInput)
    {

        m_stringInput = stringInput;
        emit stringInputChanged(m_stringInput);
        inputsChanged();
    }


    void setStringOutput(QVariant stringOutput)
    {
        m_stringOutput = stringOutput;
        emit stringOutputChanged(m_stringOutput);
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

    void setInputType(InputType inputType)
    {
        if (m_inputType == inputType)
            return;

        m_inputType = inputType;
        updateports();
        emit inputTypeChanged(m_inputType);
    }

    void setStringInput2(QVariant stringInput2)
    {


        m_stringInput2 = stringInput2;
        emit stringInput2Changed(m_stringInput2);
        inputsChanged();
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

    void inputTypeChanged(InputType inputType);

    void stringInput2Changed(QVariant stringInput2);

private:
    QVariant m_stringValue=QVariant::fromValue(QString(""));


    void inputsChanged(){
        if(inputType()==InputType::InputSuffix){
            setStringOutput(stringValue().value<QString>()+QVariant(m_stringInput).toString());
        }else if(inputType()==InputType::InputPrefix){
            setStringOutput(m_stringInput.value<QString>()+stringValue().value<QString>());
        }
        else if(inputType()==InputType::InputExtract) {
            updateExtract();
        }
        else if(inputType()==InputType::InputCompare){
            compareStrings();
        }
        else if(inputType()==InputType::InputJoin){
            QString inputstr=m_stringInput.value<QString>();
            QString inputstr2=m_stringInput2.value<QString>();

            QString joined=m_stringInput.value<QString>().append(m_stringValue.value<QString>()).append(inputstr2);
            setStringOutput(joined);
        }
    }

    void compareStrings(){
        QString inputstr=m_stringInput.value<QString>();
        QString stringvalue=m_stringValue.value<QString>();

        QString inputstr2=m_stringInput2.value<QString>();

        if(stringvalue!=""){
            inputstr2=stringvalue;
        }

        if(inputstr==inputstr2){
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
        //        else{
        //            setStringOutput(QString(""));
        //        }
    }
    void updateports(){

        if(configsLoaded()){
            FlowNodePort* inputstringport=getPortFromKey("stringInput");
            if(m_inputType==InputType::InputNone){


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

            FlowNodePort* inputstring2port=getPortFromKey("stringInput2");
            if(m_inputType==InputType::InputNone){


                SceneGraph* graph=qobject_cast<SceneGraph*>(this->getGraph());

                if(inputstring2port->getPortItem()->getInEdgeItems().size()>0){

                    qan::EdgeItem* edgeitem=inputstring2port->getPortItem()->getInEdgeItems().at(0);
                    graph->deleteEdge(edgeitem->getEdge());
                }

                inputstring2port->setHidden(true);
            }
            else{
                inputstring2port->setHidden(false);
            }

            FlowNodePort* stringequal=getPortFromKey("stringEqual");
            FlowNodePort* stringnotequal=getPortFromKey("stringNotEqual");

            if(m_inputType!=InputType::InputCompare){

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

            if(inputType()==InputType::InputCompare){


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



    QVariant m_stringInput=QVariant::fromValue(QString(""));

    QVariant m_stringOutput=QVariant::fromValue(QString(""));

    QVariant m_stringEqual=QVariant::fromValue(false);

    QVariant m_stringNotEqual=QVariant::fromValue(false);

    InputType m_inputType=InputType::InputNone;

    QVariant m_stringInput2=QString("");

public:
    void Serialize(QJsonObject &json) override;
    void DeSerialize(QJsonObject &json) override;


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

    QVariant stringEqual() const
    {
        return m_stringEqual;
    }
    QVariant stringNotEqual() const
    {
        return m_stringNotEqual;
    }
    InputType inputType() const
    {
        return m_inputType;
    }
    QVariant stringInput2() const
    {
        return m_stringInput2;
    }
};

#endif // STRINGNODE_H
