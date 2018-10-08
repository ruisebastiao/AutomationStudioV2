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

    Q_PROPERTY(QVariant input READ input WRITE setInput NOTIFY inputChanged)
    Q_PROPERTY(QVariant output READ output WRITE setOutput NOTIFY outputChanged)

    Q_PROPERTY(QString proxyType READ proxyType WRITE setProxyType NOTIFY proxyTypeChanged USER("serialize"))

    Q_PROPERTY(FlowNodePort* inputPort READ inputPort WRITE setInputPort NOTIFY inputPortChanged USER("serialize"))
    Q_PROPERTY(FlowNodePort* outputPort READ outputPort WRITE setOutputPort NOTIFY outputPortChanged USER("serialize"))

    Q_PROPERTY(FlowNode* selectedBindedNode READ selectedBindedNode WRITE setSelectedBindedNode NOTIFY selectedBindedNodeChanged)


    Q_PROPERTY(ProxyInputNodeListModel* proxyNodes READ proxyNodes WRITE setProxyNodes NOTIFY proxyNodesChanged)


public:
    ProxyInputNode();
    static  QQmlComponent*      delegate(QQmlEngine& engine);



    FlowNodePort* inputPort() const
    {
        return m_inputPort;
    }

    FlowNodePort* outputPort() const
    {
        return m_outputPort;
    }

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




    void setInputPort(FlowNodePort* inputPort)
    {
        if (m_inputPort == inputPort)
            return;

        m_inputPort = inputPort;
        emit inputPortChanged(m_inputPort);
    }

    void setOutputPort(FlowNodePort* outputPort)
    {
        if (m_outputPort == outputPort)
            return;

        m_outputPort = outputPort;
        emit outputPortChanged(m_outputPort);
    }

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

        if(!m_inputPort){
            return;
        }

        SceneGraph* graph=qobject_cast<SceneGraph*>(this->getGraph());

        if(m_proxyType=="Output"){
            m_outputPort->setHidden(false);

            m_inputPort->setHidden(true);

        }
        else{
            m_outputPort->setHidden(true);

            m_inputPort->setHidden(false);

        }

        if(m_inputPort->getPortItem()->getInEdgeItems().size()>0){
            graph->deleteEdge(m_inputPort->getPortItem()->getInEdgeItems().at(0)->getEdge());
        }
        if(m_outputPort->getPortItem()->getOutEdgeItems().size()>0){
            graph->deleteEdge(m_outputPort->getPortItem()->getOutEdgeItems().at(0)->getEdge());
        }

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

        if(inputPort()->getPortItem()->getInEdgeItems().size()>0){

            qan::EdgeItem* edgeitem=inputPort()->getPortItem()->getInEdgeItems().at(0);
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
                qan::Edge* newedge=graph->insertNewEdge(false,m_selectedBindedNode,this);
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


    void inputPortChanged(FlowNodePort* inputPort);

    void outputPortChanged(FlowNodePort* outputPort);

    void proxyNodesChanged(ProxyInputNodeListModel* proxyNodes);

    void proxyTypeChanged(QString proxyType);

    void selectedBindedNodeChanged(FlowNode* selectedBindedNode);

    void inputChanged(QVariant input);

    void outputChanged(QVariant output);

private:


    FlowNodePort* m_inputPort=nullptr;
    FlowNodePort* m_outputPort=nullptr;


    // JsonSerializable interface
    ProxyInputNodeListModel* m_proxyNodes= nullptr;

    QString m_proxyType="";



    FlowNode* m_selectedBindedNode=nullptr;

    QVariant m_input;

    QVariant m_output;

protected:
    virtual void DeSerialize(QJsonObject &json) override;
};

#endif // PROXYINPUTNODE_H
