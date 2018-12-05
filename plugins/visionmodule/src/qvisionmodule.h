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


    // QAutomationModule interface
public:
    FlowNode *createModuleNode(qan::GraphView *graphView, QString nodetype) override;
};

#endif // QVISIONMODULE_H
