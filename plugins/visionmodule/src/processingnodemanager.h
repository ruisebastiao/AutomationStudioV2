#ifndef PROCESSINGNODEMANAGER_H
#define PROCESSINGNODEMANAGER_H

#include <flownodemanager.h>



class ProcessingNodeManager : public FlowNodeManager
{
    Q_OBJECT
    Q_ENUMS(ProcessingNodeManagerRoles)
    Q_INTERFACES(JsonSerializable)


public:

    enum ProcessingNodeManagerRoles {
        ProcessingTypeRole = FlowNodeManager::NodeTypeRole+ 1,
    };

    ProcessingNodeManager(QObject* parent=nullptr);

    // QAbstractItemModel interface
public:
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;
};

#endif // PROCESSINGNODEMANAGER_H
