#ifndef PROXYINPUTNODE_H
#define PROXYINPUTNODE_H

#include "flownode.h"
#include "qautomationmodule.h"


class ProxyInputNode : public FlowNode
{
    Q_OBJECT

    Q_PROPERTY(QVariant input READ input WRITE setInput NOTIFY inputChanged REVISION 30)
    Q_PROPERTY(QVariant output READ output WRITE setOutput NOTIFY outputChanged REVISION 31)

    Q_PROPERTY(QString proxyType READ proxyType WRITE setProxyType NOTIFY proxyTypeChanged USER("serialize"))

//    Q_PROPERTY(FlowNode* selectedBindedNode READ selectedBindedNode WRITE setSelectedBindedNode NOTIFY selectedBindedNodeChanged)


//   Q_PROPERTY(FlowNodeManager* proxyNodes READ proxyNodes WRITE setProxyNodes NOTIFY proxyNodesChanged)

    Q_PROPERTY(FlowNodeManager* flowNodes READ flowNodes WRITE setFlowNodes NOTIFY flowNodesChanged)


public:
    ProxyInputNode();
    static  QQmlComponent*      delegate(QQmlEngine& engine);




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

//    void setSelectedBindedNode(FlowNode* selectedBindedNode)
//    {

//        if (m_selectedBindedNode == selectedBindedNode)
//            return;




//        m_selectedBindedNode = selectedBindedNode;


//        if(configsLoaded()==false){
//            return;
//        }

//        FlowNodePort* outputport=getPortFromKey("output");
//        FlowNodePort* inputport=getPortFromKey("input");

//        if(!outputport || !inputport){
//            return;
//        }

//        SceneGraph* graph=qobject_cast<SceneGraph*>(this->getGraph());

//        if(inputport->getPortItem()->getInEdgeItems().size()>0){

//            qan::EdgeItem* edgeitem=inputport->getPortItem()->getInEdgeItems().at(0);
//            graph->deleteEdge(edgeitem->getEdge());

//            QObject::connect(edgeitem, &qan::EdgeItem::destroyed,[this,graph,inputport](QObject* edgeObject){
//                if(m_selectedBindedNode){
//                    qan::Edge* newedge=graph->insertNewEdge(true,m_selectedBindedNode,this);
//                    FlowNodePort* outPort=m_selectedBindedNode->getPortByID("output");

//                    if(outPort){
//                        graph->bindEdge(newedge,outPort->getPortItem(),inputport->getPortItem());
//                    }
//                }
//            });
//        }
//        else{
//            if(m_selectedBindedNode){
//                qan::Edge* newedge=graph->insertNewEdge(true,m_selectedBindedNode,this);
//                FlowNodePort* outPort=m_selectedBindedNode->getPortByID("output");

//                if(outPort){
//                    graph->bindEdge(newedge,outPort->getPortItem(),inputport->getPortItem());
//                }
//            }
//        }





//        emit selectedBindedNodeChanged(m_selectedBindedNode);
//    }

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




    void flowNodesChanged(FlowNodeManager* flowNodes);

    void proxyTypeChanged(QString proxyType);

//    void selectedBindedNodeChanged(FlowNode* selectedBindedNode);

    void inputChanged(QVariant input);

    void outputChanged(QVariant output);

private:



    // JsonSerializable interface
    FlowNodeManager* m_flowNodes= nullptr;

    QString m_proxyType="";

//    FlowNode* m_selectedBindedNode=nullptr;

    QVariant m_input;

    QVariant m_output;

protected:
    virtual void DeSerialize(QJsonObject &json) override;

    // FlowNode interface
public:
    

    // FlowNode interface
public:


    // FlowNode interface
public:
    void initializeNode(int id) override;
};

#endif // PROXYINPUTNODE_H
