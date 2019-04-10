#ifndef STRINGNODE_H
#define STRINGNODE_H

#include "flownode.h"

#include <QObject>

class StringNode : public FlowNode
{
    Q_OBJECT


    Q_PROPERTY(QVariant stringValue READ stringValue WRITE setStringValue NOTIFY stringValueChanged USER("serialize"))
    Q_PROPERTY(QString storedValue READ storedValue WRITE setStoredValue NOTIFY storedValueChanged USER("serialize"))

    Q_PROPERTY(QVariant stringInput READ stringInput WRITE setStringInput NOTIFY stringInputChanged REVISION 30)
    Q_PROPERTY(QVariant stringInput2 READ stringInput2 WRITE setStringInput2 NOTIFY stringInput2Changed REVISION 30)

    Q_PROPERTY(QVariant stringOutput READ stringOutput WRITE setStringOutput NOTIFY stringOutputChanged REVISION 31)

    Q_PROPERTY(QVariant stringEqual READ stringEqual WRITE setStringEqual NOTIFY stringEqualChanged REVISION 31)
    Q_PROPERTY(QVariant stringNotEqual READ stringNotEqual WRITE setStringNotEqual NOTIFY stringNotEqualChanged REVISION 31)

    Q_PROPERTY(QVariant stringLessThen READ stringLessThen WRITE setStringLessThen NOTIFY stringLessThenChanged REVISION 31)
    Q_PROPERTY(QVariant stringGreaterThen READ stringGreaterThen WRITE setStringGreaterThen NOTIFY stringGreaterThenChanged REVISION 31)


    Q_PROPERTY(InputType inputType READ inputType WRITE setInputType NOTIFY inputTypeChanged USER("serialize"))


    Q_PROPERTY(QVariant processInputs READ processInputs WRITE setProcessInputs NOTIFY processInputsChanged REVISION 30)

    Q_PROPERTY(bool processOnInput READ processOnInput WRITE setProcessOnInput NOTIFY processOnInputChanged USER("serialize"))





public:

    enum class InputType {
        InputNotSet,
        InputNone,
        InputPrefix,
        InputSuffix,
        InputExtract,
        InputCompare,
        InputJoin,
        InputSerialize,
        InputParse,
        InputReadFile,
        InputWriteFile
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

        emit stringValueChanged(m_stringValue);
        inputsChanged(m_processOnInput);


    }


    void setStringInput(QVariant stringInput)
    {

        m_stringInput = stringInput;
        emit stringInputChanged(m_stringInput);
        inputsChanged(m_processOnInput && connectionsLoaded());
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
        inputsChanged(true);
    }

    void setStringInput2(QVariant stringInput2)
    {


        m_stringInput2 = stringInput2;
        emit stringInput2Changed(m_stringInput2);

        inputsChanged(m_processOnInput && connectionsLoaded());
    }

    void setStoredValue(QString storedValue)
    {
        if (m_storedValue == storedValue)
            return;

        m_storedValue = storedValue;
        emit storedValueChanged(m_storedValue);
    }

    void setStringLessThen(QVariant stringLessThen)
    {
        m_stringLessThen = stringLessThen;

        if(m_stringLessThen==true){
            setStringOutput(m_stringInput2);
        }
        emit stringLessThenChanged(m_stringLessThen);
    }

    void setStringGreaterThen(QVariant stringGreaterThen)
    {

        m_stringGreaterThen = stringGreaterThen;
        if(m_stringGreaterThen==true){
            setStringOutput(m_stringInput);
        }

        emit stringGreaterThenChanged(m_stringGreaterThen);
    }

    void setProcessInputs(QVariant processInputs)
    {


        m_processInputs = processInputs;


        bool doprocess=m_processInputs.value<bool>();
        inputsChanged(doprocess);


        emit processInputsChanged(m_processInputs);
        m_processInputs=false;
    }

