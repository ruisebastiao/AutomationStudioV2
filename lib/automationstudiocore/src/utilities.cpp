#include "utilities.h"

namespace as{

Utilities::Utilities(QObject *parent) : QObject(parent)
{
    runCommandProcess= new QProcess(parent);

}

void Utilities::executeCommand(QString command, bool waitfinished)
{
    //QProcess::start()
    runCommandProcess->start(command);
    if(waitfinished){
        runCommandProcess->waitForFinished();
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


}
