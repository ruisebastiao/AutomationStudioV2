#ifndef COMMANDPARSERNODE_H
#define COMMANDPARSERNODE_H

#include <flownode.h>



class CommandParserNode : public FlowNode
{
    Q_OBJECT


    Q_PROPERTY(QString commandToParse READ commandToParse WRITE setCommandToParse NOTIFY commandToParseChanged USER("serialized"))

    Q_PROPERTY(QVariant dataReceived READ dataReceived WRITE setDataReceived NOTIFY dataReceivedChanged REVISION 30)
    Q_PROPERTY(QVariant commandReceived READ commandReceived WRITE setCommandReceived NOTIFY commandReceivedChanged REVISION 31)

public:
    CommandParserNode();
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

public slots:
    void setDataReceived(QVariant dataReceived)
    {

        m_dataReceived = dataReceived;

        QString datareceived=m_dataReceived.value<QString>();
        datareceived=datareceived.replace("\n","");
        datareceived=datareceived.replace("\r","");
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

signals:
    void dataReceivedChanged(QVariant dataReceived);

    void commandReceivedChanged(QVariant commandReceived);

    void commandToParseChanged(QString commandToParse);

private:

    QVariant m_dataReceived=QVariant::fromValue(nullptr);
    QVariant m_commandReceived=QVariant::fromValue(false);
    QString m_commandToParse="";
};

#endif // COMMANDPARSERNODE_H
