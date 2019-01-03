#ifndef MODULEPROXYNODE_H
#define MODULEPROXYNODE_H

#include "proxynode.h"



class ModuleProxyNode : public ProxyNode
{
    Q_OBJECT

    Q_PROPERTY(int selectedBindedModuleID READ selectedBindedModuleID WRITE setSelectedBindedModuleID NOTIFY selectedBindedModuleIDChanged USER("serialize"))

public:
    ModuleProxyNode();

    int selectedBindedModuleID() const
    {
        return m_selectedBindedModuleID;
    }

public slots:
    void setSelectedBindedModuleID(int selectedBindedModuleID);


signals:
    void selectedBindedModuleIDChanged(int selectedBindedModuleID);

private:
    void setNodesFromModule(FlowNodeManager* modulenodes);
    int m_selectedBindedModuleID=-1;

    // ProxyNode interface
public:
    virtual void setBindedFlowNode(FlowNode *node) override;

    // ProxyNode interface
public slots:
    virtual void initProxyNode() override;

    // ProxyNode interface
public slots:
    virtual void setFlowNodes(FlowNodeManager *flowNodes) override;

    // JsonSerializable interface
public:
    virtual void DeSerialize(QJsonObject &json) override;
};

#endif // MODULEPROXYNODE_H
