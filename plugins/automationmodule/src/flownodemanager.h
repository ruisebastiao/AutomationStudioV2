#ifndef FLOWNODEMANAGER_H
#define FLOWNODEMANAGER_H

#include "flownode.h"

#include <QAbstractListModel>
#include <serializedlistmodel.h>

#include "automationmoduleglobal.h"



class AUTOMATIONMODULE_EXPORT FlowNodeManager : public SerializedListModel<FlowNode>
{
    Q_OBJECT
    Q_ENUMS(FlowNodeManagerRoles)
    Q_INTERFACES(JsonSerializable)

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

    QMap<int,FlowNode*> m_flownodesTable;


    QList<FlowNode*> m_proxynodes;



public slots:
    FlowNode* getByID(int id);

    QList<FlowNode *> flownodes();

    int indexOf(FlowNode* node){
        int idx=this->m_internalList.indexOf(node);
        return  idx;
    }



public:



    virtual QVariant data(const QModelIndex &index, int role) const override;



    // QAbstractItemModel interface
public:
    virtual QHash<int, QByteArray> roleNames() const override;

    int getAvailableID();

    FlowNode::Type getFilterType() const;
    void setFilterType(const FlowNode::Type &filterType);
    QMap<int, FlowNode *> getFlownodesTable() const;
    //void removeNode(FlowNode *node);


    // JsonSerializable interface
//public:
//    virtual void Serialize(QJsonObject &json) override;
//    virtual void DeSerialize(QJsonObject &json) override;



    // SerializedListModel interface
public:
    virtual void AddItem(FlowNode *item) override;


public:
    virtual void RemoveItem(FlowNode *item) override;

    // JsonSerializable interface
public:
//    virtual void Serialize(QJsonArray &jsonarray) override;
    virtual void DeSerialize(QJsonArray &jsonarray) override;
};


#endif // FLOWNODEMANAGER_H
