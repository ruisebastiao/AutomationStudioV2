#ifndef LOGICNODE_H
#define LOGICNODE_H

#include "flownode.h"




class LogicNode : public FlowNode
{

    Q_OBJECT

    Q_PROPERTY(LogicalType logicalType READ logicalType WRITE setLogicalType NOTIFY logicalTypeChanged USER("serialize"))

    Q_PROPERTY(QVariant process READ process WRITE setProcess NOTIFY ProcessChanged REVISION 30)

    Q_PROPERTY(bool processOnInput READ processOnInput WRITE setProcessOnInput NOTIFY processOnInputChanged USER("serialize"))

    Q_PROPERTY(int numInputs READ numInputs WRITE setNumInputs NOTIFY numInputsChanged USER("serialize"))

    Q_PROPERTY(QString outputValue READ outputValue WRITE setOutputValue NOTIFY outputValueChanged USER("serialize"))

    Q_PROPERTY(QVariant logicalInput1 READ logicalInput1 WRITE setLogicalInput1 NOTIFY logicalInput1Changed REVISION 30)


    Q_PROPERTY(QVariant logicalInput2 READ logicalInput2 WRITE setLogicalInput2 NOTIFY logicalInput2Changed REVISION 30)


    Q_PROPERTY(QVariant logicalInput3 READ logicalInput3 WRITE setLogicalInput3 NOTIFY logicalInput3Changed REVISION 30)

    Q_PROPERTY(QVariant logicalInput4 READ logicalInput4 WRITE setLogicalInput4 NOTIFY logicalInput4Changed REVISION 30)


    Q_PROPERTY(QVariant logicalOutput READ logicalOutput WRITE setLogicalOutput NOTIFY logicalOutputChanged REVISION 31)


    Q_PROPERTY(bool in1Enabled READ in1Enabled WRITE setIn1Enabled NOTIFY in1EnabledChanged USER("serialize"))
    Q_PROPERTY(bool in2Enabled READ in2Enabled WRITE setIn2Enabled NOTIFY in2EnabledChanged USER("serialize"))
    Q_PROPERTY(bool in3Enabled READ in3Enabled WRITE setIn3Enabled NOTIFY in3EnabledChanged USER("serialize"))
    Q_PROPERTY(bool in4Enabled READ in4Enabled WRITE setIn4Enabled NOTIFY in4EnabledChanged USER("serialize"))






public:
    enum LogicalType {

        OR=0,
        AND

    };
    Q_ENUMS(LogicalType)

    LogicNode();

    // ProcessingNode interface
    LogicalType logicalType() const
    {
        return m_logicalType;
    }

    QVariant logicalInput1() const
    {
        return m_logicalInput1;
    }



    QVariant logicalInput2() const
    {
        return m_logicalInput2;
    }


    QVariant logicalOutput() const
    {
        return m_logicalOutput;
    }


public slots:


    void setLogicalType(LogicalType logicalType)
    {
        if (m_logicalType == logicalType)
            return;

        m_logicalType = logicalType;
        emit logicalTypeChanged(m_logicalType);

        if(configsLoaded()){
            setProcess(true);
        }
    }

    void setLogicalInput1(QVariant logicalInput1)
    {

        m_logicalInput1 = logicalInput1;
        emit logicalInput1Changed(m_logicalInput1);

        setProcess(m_processOnInput);


    }


    void setLogicalInput2(QVariant logicalInput2)
    {

        m_logicalInput2 = logicalInput2;
        emit logicalInput2Changed(m_logicalInput2);

        setProcess(m_processOnInput);
    }



    void setLogicalOutput(QVariant logicalOutput)
    {


        m_logicalOutput = logicalOutput;
        emit logicalOutputChanged(m_logicalOutput);


    }

    void setProcess(QVariant process)
    {

        m_process = process;
        emit ProcessChanged(m_process);

        if(m_process.value<bool>()){
            if(configsLoaded() ){
                if(logicalType()==LogicalType::AND){
                    setLogicalOutput(m_logicalInput1==true && m_logicalInput2==true);
                }
                else if(logicalType()==LogicalType::OR){
                    setLogicalOutput(m_logicalInput1==true  || m_logicalInput2==true);
                }
            }

        }
    }

    void setProcessOnInput(bool processOnInput)
    {
        if (m_processOnInput == processOnInput)
            return;

        m_processOnInput = processOnInput;
        emit processOnInputChanged(m_processOnInput);
    }

