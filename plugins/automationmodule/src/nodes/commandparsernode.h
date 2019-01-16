#ifndef COMMANDPARSERNODE_H
#define COMMANDPARSERNODE_H

#include "ionode.h"

#include <flownode.h>
#include <flownodemanager.h>

#include <string>
#include <regex>

class CommandParserNode : public FlowNode
{
    Q_OBJECT


    Q_PROPERTY(QString commandToParse READ commandToParse WRITE setCommandToParse NOTIFY commandToParseChanged USER("serialized"))

    Q_PROPERTY(QString commandValidator READ commandValidator WRITE setCommandValidator NOTIFY commandValidatorChanged USER("serialized"))

    Q_PROPERTY(QVariant commandReceived READ commandReceived WRITE setCommandReceived NOTIFY commandReceivedChanged)

    Q_PROPERTY(QVariant commandOK READ commandOK WRITE setCommandOK NOTIFY commandOKChanged REVISION 31)

    Q_PROPERTY(QVariant commandValue READ commandValue WRITE setCommandValue NOTIFY commandValueChanged REVISION 31)

    Q_PROPERTY(FlowNodeManager* flowNodes READ flowNodes WRITE setFlowNodes NOTIFY flowNodesChanged)

    Q_PROPERTY(int selectedBindedNodeID READ selectedBindedNodeID WRITE setSelectedBindedNodeID NOTIFY selectedBindedNodeIDChanged USER("serialize"))


public:
    CommandParserNode();


    Q_INVOKABLE virtual void setBindedIONode(IONode* node);

    Q_INVOKABLE void validate(){
        setCommandReceived(m_commandReceived);
    }

    static QQmlComponent *delegate(QQmlEngine &engine) noexcept;

    QVariant commandReceived() const
    {
        return m_commandReceived;
    }

    QVariant commandOK() const
    {
        return m_commandOK;
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
    void setCommandReceived(QVariant commandReceived)
    {



        QString commandreceived=commandReceived.value<QString>();


        QStringList commandsplited=commandreceived.split(m_commandToParse);
        if(commandsplited.length()>1){

            m_commandReceived = commandReceived;
            emit commandReceivedChanged(m_commandReceived);

            setCommandValue(commandsplited[1]);
            bool cmdok=commandsplited[1]==commandValidator();
            setCommandOK(cmdok);

        }


    }

    void setCommandOK(QVariant commandOK)
    {

        m_commandOK = commandOK;
        emit commandOKChanged(m_commandOK);
    }

    void setCommandToParse(QString commandToParse)
    {
        if (m_commandToParse == commandToParse)
            return;

        m_commandToParse = commandToParse;
        setCommandOK(false);
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

    void setCommandValue(QVariant commandValue)
    {

        m_commandValue = commandValue;
        emit commandValueChanged(m_commandValue);
    }



    void setCommandValidator(QString commandValidator)
    {
        if (m_commandValidator == commandValidator)
            return;

        m_commandValidator = commandValidator;
        emit commandValidatorChanged(m_commandValidator);
    }

signals:
    void commandReceivedChanged(QVariant commandReceived);

    void commandOKChanged(QVariant commandOK);

    void commandToParseChanged(QString commandToParse);

    void flowNodesChanged(FlowNodeManager* flowNodes);

    void selectedBindedNodeIDChanged(int selectedBindedNodeID);

    void commandValueChanged(QVariant commandValue);



    void commandValidatorChanged(QString commandValidator);

private:

    QVariant m_commandReceived=QString("");
    QVariant m_commandOK=QVariant::fromValue(false);
    bool m_commandOK_lastvalue=false;
    QString m_commandToParse="";
    FlowNodeManager* m_flowNodes=nullptr;
    IONode* m_bindedIONode=nullptr;
    int m_selectedBindedNodeID=-1;

    // JsonSerializable interface
    QVariant m_commandValue=QString("");



    QString m_commandValidator="";

public:
    void DeSerialize(QJsonObject &json) override;
    QVariant commandValue() const
    {
        return m_commandValue;
    }

    QString commandValidator() const
    {
        return m_commandValidator;
    }
};

#endif // COMMANDPARSERNODE_H
