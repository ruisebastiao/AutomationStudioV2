#ifndef COMMANDPARSERNODE_H
#define COMMANDPARSERNODE_H

#include "ionode.h"

#include <flownode.h>
#include <flownodemanager.h>



class CommandParserNode : public FlowNode
{
    Q_OBJECT


    Q_PROPERTY(QString commandToParse READ commandToParse WRITE setCommandToParse NOTIFY commandToParseChanged USER("serialized"))

    Q_PROPERTY(QVariant dataReceived READ dataReceived WRITE setDataReceived NOTIFY dataReceivedChanged)

    Q_PROPERTY(QVariant commandReceived READ commandReceived WRITE setCommandReceived NOTIFY commandReceivedChanged REVISION 31)

    Q_PROPERTY(FlowNodeManager* flowNodes READ flowNodes WRITE setFlowNodes NOTIFY flowNodesChanged)

    Q_PROPERTY(int selectedBindedNodeID READ selectedBindedNodeID WRITE setSelectedBindedNodeID NOTIFY selectedBindedNodeIDChanged USER("serialize"))


public:
    CommandParserNode();


    Q_INVOKABLE virtual void setBindedIONode(IONode* node);

    static QQmlComponent *delegate(QQmlEngine &engine) noexcept;

    QVariant dataReceived() const
    {
        return m_dataReceived;
    }

    QVariant commandReceived() const
    {
        return m_commandReceived;
    }

    QString commandToParse() const
    {
        return m_commandToParse;
    }

    FlowNodeManager* flowNodes() const
    {
        return m_flowNodes;
    }

    int selectedBindedNodeID() const
    {
        return m_selectedBindedNodeID;
    }

public slots:
    void setDataReceived(QVariant dataReceived)
    {

        m_dataReceived = dataReceived;

        QString datareceived=m_dataReceived.value<QString>();
        datareceived=datareceived.replace("\n","");
        datareceived=datareceived.replace("\r","");
        m_dataReceived=QVariant::fromValue(datareceived);
        if(datareceived==commandToParse()){
            setCommandReceived(true);
        }
        else{
            setCommandReceived(false);
        }
        emit dataReceivedChanged(m_dataReceived);
    }

    void setCommandReceived(QVariant commandReceived)
    {


        m_commandReceived = commandReceived;
        emit commandReceivedChanged(m_commandReceived);
    }

    void setCommandToParse(QString commandToParse)
    {
        if (m_commandToParse == commandToParse)
            return;

        m_commandToParse = commandToParse;
        emit commandToParseChanged(m_commandToParse);
    }

    void setFlowNodes(FlowNodeManager* flowNodes)
    {
        if (m_flowNodes == flowNodes)
            return;

        m_flowNodes = flowNodes;
        if(m_flowNodes){
            IONode* ionode=dynamic_cast<IONode*>(m_flowNodes->getByID(m_selectedBindedNodeID));
            setBindedIONode(ionode);
        }
        emit flowNodesChanged(m_flowNodes);
    }

    void setSelectedBindedNodeID(int selectedBindedNodeID)
    {
        if (m_selectedBindedNodeID == selectedBindedNodeID)
            return;

        m_selectedBindedNodeID = selectedBindedNodeID;



        emit selectedBindedNodeIDChanged(m_selectedBindedNodeID);
    }

signals:
    void dataReceivedChanged(QVariant dataReceived);

    void commandReceivedChanged(QVariant commandReceived);

    void commandToParseChanged(QString commandToParse);

    void flowNodesChanged(FlowNodeManager* flowNodes);

    void selectedBindedNodeIDChanged(int selectedBindedNodeID);

private:

    QVariant m_dataReceived=QVariant::fromValue(nullptr);
    QVariant m_commandReceived=QVariant::fromValue(false);
    QString m_commandToParse="";
    FlowNodeManager* m_flowNodes=nullptr;
    IONode* m_bindedIONode=nullptr;
    int m_selectedBindedNodeID=-1;

    // JsonSerializable interface
public:
    void DeSerialize(QJsonObject &json) override;
};

#endif // COMMANDPARSERNODE_H
