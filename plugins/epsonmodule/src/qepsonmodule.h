#ifndef QEPSONMODULE_H
#define QEPSONMODULE_H

#include "automationmodule/qautomationmodule.h"

class QEpsonModule: public QAutomationModule
{
Q_OBJECT

public:
    QEpsonModule(QQuickItem *parent=nullptr);

    // QAutomationModule interface
protected:
    void loadModuleSettings(QString path) override;
    void save() override;
    FlowNode *readNode(qan::GraphView *graphView, QJsonObject nodeobject) override;
};

#endif // QEPSONMODULE_H
