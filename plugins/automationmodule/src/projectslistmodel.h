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

public:
    enum MyRoles {
        NameRole = Qt::UserRole + 1,
        ProjectRole = Qt::UserRole + 2
    };

    ProjectsListModel(QObject *parent = nullptr);
    ~ProjectsListModel();

    // QAbstractItemModel interface
public:

    QVariant data(const QModelIndex &index, int role) const;


    QHash<int, QByteArray> roleNames() const;
public slots:



};


#endif // PROJECTSLISTMODEL_
