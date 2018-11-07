#ifndef PROJECTSLISTMODEL_H
#define PROJECTSLISTMODEL_H



#include <QAbstractListModel>
#include <QObject>
#include "automationstudiocoreglobal.h"
#include <project.h>

namespace as {



class AUTOMATIONSTUDIO_CORE_EXPORT ProjectsListModel : public QAbstractListModel
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
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    void AddProject(Project *module);
    void clear();
    QHash<int, QByteArray> roleNames() const;
public slots:
    Project *getItemAt(int index);
    int count();

private:

    QList<Project*> m_projects;



};

}
#endif // PROJECTSLISTMODEL_
