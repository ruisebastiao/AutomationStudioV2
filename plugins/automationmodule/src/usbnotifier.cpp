#include "usbnotifier.h"
#include "qquickwindow.h"

#include <qqmlengine.h>
#include <QQmlContext>
#include <qqmlapplicationengine.h>



USBNotifier::USBNotifier(QQuickItem *parent):QQuickItem (parent)
{

    m_eventfilter= new UsbEventFilter();
    //parent->window()->winId();
}

USBNotifier::~USBNotifier()
{

}

void USBNotifier::initialize()
{
#if defined(Q_OS_WIN32)
    GUID InterfaceClassGuid ={0x4d36e978,0xe325,0x11ce,0xbfc1,0x08002be10318};
    DEV_BROADCAST_DEVICEINTERFACE NotificationFilter;
    ZeroMemory( &NotificationFilter, sizeof(NotificationFilter) );
    NotificationFilter.dbcc_size = sizeof(DEV_BROADCAST_PORT);
    NotificationFilter.dbcc_devicetype = DBT_DEVTYP_PORT;
    NotificationFilter.dbcc_classguid = InterfaceClassGuid;

    QQmlApplicationEngine  *engine = (QQmlApplicationEngine*)QQmlEngine::contextForObject(this)->engine();;

    if(engine){
        QList<QObject*> m_rootObjects=engine->rootObjects();
        if(m_rootObjects.length()>0){
            QObject* m_rootObject = (QObject*)m_rootObjects.first();
            if(m_rootObject) {
                QWindow *window = qobject_cast<QWindow *>(m_rootObject);
                if(window) {
                    //                    window->nativeEvent();

                    //    window->
                    HWND hw = (HWND) window->winId();//Main window handle
                    if(hw){
                        HDEVNOTIFY  hDevNotify = RegisterDeviceNotification(hw,&NotificationFilter, DEVICE_NOTIFY_WINDOW_HANDLE);
                    }


                    coreApplication()->installNativeEventFilter(m_eventfilter);
                    connect(m_eventfilter,&UsbEventFilter::portAdded,this,[this](){
                       emit this->portAdded();

                    });
                    connect(m_eventfilter,&UsbEventFilter::portRemoved,this,[this](){
                       emit this->portRemoved();
                    });


                }
            }
        }


    }


    //HWND hw = (HWND) this->effectiveWinId();   //Main window handle
    //hDevNotify = RegisterDeviceNotification(hw,&NotificationFilter, DEVICE_NOTIFY_WINDOW_HANDLE);
#endif
}


void USBNotifier::componentComplete()
{
#if defined(Q_OS_WIN32)

#endif
    QQuickItem::componentComplete();
}

UsbEventFilter::UsbEventFilter()
{

}

bool UsbEventFilter::nativeEventFilter(const QByteArray &eventType, void *message, long *result)
{
    MSG * msg = static_cast< MSG * > (message);
    int msgType = msg->message;

    if(msgType == WM_DEVICECHANGE)
       {

          PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)msg->lParam;
          switch(msg->wParam)
          {
                case DBT_DEVICEARRIVAL: // never comes here!
                   if (lpdb -> dbch_devicetype == DBT_DEVTYP_PORT)
                   {
                       emit portAdded();
                   }
               break;
               case DBT_DEVICEREMOVECOMPLETE:
                   if (lpdb -> dbch_devicetype == DBT_DEVTYP_PORT)
                   {
                       emit portRemoved();
                   }
               break;
          case DBT_DEVICEREMOVEPENDING :
          {
//               qDebug() << "USBNotifier: DBT_DEVICEREMOVEPENDING case";
          }
          break;
          default:
          {
//              qDebug() << "USBNotifier: Went to Default case";
          }


          }
       }
       return false;
}
