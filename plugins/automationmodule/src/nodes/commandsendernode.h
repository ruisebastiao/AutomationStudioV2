#ifndef COMMANDSENDERNODE_H
#define COMMANDSENDER_H


#include "ionode.h"

#include <flownode.h>
#include <flownodemanager.h>



class CommandSenderNode : public FlowNode
{
    Q_OBJECT

    Q_PROPERTY(QStringList commandsAvailable READ commandsAvailable WRITE setCommandsAvailable NOTIFY commandsAvailableChanged)

    Q_PROPERTY(QString commandToSend READ commandToSend WRITE setCommandToSend NOTIFY commandToSendChanged USER("serialized"))

    Q_PROPERTY(bool appendFromInput READ appendFromInput WRITE setAppendFromInput NOTIFY appendFromInputChanged USER("serialized"))
    Q_PROPERTY(bool sendOnData READ sendOnData WRITE setSendOnData NOTIFY sendOnDataChanged USER("serialized"))

    Q_PROPERTY(bool invertSendInput READ invertSendInput WRITE setInvertSendInput NOTIFY invertSendInputChanged USER("serialized"))

    Q_PROPERTY(QVariant commandInput READ commandInput WRITE setCommandInput NOTIFY commandInputChanged REVISION 30)

    Q_PROPERTY(QVariant send READ send WRITE setSend NOTIFY sendChanged REVISION 30)

    Q_PROPERTY(QString finalCommand READ finalCommand WRITE setFinalCommand NOTIFY finalCommandChanged)

    Q_PROPERTY(FlowNodeManager* flowNodes READ flowNodes WRITE setFlowNodes NOTIFY flowNodesChanged)

    Q_PROPERTY(int selectedBindedNodeID READ selectedBindedNodeID WRITE setSelectedBindedNodeID NOTIFY selectedBindedNodeIDChanged USER("serialize"))

    Q_PROPERTY(int delaySendTime READ delaySendTime WRITE setDelaySendTime NOTIFY delaySendTimeChanged USER("serialize"))


public:
    CommandSenderNode();
    static QQmlComponent *delegate(QQmlEngine &engine) noexcept;

    Q_INVOKABLE void doSendCommand();
    Q_INVOKABLE virtual void setBindedIONode(IONode* node);

    QStringList commandsAvailable() const
    {
        return m_commandsAvailable;
    }
    QString commandToSend() const
    {
        return m_commandToSend;
    }


    QVariant epsonNode() const
    {
        return m_epsonNode;
    }


    QVariant send() const
    {
        return m_send;
    }

    bool appendFromInput() const
    {
        return m_appendFromInput;
    }

    QVariant commandInput() const
    {
        return m_commandInput;
    }

    QString finalCommand() const
    {
        return m_finalCommand;
    }

    bool sendOnData() const
    {
        return m_sendOnData;
    }

    FlowNodeManager* flowNodes() const
    {
        return m_flowNodes;
    }

    int selectedBindedNodeID() const
    {
        return m_selectedBindedNodeID;
    }

    bool invertSendInput() const
    {
        return m_invertSendInput;
    }

    int delaySendTime() const
    {
        return m_delaySendTime;
    }

public slots:
    void setCommandsAvailable(QStringList commandsAvailable)
    {
        if (m_commandsAvailable == commandsAvailable)
            return;

        m_commandsAvailable = commandsAvailable;
        emit commandsAvailableChanged(m_commandsAvailable);
    }
    void setCommandToSend(QString commandToSend)
    {
        if (m_commandToSend == commandToSend)
            return;

        m_commandToSend = commandToSend;

        QString command_frominput = m_commandInput.value<QString>();
        setFinalCommand(commandToSend+command_frominput);


        emit commandToSendChanged(m_commandToSend);
    }





    void setSend(QVariant send)
    {



        m_send = send;
        if(configsLoaded()){
            if(m_send.value<bool>() || (m_send.value<bool>()==false && invertSendInput())) {
                if(m_bindedIONode){
                    if(appendFromInput()){
                        m_bindedIONode->setSendData(finalCommand());
                    }
                    else {
                        m_bindedIONode->setSendData(commandToSend());
                    }
                    if(delaySendTime()>0){
                        Utilities::NonBlockingWait(delaySendTime());
                    }

                    m_bindedIONode->setSend(true);

                }


            }
           emit sendChanged(m_send);
        }

        m_send=false;
    }

    void setAppendFromInput(bool appendFromInput)
    {
        if (m_appendFromInput == appendFromInput)
            return;

        m_appendFromInput = appendFromInput;
        emit appendFromInputChanged(m_appendFromInput);
    }

    void setCommandInput(QVariant commandInput)
    {

        if(connectionsLoaded()==false){
            return;
        }


        m_commandInput = commandInput;
        QString command_frominput = m_commandInput.value<QString>();

        setFinalCommand(commandToSend()+command_frominput);


        emit commandInputChanged(m_commandInput);
    }


    void setSendOnData(bool sendOnData)
    {
        if (m_sendOnData == sendOnData)
            return;

        m_sendOnData = sendOnData;
        emit sendOnDataChanged(m_sendOnData);
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

    void setInvertSendInput(bool invertSendInput)
    {
        if (m_invertSendInput == invertSendInput)
            return;

        m_invertSendInput = invertSendInput;
        emit invertSendInputChanged(m_invertSendInput);
    }

    void setDelaySendTime(int delaySendTime)
    {
        if (m_delaySendTime == delaySendTime)
            return;

        m_delaySendTime = delaySendTime;
        emit delaySendTimeChanged(m_delaySendTime);
    }

signals:
    void commandsAvailableChanged(QStringList commandsAvailable);

    void commandToSendChanged(QString commandToSend);



    void epsonNodeChanged(QVariant epsonNode);



    void sendChanged(QVariant send);

    void appendFromInputChanged(bool appendFromInput);

    void commandInputChanged(QVariant commandInput);

    void finalCommandChanged(QString finalCommand);

    void sendOnDataChanged(bool sendOnData);

    void flowNodesChanged(FlowNodeManager* flowNodes);

    void selectedBindedNodeIDChanged(int selectedBindedNodeID);

    void invertSendInputChanged(bool invertSendInput);

    void delaySendTimeChanged(int delaySendTime);

private:

    void setFinalCommand(QString finalCommand)
    {

        m_finalCommand = finalCommand;
        emit finalCommandChanged(m_finalCommand);
        if(sendOnData()){
            setSend(true);
        }
    }

    IONode* m_bindedIONode=nullptr;

    QStringList m_commandsAvailable;
    QString m_commandToSend="";

    QVariant m_epsonNode=QVariant::fromValue(nullptr);


    QVariant m_send=QVariant::fromValue(false);
    bool m_appendFromInput=false;
    QVariant m_commandInput=QVariant::fromValue(QString(""));

    QString m_finalCommand;
    bool m_sendOnData=false;
    FlowNodeManager* m_flowNodes=nullptr;
    int m_selectedBindedNodeID=-1;
    bool m_invertSendInput=false;
    int m_delaySendTime=0;
};

#endif // COMMANDSENDER_H
