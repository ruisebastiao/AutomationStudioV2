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
    Q_PROPERTY(QString commandToReset READ commandToReset WRITE setCommandToReset NOTIFY commandToResetChanged USER("serialized"))

    Q_PROPERTY(QVariant dataReceived READ dataReceived WRITE setDataReceived NOTIFY dataReceivedChanged)

    Q_PROPERTY(QVariant commandOK READ commandOK WRITE setCommandOK NOTIFY commandOKChanged REVISION 31)

    Q_PROPERTY(QVariant commandValue READ commandValue WRITE setCommandValue NOTIFY commandValueChanged REVISION 31)

    Q_PROPERTY(FlowNodeManager* flowNodes READ flowNodes WRITE setFlowNodes NOTIFY flowNodesChanged)

    Q_PROPERTY(int selectedBindedNodeID READ selectedBindedNodeID WRITE setSelectedBindedNodeID NOTIFY selectedBindedNodeIDChanged USER("serialize"))


public:
    CommandParserNode();


    Q_INVOKABLE virtual void setBindedIONode(IONode* node);

    Q_INVOKABLE void validate(){
        setDataReceived(m_dataReceived);
    }

    static QQmlComponent *delegate(QQmlEngine &engine) noexcept;

    QVariant dataReceived() const
    {
        return m_dataReceived;
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
    void setDataReceived(QVariant dataReceived)
    {

        m_dataReceived = dataReceived;

        QString datareceived=m_dataReceived.value<QString>();

        m_dataReceived=QVariant::fromValue(datareceived);

        QRegularExpression regex_set(m_commandToParse);

        QRegularExpressionMatch setmatch = regex_set.match(datareceived);
        bool hasMatch = setmatch.hasMatch(); // true


        if (hasMatch){
            setCommandValue(m_dataReceived);
            setCommandOK(true);
        }


        QRegularExpression regex_reset(m_commandToReset);

        QRegularExpressionMatch resetmatch = regex_reset.match(datareceived);
        hasMatch = resetmatch.hasMatch(); // true


        if (hasMatch){
            setCommandValue(m_dataReceived);
            setCommandOK(false);
        }

        //            std::cout << "string literal matched\n";

        //        if(datareceived==commandToParse()){
        //            setCommandValue(m_dataReceived);
        //            setCommandOK(true);
        //        }
        //        else{
        //            setCommandOK(false);
        //        }
        emit dataReceivedChanged(m_dataReceived);
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
        if (m_commandValue == commandValue)
            return;

        m_commandValue = commandValue;
        emit commandValueChanged(m_commandValue);
    }

    void setCommandToReset(QString commandToReset)
    {
        if (m_commandToReset == commandToReset)
            return;

        m_commandToReset = commandToReset;
        emit commandToResetChanged(m_commandToReset);
    }

signals:
    void dataReceivedChanged(QVariant dataReceived);

    void commandOKChanged(QVariant commandOK);

    void commandToParseChanged(QString commandToParse);

    void flowNodesChanged(FlowNodeManager* flowNodes);

    void selectedBindedNodeIDChanged(int selectedBindedNodeID);

    void commandValueChanged(QVariant commandValue);

    void commandToResetChanged(QString commandToReset);

private:

    QVariant m_dataReceived=QVariant::fromValue(nullptr);
    QVariant m_commandOK=QVariant::fromValue(false);
    QString m_commandToParse="";
    FlowNodeManager* m_flowNodes=nullptr;
    IONode* m_bindedIONode=nullptr;
    int m_selectedBindedNodeID=-1;

    // JsonSerializable interface
    QVariant m_commandValue=QVariant::fromValue(QString(""));

    QString m_commandToReset="";

public:
    void DeSerialize(QJsonObject &json) override;
    QVariant commandValue() const
    {
        return m_commandValue;
    }
    QString commandToReset() const
    {
        return m_commandToReset;
    }
};

#endif // COMMANDPARSERNODE_H
