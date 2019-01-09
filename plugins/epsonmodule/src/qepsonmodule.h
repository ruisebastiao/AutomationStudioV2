#ifndef QEPSONMODULE_H
#define QEPSONMODULE_H

#include "automationmodule/qautomationmodule.h"

class QEpsonModule: public QAutomationModule
{
Q_OBJECT

    QVariantList getModuleNodeTypes() const;

    Q_PROPERTY(bool productionStarted READ productionStarted WRITE setProductionStarted NOTIFY productionStartedChanged REVISION 2)
    Q_PROPERTY(bool startProduction READ startProduction WRITE setStartProduction NOTIFY startProductionChanged REVISION 2)
    Q_PROPERTY(bool stopProduction READ stopProduction WRITE setStopProduction NOTIFY stopProductionChanged REVISION 2)



public:
    QEpsonModule(QQuickItem *parent=nullptr);


    bool productionStarted() const
    {
        return m_productionStarted;
    }

    bool startProduction() const
    {
        return m_startProduction;
    }

    bool stopProduction() const
    {
        return m_stopProduction;
    }

public slots:
    void setProductionStarted(bool productionStarted)
    {

        m_productionStarted = productionStarted;
        emit productionStartedChanged(m_productionStarted);

    }




    void setStartProduction(bool startProduction)
    {


        m_startProduction = startProduction;
        emit startProductionChanged(m_startProduction);

    }

    void setStopProduction(bool stopProduction)
    {


        m_stopProduction = stopProduction;
        emit stopProductionChanged(m_stopProduction);

    }

signals:
    void productionStartedChanged(bool productionStarted);

    void startProductionChanged(bool startProduction);

    void stopProductionChanged(bool stopProduction);

private:


    bool m_productionStarted=false;
    bool m_startProduction=false;
    bool m_stopProduction=false;
};

#endif // QEPSONMODULE_H
