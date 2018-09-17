#ifndef QBSVALIDATIONMODULE_H
#define QBSVALIDATIONMODULE_H

#include <QQuickItem>
#include <qautomationmodule.h>

class QBSValidationModule : public QAutomationModule
{
    Q_OBJECT


public:
    QBSValidationModule(QQuickItem *parent=nullptr);

signals:

public slots:

    // QAutomationModule interface
protected:
    void load(QString path) override;

    // QAutomationModule interface
protected:
    FlowNode *readNode(qan::GraphView *graphView, QJsonObject nodeobject) override;

    // QAutomationModule interface
protected:
    void save() override;
};

#endif // QBSVALIDATIONMODULE_H
