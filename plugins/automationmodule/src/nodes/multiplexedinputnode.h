#ifndef MULTIPLEXEDINPUTNODE_H
#define MULTIPLEXEDINPUTNODE_H

#include "flownode.h"

#include <QObject>

class MultiplexedInputNode : public FlowNode
{
    Q_OBJECT

    Q_PROPERTY(bool autoExclusive READ autoExclusive WRITE setAutoExclusive NOTIFY autoExclusiveChanged USER("serialize"))


    /// IN ports

    Q_PROPERTY(QVariant in1 READ in1 WRITE setIn1 NOTIFY in1Changed REVISION 30)

    Q_PROPERTY(QVariant in2 READ in2 WRITE setIn2 NOTIFY in2Changed REVISION 30)

    Q_PROPERTY(QVariant in1Enabled READ in1Enabled WRITE setIn1Enabled NOTIFY in1EnabledChanged REVISION 30)

    Q_PROPERTY(QVariant in2Enabled READ in2Enabled WRITE setIn2Enabled NOTIFY in2EnabledChanged REVISION 30)



    /////OUT ports

    Q_PROPERTY(QVariant out READ out WRITE setOut NOTIFY outChanged REVISION 31)


private:


    QVariant m_in1=QVariant();
    QVariant m_in2=QVariant();
    QVariant m_out=QVariant();

    QVariant m_in1Enabled=false;

    QVariant m_in2Enabled=false;

    bool m_autoExclusive=true;

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

        if(m_in1Enabled.value<bool>()){
            setOut(m_in1);
        }
        emit in1Changed(m_in1);
    }

    void setIn2(QVariant in2)
    {


        m_in2 = in2;
        if(m_in2Enabled.value<bool>()){
            setOut(m_in2);
        }
        emit in2Changed(m_in2);
    }


    void setOut(QVariant out)
    {

        m_out = out;
        emit outChanged(m_out);
    }


    void setIn1Enabled(QVariant in1Enabled)
    {


        m_in1Enabled = in1Enabled;

        if(m_in1Enabled.value<bool>() && autoExclusive()){
            setIn2Enabled(false);
        }

        emit in1EnabledChanged(m_in1Enabled);
    }

    void setIn2Enabled(QVariant in2Enabled)
    {

        m_in2Enabled = in2Enabled;

        if(m_in2Enabled.value<bool>() && autoExclusive()){
            setIn1Enabled(false);
        }
        emit in2EnabledChanged(m_in2Enabled);
    }

    void setAutoExclusive(bool autoExclusive)
    {
        if (m_autoExclusive == autoExclusive)
            return;

        m_autoExclusive = autoExclusive;
        emit autoExclusiveChanged(m_autoExclusive);
    }

signals:
    void in1Changed(QVariant in1);
    void in1PortChanged(FlowNodePort* in1Port);
    void in2Changed(QVariant in2);
    void in2PortChanged(FlowNodePort* in2Port);
    void outChanged(QVariant out);
    void outPortChanged(FlowNodePort* outPort);

    // JsonSerializable interface
    void in1EnabledChanged(QVariant in1Enabled);

    void in2EnabledChanged(QVariant in2Enabled);

    void autoExclusiveChanged(bool autoExclusive);

public:
    void Serialize(QJsonObject &json) override;
    void DeSerialize(QJsonObject &json) override;

    // FlowNode interface
public:

    QVariant in1Enabled() const
    {
        return m_in1Enabled;
    }
    QVariant in2Enabled() const
    {
        return m_in2Enabled;
    }
    bool autoExclusive() const
    {
        return m_autoExclusive;
    }
};

#endif // MULTIPLEXEDINPUTNODE_H
