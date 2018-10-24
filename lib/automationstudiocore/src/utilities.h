#ifndef UTILITIES_H
#define UTILITIES_H

#include "automationstudiocoreglobal.h"


#include <QGuiApplication>
#include <QObject>
#include <QProcess>
#include <QQmlApplicationEngine>
#include <QQuickItem>

namespace as{


class AUTOMATIONSTUDIO_CORE_EXPORT Utilities : public QObject
{
    Q_OBJECT
public:
    explicit Utilities(QObject *parent = nullptr);

    Q_PROPERTY(bool controlPressed READ controlPressed WRITE setControlPressed NOTIFY controlPressedChanged)

    Q_INVOKABLE void executeCommand(QString command, bool waitfinished=false, QString cwd="", bool captureStdOut=false, bool detached=false, const std::function<void (QString out)> &execFunc=nullptr);
    Q_INVOKABLE bool fileExists(QString filepath);


    template<typename T>
    static QList<QString> QtEnumsToStrings (bool lowercase)
    {

        QList<QString> enums;

        int enumscount=QMetaEnum::fromType<T>().keyCount();

        for (int i = 0; i < enumscount; ++i) {
            std::string enum_str=std::string(QMetaEnum::fromType<T>().valueToKey(i));
            QString moduletypename=QString::fromUtf8(enum_str.c_str());
            if(lowercase){
                moduletypename=moduletypename.toLower();
            }

            enums.append(moduletypename);
        }

        return enums;
    }

    template<typename T>
    static T* find (QList<T*> &list,const char* key,QVariant value )
    {

        foreach (T* item, list) {

            if (item->property(key).isValid()) {

                QVariant propertyValue=item->property(key);

                if (propertyValue==value) {
                    return item;
                    break;
                }

            }
        }

        return nullptr;
    }

    bool controlPressed()     {

        m_controlPressed=(QGuiApplication::queryKeyboardModifiers() && Qt::ControlModifier);
        return m_controlPressed;
    }

private:
//    QProcess *runCommandProcess;

    bool m_controlPressed=false;

signals:


    void controlPressedChanged(bool controlPressed);

public slots:
    void setControlPressed(bool controlPressed)
    {
        if (m_controlPressed == controlPressed)
            return;

        m_controlPressed = controlPressed;
        emit controlPressedChanged(m_controlPressed);
    }

    // QObject interface
public:
    bool eventFilter(QObject *watched, QEvent *event);
    Q_INVOKABLE bool resourceExists(QString path);
    static void NonBlockingWait(int ms);
    static void NonBlockingExec(const std::function<void ()> &execFunc);

private slots:

};
}
#endif // UTILITIES_H
