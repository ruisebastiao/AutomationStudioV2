#ifndef QEPSONMODULE_H
#define QEPSONMODULE_H

#include "automationmodule/qautomationmodule.h"

class QEpsonModule: public QAutomationModule
{
Q_OBJECT

    QVariantList getModuleNodeTypes() const;

    Q_PROPERTY(bool startProduction READ startProduction WRITE setStartProduction NOTIFY startProductionChanged REVISION 2)
    Q_PROPERTY(bool stationReady READ stationReady WRITE setStationReady NOTIFY stationReadyChanged REVISION 2)

    Q_PROPERTY(bool stopProduction READ stopProduction WRITE setStopProduction NOTIFY stopProductionChanged REVISION 2)
    Q_PROPERTY(bool productionRunning READ productionRunning WRITE setProductionRunning NOTIFY productionRunningChanged REVISION 2)
    Q_PROPERTY(bool toolInDock READ toolInDock WRITE setToolInDock NOTIFY toolInDockChanged REVISION 2)



public:
    QEpsonModule(QQuickItem *parent=nullptr);




    bool startProduction() const
    {
        return m_startProduction;
    }

    bool stopProduction() const
    {
        return m_stopProduction;
    }

    bool productionRunning() const
    {
        return m_productionRunning;
    }

    bool toolInDock() const
    {
        return m_toolInDock;
    }

    bool stationReady() const
    {
        return m_stationReady;
    }

public slots:




    void setStartProduction(bool startProduction)
    {


        m_startProduction = startProduction;
        emit startProductionChanged(m_startProduction);
        m_startProduction=false;

    }

    void setStopProduction(bool stopProduction)
    {


        m_stopProduction = stopProduction;
        emit stopProductionChanged(m_stopProduction);
        m_stopProduction=false;

    }

    void setProductionRunning(bool productionRunning)
    {
        if (m_productionRunning == productionRunning)
            return;

        m_productionRunning = productionRunning;
        emit productionRunningChanged(m_productionRunning);
    }

    void setToolInDock(bool toolInDock)
    {
        if (m_toolInDock == toolInDock)
            return;

        m_toolInDock = toolInDock;
        emit toolInDockChanged(m_toolInDock);
    }

    void setStationReady(bool stationReady)
    {
        if (m_stationReady == stationReady)
            return;

        m_stationReady = stationReady;
        emit stationReadyChanged(m_stationReady);
    }

signals:


    void startProductionChanged(bool startProduction);

    void stopProductionChanged(bool stopProduction);

    void productionRunningChanged(bool productionRunning);

    void toolInDockChanged(bool toolInDock);

    void stationReadyChanged(bool stationReady);

private:



    bool m_startProduction=false;
    bool m_stopProduction=false;
    bool m_productionRunning=false;
    bool m_toolInDock=false;
    bool m_stationReady=false;
};

#endif // QEPSONMODULE_H
