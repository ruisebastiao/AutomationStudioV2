#ifndef MULTIPLEXEDINPUTNODE_H
#define MULTIPLEXEDINPUTNODE_H

#include "flownode.h"

#include <QObject>

class MultiplexedInputNode : public FlowNode
{
    Q_OBJECT


    /// IN ports

    Q_PROPERTY(QVariant in1 READ in1 WRITE setIn1 NOTIFY in1Changed )
    Q_PROPERTY(FlowNodePort* in1Port READ in1Port WRITE setIn1Port NOTIFY in1PortChanged USER("serialize"))

    Q_PROPERTY(QVariant in2 READ in2 WRITE setIn2 NOTIFY in2Changed )
    Q_PROPERTY(FlowNodePort* in2Port READ in2Port WRITE setIn2Port NOTIFY in2PortChanged USER("serialize"))


    /////OUT ports

    Q_PROPERTY(QVariant out READ out WRITE setOut NOTIFY outChanged)
    Q_PROPERTY(FlowNodePort* outPort READ outPort WRITE setOutPort NOTIFY outPortChanged USER("serialize"))

private:


    QVariant m_in1=QVariant();

    FlowNodePort* m_in1Port=nullptr;

    QVariant m_in2=QVariant();

    FlowNodePort* m_in2Port=nullptr;

    QVariant m_out=QVariant();

    FlowNodePort* m_outPort=nullptr;

public:
    MultiplexedInputNode();

    static QQmlComponent *delegate(QQmlEngine &engine) noexcept;
    QVariant in1() const
    {
        return m_in1;
    }
    FlowNodePort* in1Port() const
    {
        return m_in1Port;
    }

    QVariant in2() const
    {
        return m_in2;
    }

    FlowNodePort* in2Port() const
    {
        return m_in2Port;
    }

    QVariant out() const
    {
        return m_out;
    }

    FlowNodePort* outPort() const
    {
        return m_outPort;
    }

public slots:
    void setIn1(QVariant in1)
    {
        m_in1 = in1;
        setOut(m_in1);
        emit in1Changed(m_in1);
    }
    void setIn1Port(FlowNodePort* in1Port)
    {

        if (m_in1Port == in1Port)
            return;
        m_in1Port = in1Port;

        emit in1PortChanged(m_in1Port);
    }

    void setIn2(QVariant in2)
    {


        m_in2 = in2;
        setOut(m_in2);
        emit in2Changed(m_in2);
    }

    void setIn2Port(FlowNodePort* in2Port)
    {
        if (m_in2Port == in2Port)
            return;

        m_in2Port = in2Port;
        emit in2PortChanged(m_in2Port);
    }

    void setOut(QVariant out)
    {

        m_out = out;
        emit outChanged(m_out);
    }

    void setOutPort(FlowNodePort* outPort)
    {
        if (m_outPort == outPort)
            return;

        m_outPort = outPort;
        emit outPortChanged(m_outPort);
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
};

#endif // MULTIPLEXEDINPUTNODE_H
