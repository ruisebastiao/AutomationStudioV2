#ifndef QVISIONMODULE_H
#define QVISIONMODULE_H

#include "automationmodule/qautomationmodule.h"

class QVisionModule: public QAutomationModule
{
Q_OBJECT

    QVariantList getModuleNodeTypes() const;
public:
    QVisionModule(QQuickItem *parent=nullptr);
};

#endif // QVISIONMODULE_H
