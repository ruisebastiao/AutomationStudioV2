#ifndef QAUTOMATIONPROJECT_H
#define QAUTOMATIONPROJECT_H

#include <QObject>

class QAutomationProject : public QObject
{
    Q_OBJECT
public:
    explicit QAutomationProject(QObject *parent = nullptr);

signals:

public slots:
};

#endif // QAUTOMATIONPROJECT_H