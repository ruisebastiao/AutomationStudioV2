#ifndef CVSERIALIZATION_H
#define CVSERIALIZATION_H

#include "qobject.h"
#include <qvariant.h>
#include "processingnode.h"

class cvSerialization
{
public:
    cvSerialization(QObject* parent=nullptr);
    QString serializer(QVariant value) const;
};

#endif // CVSERIALIZATION_H
