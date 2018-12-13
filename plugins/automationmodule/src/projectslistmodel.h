#ifndef PROJECTSLISTMODEL_H
#define PROJECTSLISTMODEL_H




#include <QObject>
#include "automationmoduleglobal.h"
#include <project.h>
#include "serializedlistmodel.h"


class AUTOMATIONMODULE_EXPORT ProjectsListModel : public SerializedListModel<Project>
{
    Q_OBJECT
    Q_ENUMS(MyRoles)
    Q_INTERFACES(JsonSerializable)

    int getAvailableID();
public:
    enum MyRoles {
        NameRole = Qt::UserRole + 1,
        ProjectRole = Qt::UserRole + 2
    };

    ProjectsListModel(QObject *parent = nullptr);
    ~ProjectsListModel();

    Q_INVOKABLE void createNewProject();
    // QAbstractItemModel interface
public:

    QVariant data(const QModelIndex &index, int role) const override;


    QHash<int, QByteArray> roleNames() const override;
public slots:


};


#endif // PROJECTSLISTMODEL_
