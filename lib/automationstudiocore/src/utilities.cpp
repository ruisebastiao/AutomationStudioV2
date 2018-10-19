#include "utilities.h"
#include "Logger.h"

#include <QtConcurrent>

namespace as{

Utilities::Utilities(QObject *parent) : QObject(parent)
{
    runCommandProcess= new QProcess(parent);



    connect(runCommandProcess,&QProcess::readyReadStandardOutput,this,&Utilities::readyStandardOutput);

    connect(runCommandProcess,&QProcess::readyReadStandardOutput,this,&Utilities::readyStandardError);

    connect(runCommandProcess,SIGNAL(finished(int)),SLOT(processFinished(int)));




}




void Utilities::processFinished(int exitCode){
    LOG_INFO()<< "Process finished";
}

void Utilities::readyStandardOutput(){
    qDebug() << "StdOut> "+runCommandProcess->readAllStandardOutput();
}

void Utilities::readyStandardError(){
    qDebug()<< "StdErr> "+runCommandProcess->readAllStandardError();
}



void Utilities::executeCommand(QString command,bool waitfinished,QString cwd,bool captureStdOut)
{
    //QProcess::start()
    runCommandProcess->setWorkingDirectory(cwd);
    LOG_INFO()<< "Current dir"<<cwd;


    runCommandProcess->start("sh", QStringList() << "-c" << command);
    if(waitfinished){
        runCommandProcess->waitForFinished();
//        qDebug() << "StdErr> "+runCommandProcess->readAllStandardError();
//        qDebug() << "StdOut> "+runCommandProcess->readAllStandardOutput();
    }
}

bool Utilities::resourceExists(QString path){

    return  QFile::exists(path);
}

bool Utilities::fileExists(QString filepath)
{
    QUrl fileurl(filepath);
    QFile filecheck(fileurl.toLocalFile());

    if(!filecheck.exists()) {
        return false;
    }

    return true;
}

bool Utilities::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease)
    {
        setControlPressed(Qt::ControlModifier == QGuiApplication::queryKeyboardModifiers());
    }
    return false; // Pass the event along (don't consume it)
}




void Utilities::NonBlockingExec(std::function<void ()> const& execFunc){

    bool done=false;

    QtConcurrent::run([&](){


        execFunc();
        done=true;

    });


    while (!done){
        QThread::msleep(10);
        QCoreApplication::processEvents();
    }


}

void Utilities::NonBlockingWait(int ms){

    bool done=false;

    QtConcurrent::run([&](){


        QThread::msleep(ms);
        done=true;

    });


    while (!done){
        QThread::msleep(10);
        QCoreApplication::processEvents();
    }


}

}
