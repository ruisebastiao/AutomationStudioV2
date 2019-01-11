#ifndef LOGICNODE_H
#define LOGICNODE_H

#include "flownode.h"




class LogicNode : public FlowNode
{

    Q_OBJECT

    Q_PROPERTY(LogicalType logicalType READ logicalType WRITE setLogicalType NOTIFY logicalTypeChanged USER("serialize"))

    Q_PROPERTY(QVariant process READ process WRITE setProcess NOTIFY ProcessChanged REVISION 30)

    Q_PROPERTY(bool processOnInput READ processOnInput WRITE setProcessOnInput NOTIFY processOnInputChanged USER("serialize"))


    Q_PROPERTY(QVariant logicalInput1 READ logicalInput1 WRITE setLogicalInput1 NOTIFY logicalInput1Changed REVISION 30)


    Q_PROPERTY(QVariant logicalInput2 READ logicalInput2 WRITE setLogicalInput2 NOTIFY logicalInput2Changed REVISION 30)


    Q_PROPERTY(QVariant logicalOutput READ logicalOutput WRITE setLogicalOutput NOTIFY logicalOutputChanged REVISION 31)





public:
    enum LogicalType {

        OR=0,
        AND

    };
    Q_ENUM(LogicalType )

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

signals:
    void logicalTypeChanged(LogicalType logicalType);

    void logicalInput1Changed(QVariant logicalInput1);

    void logicalInput2Changed(QVariant logicalInput2);

    void logicalOutputChanged(QVariant logicalOutput);


    void ProcessChanged(QVariant process);

    void processOnInputChanged(bool processOnInput);

private:
    LogicalType m_logicalType=AND;

    QVariant m_logicalInput1=QVariant::fromValue(false);
    QVariant m_logicalInput2=QVariant::fromValue(false);
    QVariant m_logicalOutput=QVariant::fromValue(false);


    QVariant m_process=QVariant::fromValue(false);

    bool m_processOnInput=false;

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
};

#endif // LOGICNODE_H
