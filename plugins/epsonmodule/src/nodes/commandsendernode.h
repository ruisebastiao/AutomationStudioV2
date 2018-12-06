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
    Q_PROPERTY(QVariant commandInput READ commandInput WRITE setCommandInput NOTIFY commandInputChanged REVISION 30)

    Q_PROPERTY(QVariant epsonNode READ epsonNode WRITE setEpsonNode NOTIFY epsonNodeChanged REVISION 30)
    Q_PROPERTY(QVariant send READ send WRITE setSend NOTIFY sendChanged REVISION 30)



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
                QString command_frominput = m_commandInput.value<QString>();
                QString finalcommand=commandToSend()+command_frominput;
                node->sendCommand(finalcommand);
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
        emit commandInputChanged(m_commandInput);
    }

signals:
    void commandsAvailableChanged(QStringList commandsAvailable);

    void commandToSendChanged(QString commandToSend);



    void epsonNodeChanged(QVariant epsonNode);



    void sendChanged(QVariant send);

    void appendFromInputChanged(bool appendFromInput);

    void commandInputChanged(QVariant commandInput);

private:
    QStringList m_commandsAvailable;
    QString m_commandToSend="";

    QVariant m_epsonNode=QVariant::fromValue(nullptr);


    QVariant m_send=QVariant::fromValue(false);
    bool m_appendFromInput=false;
    QVariant m_commandInput=QVariant::fromValue(QString(""));

};

#endif // COMMANDSENDER_H
