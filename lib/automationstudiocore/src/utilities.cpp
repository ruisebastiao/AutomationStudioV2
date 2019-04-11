#include "utilities.h"
#include "Logger.h"

#include <QtConcurrent>





Utilities::Utilities(QObject *parent) : QObject(parent)
{

}




void Utilities::executeCommand(QString command,bool waitfinished,QString cwd,bool captureStdOut,bool detached,const std::function<void (QString out)>& execFunc)
{
    //QProcess::start()
    QProcess runCommandProcess;


    connect(&runCommandProcess, static_cast<void (QProcess::*)(int)>(&QProcess::finished), [](int exitStatus) {
        Q_UNUSED(exitStatus);
        LOG_INFO()<< "Process finished";
    });





    connect(&runCommandProcess,&QProcess::readyRead,[&](){
        QString str_stdout=runCommandProcess.readAllStandardOutput();
        QString str_stderr=runCommandProcess.readAllStandardError();
        if(str_stdout.length()>0){
            //            foreach (QString line, str_stdout.split("\n")) {

            //                if(line.length()>0){

            if(execFunc){
                execFunc(str_stdout);
            }
            //                }
            //            }
        }
        if(str_stderr.length()>0){
            //            foreach (QString line, str_stderr.split("\n")) {

            //                if(line.length()>0){


            if(execFunc){
                execFunc(str_stderr);
            }
            //                }
            //            }
        }

    });







    runCommandProcess.setWorkingDirectory(cwd);
    LOG_INFO()<< "Excuting command:"<<command;

    if(detached){
        runCommandProcess.startDetached("sh", QStringList() << "-c" << command);
    }
    else{
        runCommandProcess.start("sh", QStringList() << "-c" << command);
    }

    if(waitfinished){
        LOG_INFO()<< "Waiting process to finish";
        runCommandProcess.waitForFinished();
        //        QThread::msleep(1000);
        LOG_INFO()<< "Process finished";
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
        QThread::msleep(1);
        QCoreApplication::processEvents();
    }


}


SerializationUtilities* Utilities::serializationUtilities= new SerializationUtilities();
