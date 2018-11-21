#ifndef PROCESSINGLOGICALNODE_H
#define PROCESSINGLOGICALNODE_H

#include "processingnode.h"




class ProcessingLogicalNode : public ProcessingNode
{

    Q_OBJECT

    Q_PROPERTY(LogicalType logicalType READ logicalType WRITE setLogicalType NOTIFY logicalTypeChanged USER("serialize"))

    Q_PROPERTY(bool logicalInput1 READ logicalInput1 WRITE setLogicalInput1 NOTIFY logicalInput1Changed REVISION 30)


    Q_PROPERTY(bool logicalInput2 READ logicalInput2 WRITE setLogicalInput2 NOTIFY logicalInput2Changed REVISION 30)



    Q_PROPERTY(bool logicalOutput READ logicalOutput WRITE setLogicalOutput NOTIFY logicalOutputChanged REVISION 31)





public:
    enum LogicalType {

        OR=0,
        AND

    };
    Q_ENUM(LogicalType )

    ProcessingLogicalNode();

    // ProcessingNode interface
    LogicalType logicalType() const
    {
        return m_logicalType;
    }

    bool logicalInput1() const
    {
        return m_logicalInput1;
    }



    bool logicalInput2() const
    {
        return m_logicalInput2;
    }


    bool logicalOutput() const
    {
        return m_logicalOutput;
    }


public slots:
    void setInput(QMat *input) override;

    void setLogicalType(LogicalType logicalType)
    {
        if (m_logicalType == logicalType)
            return;

        m_logicalType = logicalType;
        emit logicalTypeChanged(m_logicalType);
    }

    void setLogicalInput1(bool logicalInput1)
    {

        m_logicalInput1 = logicalInput1;
        emit logicalInput1Changed(m_logicalInput1);
        doProcess();
    }


    void setLogicalInput2(bool logicalInput2)
    {

        m_logicalInput2 = logicalInput2;
        emit logicalInput2Changed(m_logicalInput2);

        doProcess();        
    }



    void setLogicalOutput(bool logicalOutput)
    {


        m_logicalOutput = logicalOutput;
        if(m_logicalOutput){
            emit logicalOutputChanged(m_logicalOutput);
            m_logicalOutput=false;
            m_logicalInput1=false;
            m_logicalInput2=false;
        }

    }

signals:
    void logicalTypeChanged(LogicalType logicalType);

    void logicalInput1Changed(bool logicalInput1);

    void logicalInput2Changed(bool logicalInput2);

    void logicalOutputChanged(bool logicalOutput);


private:
    LogicalType m_logicalType=AND;

    bool m_logicalInput1=false;
    bool m_logicalInput2=false;
    bool m_logicalOutput=false;


protected:
    void doProcess() override;

    // JsonSerializable interface
public:
    void DeSerialize(QJsonObject &json) override;
    static QQmlComponent *delegate(QQmlEngine &engine) noexcept;

    // FlowNode interface
public:
    
};

#endif // PROCESSINGLOGICALNODE_H
