#ifndef PROXYNODE_H
#define PROXYNODE_H

#include "flownode.h"
#include "qautomationmodule.h"


class ProxyNode : public FlowNode
{
    Q_OBJECT

    Q_PROPERTY(QVariant input READ input WRITE setInput NOTIFY inputChanged REVISION 30)
    Q_PROPERTY(QVariant output READ output WRITE setOutput NOTIFY outputChanged REVISION 31)

    Q_PROPERTY(QString proxyType READ proxyType WRITE setProxyType NOTIFY proxyTypeChanged USER("serialize"))

    Q_PROPERTY(int selectedBindedNodeID READ selectedBindedNodeID WRITE setSelectedBindedNodeID NOTIFY selectedBindedNodeIDChanged USER("serialize"))


    Q_PROPERTY(FlowNodeManager* flowNodes READ flowNodes WRITE setFlowNodes NOTIFY flowNodesChanged)



public:
    ProxyNode();
    static  QQmlComponent*      delegate(QQmlEngine& engine);

    Q_INVOKABLE virtual void setBindedFlowNode(FlowNode* node);



    FlowNodeManager* flowNodes() const
    {
        return m_flowNodes;
    }

    QString proxyType() const
    {
        return m_proxyType;
    }

//    FlowNode* selectedBindedNode() const
//    {
//        return m_selectedBindedNode;
//    }

    QVariant input() const
    {
        return m_input;
    }

    QVariant output() const
    {
        return m_output;
    }

public slots:



    void updateProxyType();

    void initProxyNode();

    void setFlowNodes(FlowNodeManager* flowNodes)
    {
        if (m_flowNodes == flowNodes)
            return;

        m_flowNodes = flowNodes;



        emit flowNodesChanged(m_flowNodes);
    }

    void setProxyType(QString proxyType)
    {
        if (m_proxyType == proxyType)
            return;


        m_proxyType = proxyType;
        emit proxyTypeChanged(m_proxyType);

        updateProxyType();

    }

    void setInput(QVariant input)
    {

        if(input.isValid()==false){
            return;
        }


        m_input = input;
        emit inputChanged(m_input);
        setOutput(input);
    }

    void setOutput(QVariant output)
    {


        m_output = output;
        emit outputChanged(m_output);
    }

    void setSelectedBindedNodeID(int selectedBindedNodeID)
    {
        if (m_selectedBindedNodeID == selectedBindedNodeID)
            return;

        m_selectedBindedNodeID = selectedBindedNodeID;
        emit selectedBindedNodeIDChanged(m_selectedBindedNodeID);
    }

signals:




    void flowNodesChanged(FlowNodeManager* flowNodes);

    void proxyTypeChanged(QString proxyType);


    void inputChanged(QVariant input);

    void outputChanged(QVariant output);

    void selectedBindedNodeIDChanged(int selectedBindedNodeID);

private:



    // JsonSerializable interface
    FlowNodeManager* m_flowNodes= nullptr;

    QString m_proxyType="";

    QVariant m_input;

    QVariant m_output;

    int m_selectedBindedNodeID=-1;

protected:
    virtual void DeSerialize(QJsonObject &json) override;



    // FlowNode interface
public:
void initializeNode(int id) override;
int selectedBindedNodeID() const
{
    return m_selectedBindedNodeID;
}
};

#endif // PROXYNODE_H
