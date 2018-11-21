#ifndef MULTIPLEXEDINPUTNODE_H
#define MULTIPLEXEDINPUTNODE_H

#include "flownode.h"

#include <QObject>

class MultiplexedInputNode : public FlowNode
{
    Q_OBJECT


    /// IN ports

    Q_PROPERTY(QVariant in1 READ in1 WRITE setIn1 NOTIFY in1Changed REVISION 30)

    Q_PROPERTY(QVariant in2 READ in2 WRITE setIn2 NOTIFY in2Changed REVISION 30)


    /////OUT ports

    Q_PROPERTY(QVariant out READ out WRITE setOut NOTIFY outChanged REVISION 31)


private:


    QVariant m_in1=QVariant();
    QVariant m_in2=QVariant();
    QVariant m_out=QVariant();

public:
    MultiplexedInputNode();

    static QQmlComponent *delegate(QQmlEngine &engine) noexcept;
    QVariant in1() const
    {
        return m_in1;
    }
    QVariant in2() const
    {
        return m_in2;
    }


    QVariant out() const
    {
        return m_out;
    }


public slots:
    void setIn1(QVariant in1)
    {
        m_in1 = in1;
        setOut(m_in1);
        emit in1Changed(m_in1);
    }

    void setIn2(QVariant in2)
    {


        m_in2 = in2;
        setOut(m_in2);
        emit in2Changed(m_in2);
    }


    void setOut(QVariant out)
    {

        m_out = out;
        emit outChanged(m_out);
    }


signals:
    void in1Changed(QVariant in1);
    void in1PortChanged(FlowNodePort* in1Port);
    void in2Changed(QVariant in2);
    void in2PortChanged(FlowNodePort* in2Port);
    void outChanged(QVariant out);
    void outPortChanged(FlowNodePort* outPort);

    // JsonSerializable interface
public:
    void Serialize(QJsonObject &json) override;
    void DeSerialize(QJsonObject &json) override;

    // FlowNode interface
public:

};

#endif // MULTIPLEXEDINPUTNODE_H
