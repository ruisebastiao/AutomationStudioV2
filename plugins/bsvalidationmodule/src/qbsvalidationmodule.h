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
};

#endif // QBSVALIDATIONMODULE_H
