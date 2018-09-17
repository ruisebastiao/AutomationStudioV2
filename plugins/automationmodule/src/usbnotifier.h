#ifndef USBNOTIFIER_H
#define USBNOTIFIER_H

#include <QFileSystemWatcher>
#include <QObject>
#include <QQuickItem>
#include <qabstractnativeeventfilter.h>

#if defined(Q_OS_WIN32)
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <strsafe.h>
#include <dbt.h>
#include <initguid.h>
#include <usbiodef.h>
#endif

#if defined(Q_OS_WIN32)
class UsbEventFilter;
#endif

class USBNotifier : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QCoreApplication* coreApplication READ coreApplication WRITE setCoreApplication NOTIFY coreApplicationChanged)


public:
    USBNotifier(QQuickItem* parent=nullptr);
    ~USBNotifier();

private:

#if defined(Q_OS_WIN32)


    // This GUID is for all USB serial host PnP drivers, but you can replace it
    // with any valid device class guid.
    GUID WceusbshGUID = { 0x25dbce51, 0x6c8f, 0x4a72,
                          0x8a,0x6d,0xb5,0x4c,0x2b,0x4f,0xc8,0x35 };


#endif

#if defined(Q_OS_WIN32)
        UsbEventFilter* m_eventfilter=nullptr;
#endif


#if defined(Q_OS_LINUX)
        QFileSystemWatcher* m_filesystemwatcher=nullptr;
#endif


    QCoreApplication* m_coreApplication=nullptr;
    void initialize();

signals:
    void portRemoved();
    void portAdded();

    void coreApplicationChanged(QCoreApplication* coreApplication);

public slots:


    // QQmlParserStatus interface
    void setCoreApplication(QCoreApplication* coreApplication)
    {
        if (m_coreApplication == coreApplication)
            return;


        m_coreApplication = coreApplication;
        if(m_coreApplication){
            initialize();
        }
        emit coreApplicationChanged(m_coreApplication);
    }

public:
    void componentComplete() override;
    QCoreApplication* coreApplication() const
    {
        return m_coreApplication;
    }
};
#if defined(Q_OS_WIN32)
class UsbEventFilter : public QObject,public QAbstractNativeEventFilter
{
    Q_OBJECT

public:
    UsbEventFilter();
    virtual bool nativeEventFilter(const QByteArray &eventType, void *message, long *result);
signals:
    void portRemoved();
    void portAdded();

};

#endif

#endif // USBNOTIFIER_H