    void setProcessOnInput(bool processOnInput)
    {
        if (m_processOnInput == processOnInput)
            return;

        m_processOnInput = processOnInput;
        emit processOnInputChanged(m_processOnInput);
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

    void storedValueChanged(QString storedValue);

    void stringLessThenChanged(QVariant stringLessThen);

    void stringGreaterThenChanged(QVariant stringGreaterThen);

    void processInputsChanged(QVariant processInputs);

    void processOnInputChanged(bool processOnInput);

private:
    QVariant m_stringValue=QVariant::fromValue(QString(""));


    QString serialize_input(){

        if(m_stringInput.canConvert<QString>()){
            return  m_stringInput.toString();
        }
        else {
            if(m_stringInput.canConvert<QLineF>()){
                QLineF linef=m_stringInput.value<QLineF>();

                return Utilities::serializationUtilities->serialize(linef);


            }
            else{
                return Utilities::serializationUtilities->serialize(m_stringInput);
            }
            //            else if(m_stringInput.canConvert<QLineF>()){

            //            }
        }

        return "Invalid input:"+QString(m_stringInput.typeName());
    }

    void inputsChanged(bool process);

    void compareStrings(){
        QString inputstr=m_stringInput.value<QString>();
        QString stringvalue=m_stringValue.value<QString>();

        QString inputstr2=m_stringInput2.value<QString>();

        if(stringvalue!=""){
            inputstr2=stringvalue;
        }

        if(inputstr==inputstr2){
            setStringEqual(true);
            setStringOutput(m_stringInput);
        }
        else {
            setStringEqual(false);
        }

        if(m_stringInput.canConvert<double>() && m_stringInput2.canConvert<double>()){
            double in1,in2;

            in1=m_stringInput.value<double>();
            in2=m_stringInput2.value<double>();

            setStringLessThen(in1<in2);
            setStringGreaterThen(in1>in2);

        }
        else{
            setStringLessThen(false);
            setStringGreaterThen(false);
        }

    }


    void updateExtract(){

        QString inputstr=m_stringInput.value<QString>();
        QString regstr=m_stringValue.value<QString>();
        QRegularExpression re(regstr);

        QRegularExpressionMatch match = re.match(inputstr);

        bool hasMatch = match.hasMatch(); // true


        if (hasMatch){
            qDebug()<<"Match:"<<match;

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
            if(m_inputType==InputType::InputNone || m_inputType==InputType::InputSerialize || m_inputType==InputType::InputParse || m_inputType==InputType::InputReadFile){


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
            if(!stringequal){
                return;
            }
            FlowNodePort* stringnotequal=getPortFromKey("stringNotEqual");

            if(!stringnotequal){
                return;
            }

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


            FlowNodePort* stringless=getPortFromKey("stringLessThen");
            if(!stringequal){
                return;
            }
            FlowNodePort* stringgreater=getPortFromKey("stringGreaterThen");

            if(!stringgreater){
                return;
            }

            if(m_inputType!=InputType::InputCompare){

                SceneGraph* graph=qobject_cast<SceneGraph*>(this->getGraph());

                if(stringless->getPortItem()->getOutEdgeItems().size()>0){

                    for (int var = 0; var < stringless->getPortItem()->getOutEdgeItems().size(); ++var) {
                        qan::EdgeItem* edgeitem=stringless->getPortItem()->getOutEdgeItems().at(var);
                        graph->deleteEdge(edgeitem->getEdge());
                    }

                }

                if(stringgreater->getPortItem()->getOutEdgeItems().size()>0){

                    for (int var = 0; var < stringgreater->getPortItem()->getOutEdgeItems().size(); ++var) {
                        qan::EdgeItem* edgeitem=stringgreater->getPortItem()->getOutEdgeItems().at(var);
                        graph->deleteEdge(edgeitem->getEdge());
                    }

                }

                stringless->setHidden(true);
                stringgreater->setHidden(true);
            }
            else{
                stringless->setHidden(false);
                stringgreater->setHidden(false);
            }

            FlowNodePort* stringoutput=getPortFromKey("stringOutput");

//            if(inputType()==InputType::InputCompare){


//                SceneGraph* graph=qobject_cast<SceneGraph*>(this->getGraph());

//                if(stringoutput->getPortItem()->getOutEdgeItems().size()>0){

//                    qan::EdgeItem* edgeitem=stringoutput->getPortItem()->getOutEdgeItems().at(0);
//                    graph->deleteEdge(edgeitem->getEdge());
//                }

//                stringoutput->setHidden(true);
//            }
//            else{
                stringoutput->setHidden(false);
//            }



        }
    }



    QVariant m_stringInput=QVariant::fromValue(QString(""));

    QVariant m_stringOutput=QVariant::fromValue(QString(""));

    QVariant m_stringEqual=QVariant::fromValue(false);

    QVariant m_stringNotEqual=QVariant::fromValue(false);

    InputType m_inputType=InputType::InputNotSet;

    QVariant m_stringInput2=QString("");

    QString m_storedValue="";

    QVariant m_stringLessThen;

    QVariant m_stringGreaterThen;

    QVariant m_processInputs=false;

    bool m_processOnInput=true;

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
    QString storedValue() const
    {
        return m_storedValue;
    }
    QVariant stringLessThen() const
    {
        return m_stringLessThen;
    }
    QVariant stringGreaterThen() const
    {
        return m_stringGreaterThen;
    }
    QVariant processInputs() const
    {
        return m_processInputs;
    }
    bool processOnInput() const
    {
        return m_processOnInput;
    }
};

#endif // STRINGNODE_H
