#ifndef AUTOMATIONPROJECTS_H
#define AUTOMATIONPROJECTS_H

#include "qautomationmodule.h"

#include <QAbstractListModel>
#include <QObject>

class AutomationProjects : public QAbstractListModel
{  Q_OBJECT
    Q_ENUMS(MyRoles)

public:
    enum MyRoles {
        NameRole = Qt::UserRole + 1,
        TypeRole = Qt::UserRole + 2,
        ModuleRole = Qt::UserRole + 3
    };

    AutomationProjects(QObject *parent = nullptr);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;


    void AddModule(QAutomationModule *module);
    void clear();
private:

    QList<QAutomationModule*> m_modules;


    // QAbstractItemModel interface
public:
    QHash<int, QByteArray> roleNames() const;

};

#endif // AUTOMATIONPROJECTS_H
