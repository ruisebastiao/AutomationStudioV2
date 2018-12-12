#ifndef MODULEMODULEPROXYNODESMANAGER_H
#define MODULEPROXYNODESMANAGER_H

#include <qabstractitemmodel.h>

#include <nodes/moduleproxyinputnode.h>



class ProxyNodesManager : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ProxyNodesManagerRoles {
        NodeRole= Qt::UserRole + 1

    };
    Q_ENUMS(ProxyNodesManagerRoles)

    explicit ProxyNodesManager(QObject *parent = nullptr);

signals:

public slots:

private:
    QList<ModuleProxyInputNode*> m_moduleproxynodes;

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

};



#endif // MODULEPROXYNODESMANAGER_H
