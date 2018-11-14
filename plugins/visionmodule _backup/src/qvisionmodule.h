#ifndef QVISIONMODULE_H
#define QVISIONMODULE_H

#include "automationmodule/qautomationmodule.h"

class QVisionModule: public QAutomationModule
{
Q_OBJECT

public:
    QVisionModule(QQuickItem *parent=nullptr);

    // QAutomationModule interface
protected:
    void loadModuleSettings(QString path) override;
    void save() override;
    FlowNode *readNode(qan::GraphView *graphView, QJsonObject nodeobject) override;
};

#endif // QVISIONMODULE_H
