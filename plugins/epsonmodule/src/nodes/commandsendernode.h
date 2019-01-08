#ifndef COMMANDSENDERNODE_H
#define COMMANDSENDER_H

#include "epsonnode.h"

#include <flownode.h>



class CommandSenderNode : public FlowNode
{
    Q_OBJECT

    Q_PROPERTY(QStringList commandsAvailable READ commandsAvailable WRITE setCommandsAvailable NOTIFY commandsAvailableChanged)

    Q_PROPERTY(QString commandToSend READ commandToSend WRITE setCommandToSend NOTIFY commandToSendChanged USER("serialized"))

    Q_PROPERTY(bool appendFromInput READ appendFromInput WRITE setAppendFromInput NOTIFY appendFromInputChanged USER("serialized"))
    Q_PROPERTY(bool sendOnData READ sendOnData WRITE setSendOnData NOTIFY sendOnDataChanged USER("serialized"))

    Q_PROPERTY(QVariant commandInput READ commandInput WRITE setCommandInput NOTIFY commandInputChanged REVISION 30)

    Q_PROPERTY(QVariant epsonNode READ epsonNode WRITE setEpsonNode NOTIFY epsonNodeChanged REVISION 30)
    Q_PROPERTY(QVariant send READ send WRITE setSend NOTIFY sendChanged REVISION 30)

    Q_PROPERTY(QString finalCommand READ finalCommand WRITE setFinalCommand NOTIFY finalCommandChanged)


public:
    CommandSenderNode();
    static QQmlComponent *delegate(QQmlEngine &engine) noexcept;

    Q_INVOKABLE void doSendCommand();

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



    void setEpsonNode(QVariant epsonNode)
    {

        m_epsonNode = epsonNode;
        emit epsonNodeChanged(m_epsonNode);
    }



    void setSend(QVariant send)
    {


        m_send = send;
        if(m_send.value<bool>()){
            EpsonNode* node=m_epsonNode.value<EpsonNode*>();
            if(node){
                if(appendFromInput()){
                    node->sendCommand(finalCommand());
                }
                else {
                    node->sendCommand(commandToSend());
                }
            }
        }
        emit sendChanged(m_send);
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

signals:
    void commandsAvailableChanged(QStringList commandsAvailable);

    void commandToSendChanged(QString commandToSend);



    void epsonNodeChanged(QVariant epsonNode);



    void sendChanged(QVariant send);

    void appendFromInputChanged(bool appendFromInput);

    void commandInputChanged(QVariant commandInput);

    void finalCommandChanged(QString finalCommand);

    void sendOnDataChanged(bool sendOnData);

private:

    void setFinalCommand(QString finalCommand)
    {

        m_finalCommand = finalCommand;
        emit finalCommandChanged(m_finalCommand);
        if(sendOnData()){
            setSend(true);
        }
    }

    QStringList m_commandsAvailable;
    QString m_commandToSend="";

    QVariant m_epsonNode=QVariant::fromValue(nullptr);


    QVariant m_send=QVariant::fromValue(false);
    bool m_appendFromInput=false;
    QVariant m_commandInput=QVariant::fromValue(QString(""));

    QString m_finalCommand;
    bool m_sendOnData=false;
};

#endif // COMMANDSENDER_H
