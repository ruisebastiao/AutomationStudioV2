#ifndef FLOWNODEMANAGER_H
#define FLOWNODEMANAGER_H

#include "flownode.h"

#include <QAbstractListModel>

#include "automationmoduleglobal.h"



class AUTOMATIONMODULE_EXPORT FlowNodeManager : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(FlowNodeManagerRoles)

    Q_PROPERTY(int length READ length NOTIFY lengthChanged)

public:
    enum FlowNodeManagerRoles {
        NameRole = Qt::UserRole + 1,
        IDRole,
        NodeRole,
        NodeTypeRole
    };

    FlowNodeManager(QObject *parent = nullptr);


signals:

    void lengthChanged(int length);

private:
    QList<FlowNode*> m_flownodes;
    QMap<int,FlowNode*> m_flownodesTable;


    QList<FlowNode*> m_proxynodes;



public slots:
    FlowNode* getByID(int id);

    QList<FlowNode *> flownodes();

    int indexOf(FlowNode* node){
        int idx=this->m_flownodes.indexOf(node);
        return  idx;
    }

    int length() const{
        return  this->m_flownodes.length();
    }


public:

    void addNode(FlowNode* node);

    virtual int rowCount(const QModelIndex &parent) const override;

    virtual QVariant data(const QModelIndex &index, int role) const override;



    // QAbstractItemModel interface
public:
    virtual QHash<int, QByteArray> roleNames() const override;

    int getAvailableID();

    FlowNode::Type getFilterType() const;
    void setFilterType(const FlowNode::Type &filterType);
    QMap<int, FlowNode *> getFlownodesTable() const;
    void removeNode(FlowNode *node);
    FlowNode *at(int index);
};


#endif // FLOWNODEMANAGER_H
