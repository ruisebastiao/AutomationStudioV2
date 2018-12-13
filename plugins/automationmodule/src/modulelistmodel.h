#ifndef MODULELISTMODEL_H
#define MODULELISTMODEL_H

#include "automationmoduleglobal.h"
#include "qautomationmodule.h"
#include <QObject>
#include "serializedlistmodel.h"

class AUTOMATIONMODULE_EXPORT ModuleListModel : public SerializedListModel<QAutomationModule>
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

    ~ModuleListModel();

    // QAbstractItemModel interface
public:

    QVariant data(const QModelIndex &index, int role) const;


    QHash<int, QByteArray> roleNames() const;
public slots:


private:





    // JsonSerializable interface
public:
    virtual void Serialize(QJsonObject &json) override;
    virtual void DeSerialize(QJsonObject &json) override;
};
#endif // MODULELISTMODEL_H
