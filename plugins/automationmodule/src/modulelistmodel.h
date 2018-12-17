#ifndef MODULELISTMODEL_H
#define MODULELISTMODEL_H

#include "automationmoduleglobal.h"
#include "qautomationmodule.h"
#include <QObject>
#include "serializedlistmodel.h"

class AUTOMATIONMODULE_EXPORT ModuleListModel : public TypedListModel<QAutomationModule>
{
    Q_OBJECT
    Q_ENUMS(ListRoles)

public:
    enum ListRoles {
        TypeRole = Qt::UserRole + 1,
        ModuleInstanceRole,
        ModuleSettingsRole,
        ModuleRole,
        ModuleIDRole
    };

    ModuleListModel();
    ModuleListModel(const ModuleListModel& other){ }

    ~ModuleListModel();

    // QAbstractItemModel interface
public:

    QVariant data(const QModelIndex &index, int role) const override;


    QHash<int, QByteArray> roleNames() const override;

public slots:


private:



    // TypedListModel interface
public:
    Q_INVOKABLE virtual void removeItem(QAutomationModule *item) override;
};
Q_DECLARE_METATYPE(ModuleListModel)
#endif // MODULELISTMODEL_H
