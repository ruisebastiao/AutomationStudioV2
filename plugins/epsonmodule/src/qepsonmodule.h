#ifndef QEPSONMODULE_H
#define QEPSONMODULE_H

#include "automationmodule/qautomationmodule.h"

class QEpsonModule: public QAutomationModule
{
Q_OBJECT

    QVariantList getModuleNodeTypes() const;

    Q_PROPERTY(QVariant startProduction READ startProduction WRITE setStartProduction NOTIFY startProductionChanged REVISION 2)
    Q_PROPERTY(QVariant stationReady READ stationReady WRITE setStationReady NOTIFY stationReadyChanged REVISION 2)

    Q_PROPERTY(QVariant stopProduction READ stopProduction WRITE setStopProduction NOTIFY stopProductionChanged REVISION 2)
    Q_PROPERTY(QVariant productionRunning READ productionRunning WRITE setProductionRunning NOTIFY productionRunningChanged REVISION 2)
    Q_PROPERTY(QVariant productionStarting READ productionStarting WRITE setProductionStarting NOTIFY productionStartingChanged REVISION 2)

    Q_PROPERTY(QVariant toolInDock READ toolInDock WRITE setToolInDock NOTIFY toolInDockChanged REVISION 2)






public:
    QEpsonModule(QQuickItem *parent=nullptr);




    QVariant startProduction() const
    {

        return m_startProduction;
    }

    QVariant stopProduction() const
    {
        return m_stopProduction;
    }

    QVariant productionRunning() const
    {
        return m_productionRunning;
    }

    QVariant toolInDock() const
    {
        return m_toolInDock;
    }

    QVariant stationReady() const
    {
        return m_stationReady;
    }

    QVariant productionStarting() const
    {
        return m_productionStarting;
    }



public slots:




    void setStartProduction(QVariant startProduction)
    {


        m_startProduction = startProduction;
        emit startProductionChanged(m_startProduction);
        m_startProduction=false;

    }

    void setStopProduction(QVariant stopProduction)
    {


        m_stopProduction = stopProduction;
        emit stopProductionChanged(m_stopProduction);
        m_stopProduction=false;

    }

    void setProductionRunning(QVariant productionRunning)
    {

        m_productionRunning = productionRunning;
        emit productionRunningChanged(m_productionRunning);
    }

    void setToolInDock(QVariant toolInDock)
    {
        if (m_toolInDock == toolInDock)
            return;

        m_toolInDock = toolInDock;
        emit toolInDockChanged(m_toolInDock);
    }

    void setStationReady(QVariant stationReady)
    {
        if (m_stationReady == stationReady)
            return;

        m_stationReady = stationReady;
        emit stationReadyChanged(m_stationReady);
    }

    void setProductionStarting(QVariant productionStarting)
    {
        if (m_productionStarting == productionStarting)
            return;

        m_productionStarting = productionStarting;
        emit productionStartingChanged(m_productionStarting);
    }


signals:


    void startProductionChanged(QVariant startProduction);

    void stopProductionChanged(QVariant stopProduction);

    void productionRunningChanged(QVariant productionRunning);

    void toolInDockChanged(QVariant toolInDock);

    void stationReadyChanged(QVariant stationReady);

    void productionStartingChanged(QVariant productionStarting);



private:



    QVariant m_startProduction=false;
    QVariant m_stopProduction=false;
    QVariant m_productionRunning=false;
    QVariant m_toolInDock=false;
    QVariant m_stationReady=false;
    QVariant m_productionStarting=false;

};

#endif // QEPSONMODULE_H
