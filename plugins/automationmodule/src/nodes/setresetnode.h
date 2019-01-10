#ifndef SETRESETNODE_H
#define SETRESETNODE_H

#include "flownode.h"



class SetResetNode: public FlowNode
{
    Q_OBJECT

    Q_PROPERTY(QVariant set READ set WRITE setSet NOTIFY setChanged REVISION 30)
    Q_PROPERTY(QVariant reset READ reset WRITE setReset NOTIFY resetChanged REVISION 30)
    Q_PROPERTY(QVariant output READ output WRITE setOutput NOTIFY outputChanged REVISION 31)



public:
    SetResetNode();
    static QQmlComponent *delegate(QQmlEngine &engine) noexcept;

    QVariant set() const
    {
        return m_set;
    }

    QVariant reset() const
    {
        return m_reset;
    }

    QVariant output() const
    {
        return m_output;
    }

public slots:
    void setSet(QVariant set)
    {


        m_set = set;

        if(set.value<bool>()){
            setOutput(true);
        }

        emit setChanged(m_set);
    }

    void setReset(QVariant reset)
    {


        m_reset = reset;
        if(m_reset.value<bool>()){
            setOutput(false);
        }
        emit resetChanged(m_reset);
    }

    void setOutput(QVariant output)
    {

        m_output = output;
        emit outputChanged(m_output);
    }

signals:
    void setChanged(QVariant set);

    void resetChanged(QVariant reset);

    void outputChanged(QVariant output);

private:

    QVariant m_set=QVariant::fromValue(false);
    QVariant m_reset=QVariant::fromValue(false);
    QVariant m_output=QVariant::fromValue(false);

};

#endif // SETRESETNODE_H
