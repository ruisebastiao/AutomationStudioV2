#ifndef MODULELISTMODEL_H
#define MODULELISTMODEL_H

#include "automationstudiocoreglobal.h"
#include "module.h"

#include <QAbstractListModel>
#include <QObject>

class AUTOMATIONSTUDIO_CORE_EXPORT ModuleListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(ListRoles)

public:
    enum ListRoles {
        TypeRole = Qt::UserRole + 1,
        ModuleInstanceRole = Qt::UserRole + 2,
        ModuleSettingsRole = Qt::UserRole + 3,
        ModuleRole = Qt::UserRole + 4
    };

    ModuleListModel();

    ~ModuleListModel();

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    void AddModule(Module *module);
    void clear();
    QHash<int, QByteArray> roleNames() const;
public slots:
    Module *getItemAt(int index);
    Q_INVOKABLE int count();

private:

    QList<Module*> m_modules;



};
#endif // MODULELISTMODEL_H
