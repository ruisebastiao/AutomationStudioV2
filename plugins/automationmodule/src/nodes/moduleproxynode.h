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

    int m_selectedBindedModuleID=1;

    // ProxyNode interface
public:
    virtual void setBindedFlowNode(FlowNode *node) override;
};

#endif // MODULEPROXYNODE_H
