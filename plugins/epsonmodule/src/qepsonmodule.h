#ifndef QEPSONMODULE_H
#define QEPSONMODULE_H

#include "automationmodule/qautomationmodule.h"

class QEpsonModule: public QAutomationModule
{
Q_OBJECT

    QVariantList getModuleNodeTypes() const;
public:
    QEpsonModule(QQuickItem *parent=nullptr);

    // QAutomationModule interface
protected:
    void loadModuleSettings(QString path) override;
    void save() override;


    // QAutomationModule interface
public:
    FlowNode *createModuleNode(qan::GraphView *graphView, QString nodetype) override;
};

#endif // QEPSONMODULE_H