    void setNumInputs(int numInputs)
    {
        if (m_numInputs == numInputs)
            return;

        m_numInputs = numInputs;
        emit numInputsChanged(m_numInputs);
    }

    void setOutputValue(QString outputValue)
    {
        if (m_outputValue == outputValue)
            return;

        m_outputValue = outputValue;
        emit outputValueChanged(m_outputValue);
    }

    void setLogicalInput3(QVariant logicalInput3)
    {


        m_logicalInput3 = logicalInput3;
        emit logicalInput3Changed(m_logicalInput3);
        setProcess(m_processOnInput);
    }

    void setLogicalInput4(QVariant logicalInput4)
    {


        m_logicalInput4 = logicalInput4;
        emit logicalInput4Changed(m_logicalInput4);
        setProcess(m_processOnInput);
    }

    void setIn1Enabled(bool in1Enabled)
    {
        if (m_in1Enabled == in1Enabled)
            return;

        m_in1Enabled = in1Enabled;
        emit in1EnabledChanged(m_in1Enabled);
        updateport("logicalInput1",in1Enabled);
    }

    void setIn2Enabled(bool in2Enabled)
    {
        if (m_in2Enabled == in2Enabled)
            return;

        m_in2Enabled = in2Enabled;
        emit in2EnabledChanged(m_in2Enabled);
        updateport("logicalInput2",in2Enabled);
    }

    void setIn3Enabled(bool in3Enabled)
    {
        if (m_in3Enabled == in3Enabled)
            return;

        m_in3Enabled = in3Enabled;
        emit in3EnabledChanged(m_in3Enabled);
        updateport("logicalInput3",in3Enabled);
    }

    void setIn4Enabled(bool in4Enabled)
    {
        if (m_in4Enabled == in4Enabled)
            return;

        m_in4Enabled = in4Enabled;
        emit in4EnabledChanged(m_in4Enabled);
        updateport("logicalInput4",in4Enabled);
    }

signals:
    void logicalTypeChanged(LogicalType logicalType);

    void logicalInput1Changed(QVariant logicalInput1);

    void logicalInput2Changed(QVariant logicalInput2);

    void logicalOutputChanged(QVariant logicalOutput);


    void ProcessChanged(QVariant process);

    void processOnInputChanged(bool processOnInput);

    void numInputsChanged(int numInputs);

    void outputValueChanged(QString outputValue);

    void logicalInput3Changed(QVariant logicalInput3);

    void logicalInput4Changed(QVariant logicalInput4);

    void in1EnabledChanged(bool in1Enabled);

    void in2EnabledChanged(bool in2Enabled);

    void in3EnabledChanged(bool in3Enabled);

    void in4EnabledChanged(bool in4Enabled);

private:
    LogicalType m_logicalType=AND;

    QVariant m_logicalInput1=QVariant::fromValue(false);
    QVariant m_logicalInput2=QVariant::fromValue(false);
    QVariant m_logicalOutput=QVariant::fromValue(false);


    QVariant m_process=QVariant::fromValue(false);

    bool m_processOnInput=false;

    int m_numInputs=2;

    QString m_outputValue="";

    QVariant m_logicalInput3=QVariant::fromValue(false);

    QVariant m_logicalInput4=QVariant::fromValue(false);

    bool m_in1Enabled=false;

    bool m_in2Enabled=false;

    bool m_in3Enabled=false;

    bool m_in4Enabled=false;

    void updateports();
    void updateport(QString portname, bool enabled);
protected:

    // JsonSerializable interface
public:
    void DeSerialize(QJsonObject &json) override;
    static QQmlComponent *delegate(QQmlEngine &engine) noexcept;

    // FlowNode interface
public:
    
    QVariant process() const
    {
        return m_process;
    }
    bool processOnInput() const
    {
        return m_processOnInput;
    }
    int numInputs() const
    {
        return m_numInputs;
    }
    QString outputValue() const
    {
        return m_outputValue;
    }
    QVariant logicalInput3() const
    {
        return m_logicalInput3;
    }
    QVariant logicalInput4() const
    {
        return m_logicalInput4;
    }
    bool in1Enabled() const
    {
        return m_in1Enabled;
    }
    bool in2Enabled() const
    {
        return m_in2Enabled;
    }
    bool in3Enabled() const
    {
        return m_in3Enabled;
    }
    bool in4Enabled() const
    {
        return m_in4Enabled;
    }
};

#endif // LOGICNODE_H
