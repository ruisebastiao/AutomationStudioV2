#ifndef SIO_SOCKET_GLOBAL_H
#define SIO_SOCKET_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SIOCLIENT_LIBRARY)
#  define SIO_SOCKET_EXPORT Q_DECL_EXPORT
#else
#  define SIO_SOCKET_EXPORT Q_DECL_IMPORT
#endif

#endif // SIO_SOCKET_GLOBAL_H
