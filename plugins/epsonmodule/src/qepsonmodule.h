#ifndef QEPSONMODULE_H
#define QEPSONMODULE_H

#include "automationmodule/qautomationmodule.h"

class QEpsonModule: public QAutomationModule
{
Q_OBJECT

    QVariantList getModuleNodeTypes() const;
public:
    QEpsonModule(QQuickItem *parent=nullptr);


};

#endif // QEPSONMODULE_H
