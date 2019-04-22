#include "processnode.h"


ProcessNode::ProcessNode()
{
    m_type=Type::ProcessNode;


    minimizeTimer.setInterval(6000);
    minimizeTimer.setSingleShot(true);

    m_terminateTimer.setSingleShot(true);
    m_terminateTimer.setInterval(5000);

    m_delayStartTimer.setSingleShot(true);


    connect(&m_runCommandProcess, static_cast<void (QProcess::*)(int)>(&QProcess::finished), [this](int exitStatus) {
        Q_UNUSED(exitStatus);
        LOG_INFO()<< "Process "<<m_processPath<<" finished";
        this->setRunning(false);
        if(m_terminating==false && m_keepAlive){
              LOG_INFO()<< "Process "<<m_processPath<<" re-launching";
            this->setExecute(true);
        }
    });

    connect(&m_runCommandProcess, &QProcess::started, [this]() {

        LOG_INFO()<< "Process "<<m_processPath<<" started";
        this->setRunning(true);
    });

    QObject::connect(&m_terminateTimer, &QTimer::timeout,[this](){
        this->m_runCommandProcess.kill();
    });

    QObject::connect(&m_delayStartTimer, &QTimer::timeout,[this](){
        m_runCommandProcess.start(processPath().value<QString>());
    });


}

QQmlComponent*  ProcessNode::delegate(QQmlEngine& engine) noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/ProcessNodeItem.qml"));
    return delegate.get();
}
