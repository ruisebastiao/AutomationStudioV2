#ifndef PROCESSNODE_H
#define PROCESSNODE_H

#include "flownode.h"

#include <QObject>
#include <QWindow>
#ifdef Q_OS_WIN
#include <windows.h>
#endif


class ProcessNode : public FlowNode
{
    Q_OBJECT

    Q_PROPERTY(bool keepAlive READ keepAlive WRITE setKeepAlive NOTIFY keepAliveChanged USER("serialize"))
    Q_PROPERTY(bool forceTerminate READ forceTerminate WRITE setForceTerminate NOTIFY forceTerminateChanged USER("serialize"))
    Q_PROPERTY(int delayStart READ delayStart WRITE setDelayStart NOTIFY delayStartChanged USER("serialize"))

    Q_PROPERTY(QVariant execute READ execute WRITE setExecute NOTIFY executeChanged REVISION 30)
    Q_PROPERTY(QVariant terminate READ terminate WRITE setTerminate NOTIFY terminateChanged REVISION 30)
    Q_PROPERTY(QVariant processPath READ processPath WRITE setProcessPath NOTIFY processPathChanged REVISION 30)

    Q_PROPERTY(QVariant running READ running WRITE setRunning NOTIFY runningChanged REVISION 31)

private:


    QVariant m_processPath=QString("");

    QVariant m_execute=false;

    QVariant m_running=false;


    QProcess m_runCommandProcess;

    QTimer m_terminateTimer;
    QTimer m_delayStartTimer;



    bool m_terminating=false;
    bool m_keepAlive=false;

    QVariant m_terminate=false;

    bool m_forceTerminate=false;

    int m_delayStart=0;

    QTimer minimizeTimer;
public:
    ProcessNode();

    static  QQmlComponent*      delegate(QQmlEngine& engine) noexcept;


    QVariant processPath() const
    {
        return m_processPath;
    }
    QVariant execute() const
    {
        return m_execute;
    }

    QVariant running() const
    {
        return m_running;
    }

    bool keepAlive() const
    {
        return m_keepAlive;
    }

    QVariant terminate() const
    {
        return m_terminate;
    }

    bool forceTerminate() const
    {
        return m_forceTerminate;
    }

    int delayStart() const
    {
        return m_delayStart;
    }

public slots:
    void setProcessPath(QVariant processPath)
    {

        m_processPath = processPath;
        emit processPathChanged(m_processPath);
    }
    void setExecute(QVariant excute)
    {

        if(excute==true && running()==false){

            LOG_INFO()<< "Process "<<m_processPath<<" starting";
            m_delayStartTimer.start(m_delayStart);

        }
        m_execute = excute;
        emit executeChanged(m_execute);
    }

    void setRunning(QVariant running)
    {
        m_running = running;
        if(m_running.value<bool>()){


            connect(&minimizeTimer,&QTimer::timeout,this,[](){


                for ( QWindow* appWindow : qApp->allWindows() )
                {
                    appWindow->showMaximized(); //bring window to top on OSX
                    appWindow->requestActivate(); //bring window to front/unminimize on windows
                }


            });

            minimizeTimer.start();

        }


        emit runningChanged(m_running);
    }

    void setKeepAlive(bool keepAlive)
    {
        if (m_keepAlive == keepAlive)
            return;

        m_keepAlive = keepAlive;
        emit keepAliveChanged(m_keepAlive);
    }

    void setTerminate(QVariant terminate)
    {
        if(terminate==true){
            m_terminating=true;
            m_runCommandProcess.terminate();
            m_terminateTimer.start();


        }


        m_terminate = terminate;
        emit terminateChanged(m_terminate);
    }

    void setForceTerminate(bool forceTerminate)
    {
        if (m_forceTerminate == forceTerminate)
            return;

        m_forceTerminate = forceTerminate;
        emit forceTerminateChanged(m_forceTerminate);
    }

    void setDelayStart(int delayStart)
    {
        if (m_delayStart == delayStart)
            return;

        m_delayStart = delayStart;
        emit delayStartChanged(m_delayStart);
    }

signals:
    void processPathChanged(QVariant processPath);
    void executeChanged(QVariant excute);
    void runningChanged(QVariant running);
    void keepAliveChanged(bool keepAlive);
    void terminateChanged(QVariant terminate);
    void forceTerminateChanged(bool forceTerminate);
    void delayStartChanged(int delayStart);
};

#endif // PROCESSNODE_H
