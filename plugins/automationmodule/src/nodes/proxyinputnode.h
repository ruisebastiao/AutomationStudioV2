#ifndef PROXYINPUTNODE_H
#define PROXYINPUTNODE_H

#include "flownode.h"
#include "flownodemanager.h"
#include "qautomationmodule.h"


class ProxyInputNodeListModel: public FlowNodeManager
{
    Q_OBJECT

public:

    ProxyInputNodeListModel(){

        setFilterType(FlowNode::Type::ProxyInputNode);

        QObject::connect(QAutomationModule::flownodemanager,SIGNAL(onFlowNodeLoaded(FlowNode*)),this,SLOT(onNodeAdded(FlowNode*)));

    }




    // FlowNodeManager interface
public slots:
    void onNodeAdded(FlowNode *nodeloaded) override;
};




class ProxyInputNode : public FlowNode
{
    Q_OBJECT

    Q_PROPERTY(QVariant input READ input WRITE setInput NOTIFY inputChanged REVISION 30)
    Q_PROPERTY(QVariant output READ output WRITE setOutput NOTIFY outputChanged REVISION 31)

    Q_PROPERTY(QString proxyType READ proxyType WRITE setProxyType NOTIFY proxyTypeChanged USER("serialize"))

    Q_PROPERTY(FlowNode* selectedBindedNode READ selectedBindedNode WRITE setSelectedBindedNode NOTIFY selectedBindedNodeChanged)


    Q_PROPERTY(ProxyInputNodeListModel* proxyNodes READ proxyNodes WRITE setProxyNodes NOTIFY proxyNodesChanged)


public:
    ProxyInputNode();
    static  QQmlComponent*      delegate(QQmlEngine& engine);




    ProxyInputNodeListModel* proxyNodes() const
    {
        return m_proxyNodes;
    }

    QString proxyType() const
    {
        return m_proxyType;
    }

    FlowNode* selectedBindedNode() const
    {
        return m_selectedBindedNode;
    }

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

    void setProxyNodes(ProxyInputNodeListModel* proxyNodes)
    {
        if (m_proxyNodes == proxyNodes)
            return;

        m_proxyNodes = proxyNodes;
        emit proxyNodesChanged(m_proxyNodes);
    }

    void setProxyType(QString proxyType)
    {
        if (m_proxyType == proxyType)
            return;


        m_proxyType = proxyType;
        emit proxyTypeChanged(m_proxyType);

        updateProxyType();

    }

//    void updateSelectedBindedNode(FlowNode* selectedBindedNode){
//        if (m_selectedBindedNode == selectedBindedNode)
//            return;




//        m_selectedBindedNode = selectedBindedNode;
//        emit selectedBindedNodeChanged(m_selectedBindedNode);

//    }
    void setSelectedBindedNode(FlowNode* selectedBindedNode)
    {

        if (m_selectedBindedNode == selectedBindedNode)
            return;




        m_selectedBindedNode = selectedBindedNode;


        if(configsLoaded()==false){
            return;
        }
        SceneGraph* graph=qobject_cast<SceneGraph*>(this->getGraph());

        if(m_inputPort->getPortItem()->getInEdgeItems().size()>0){

            qan::EdgeItem* edgeitem=m_inputPort->getPortItem()->getInEdgeItems().at(0);
            graph->deleteEdge(edgeitem->getEdge());

            QObject::connect(edgeitem, &qan::EdgeItem::destroyed, this, [this,graph](QObject* edgeObject){
                if(m_selectedBindedNode){
                    qan::Edge* newedge=graph->insertNewEdge(true,m_selectedBindedNode,this);
                    FlowNodePort* outPort=m_selectedBindedNode->getPortByID("output");

                    if(outPort){
                        graph->bindEdge(newedge,outPort->getPortItem(),m_inputPort->getPortItem());
                    }
                }
            });
        }
        else{
            if(m_selectedBindedNode){
                qan::Edge* newedge=graph->insertNewEdge(true,m_selectedBindedNode,this);
                FlowNodePort* outPort=m_selectedBindedNode->getPortByID("output");

                if(outPort){
                    graph->bindEdge(newedge,outPort->getPortItem(),m_inputPort->getPortItem());
                }
            }
        }





        emit selectedBindedNodeChanged(m_selectedBindedNode);
    }

    void setInput(QVariant input)
    {



        m_input = input;
        emit inputChanged(m_input);
        setOutput(input);
    }

    void setOutput(QVariant output)
    {


        m_output = output;
        emit outputChanged(m_output);
    }

signals:




    void proxyNodesChanged(ProxyInputNodeListModel* proxyNodes);

    void proxyTypeChanged(QString proxyType);

    void selectedBindedNodeChanged(FlowNode* selectedBindedNode);

    void inputChanged(QVariant input);

    void outputChanged(QVariant output);

private:



    // JsonSerializable interface
    ProxyInputNodeListModel* m_proxyNodes= nullptr;

    QString m_proxyType="";

    FlowNodePort* m_outputPort=nullptr;
    FlowNodePort* m_inputPort=nullptr;





    FlowNode* m_selectedBindedNode=nullptr;

    QVariant m_input;

    QVariant m_output;

protected:
    virtual void DeSerialize(QJsonObject &json) override;

    // FlowNode interface
public:
    

    // FlowNode interface
public:
    virtual void initializePorts(QJsonObject &json) override;
};

#endif // PROXYINPUTNODE_H
