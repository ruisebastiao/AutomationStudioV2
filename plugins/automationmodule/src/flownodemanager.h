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

    Q_INVOKABLE int indexOfID(int nodeID);
signals:

    void lengthChanged(int length);

private:

    QMap<int,FlowNode*> m_flownodesTable;


    QList<FlowNode*> m_proxynodes;

    SceneGraph* m_scenegraph=nullptr;


    FlowNode *readNode(QJsonObject nodeobject);
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
    virtual void addItem(FlowNode *item) override;


public:
    virtual void removeItem(FlowNode *item) override;

    // JsonSerializable interface
public:
//    virtual void Serialize(QJsonArray &jsonarray) override;
    virtual void DeSerialize(QJsonArray &jsonarray) override;
    SceneGraph *getScenegraph() const;
    void setScenegraph(SceneGraph *scenegraph);
};


#endif // FLOWNODEMANAGER_H
