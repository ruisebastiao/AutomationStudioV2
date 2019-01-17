#ifndef TOOLNODE_H
#define TOOLNODE_H

#include <flownode.h>
#include <serializedlistmodel.h>


class ToolInfo:public QObject, public JsonSerializable
{
    Q_OBJECT
    Q_INTERFACES(JsonSerializable)


    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged USER("serialize"))
    Q_PROPERTY(QString projectName READ projectName WRITE setProjectName NOTIFY projectNameChanged USER("serialize"))

public:
    ToolInfo();
    ToolInfo(QString id,QString projectname);

    QString id() const
    {
        return m_id;
    }

    QString projectName() const
    {
        return m_projectName;
    }

public slots:
    void setId(QString id)
    {
        if (m_id == id)
            return;

        m_id = id;
        emit idChanged(m_id);
    }

    void setProjectName(QString projectName)
    {
        if (m_projectName == projectName)
            return;

        m_projectName = projectName;
        emit projectNameChanged(m_projectName);
    }

signals:
    void idChanged(QString id);

    void projectNameChanged(QString projectName);

private:

    QString m_id="";
    QString m_projectName="";

    // JsonSerializable interface
public:
    void Serialize(QJsonObject &json) override;
    void DeSerialize(QJsonObject &json) override;
};

class ToolInfoList:public SerializedListModel<ToolInfo>
{
    Q_OBJECT
    Q_INTERFACES(JsonSerializable)

public:
    enum ToolRoles {
        ProjectNameRole = Qt::UserRole + 1,
        IDRole,
        ToolRole,
        TextRole
    };
    ToolInfoList();
    ToolInfoList(const ToolInfoList& other){ }



    Q_INVOKABLE ToolInfo* getByToolId(QString toolid){

        for (int var = 0; var < m_internalList.length(); ++var) {
            ToolInfo* toolinfo=m_internalList.at(var);
            if(toolinfo->id()==toolid){
                return toolinfo;
            }
        }

        return nullptr;
    }
    // QAbstractItemModel interface
public:
    QHash<int, QByteArray> roleNames() const override;

    // QAbstractItemModel interface
public:
    QVariant data(const QModelIndex &index, int role) const override;

    // TypedListModel interface
public:
    Q_INVOKABLE void removeItem(ToolInfo *item) override;
};


class ToolNode:public FlowNode
{
    Q_OBJECT


    Q_PROPERTY(ToolInfoList* tools READ tools WRITE setTools NOTIFY toolsChanged USER("serialize"))

    Q_PROPERTY(ToolInfo* currentTool READ currentTool WRITE setCurrentTool NOTIFY currentToolChanged)


    Q_PROPERTY(QVariant checkTool READ checkTool WRITE setCheckTool NOTIFY checkToolChanged REVISION 30)
    Q_PROPERTY(QVariant currentToolId READ currentToolId WRITE setCurrentToolId NOTIFY currentToolIdChanged REVISION 30)
    Q_PROPERTY(QVariant currentProjectName READ currentProjectName WRITE setCurrentProjectName NOTIFY currentProjectNameChanged REVISION 30)

    Q_PROPERTY(QVariant toolOK READ toolOK WRITE setToolOK NOTIFY toolOKChanged REVISION 31)
    Q_PROPERTY(QVariant toolNOK READ toolNOK WRITE setToolNOK NOTIFY toolNOKChanged REVISION 31)




public:


    ToolNode();

    static  QQmlComponent*  delegate(QQmlEngine& engine) noexcept;

    ToolInfoList* tools()
    {
        return m_tools;
    }

    Q_INVOKABLE void addTool(QString toolid,QString projectname){
        ToolInfo* newtool=new ToolInfo(toolid,projectname);
        m_tools->addItem(newtool);
    }
    Q_INVOKABLE void updateTool(ToolInfo* tool, QString toolid,QString projectname){
        tool->setId(toolid);
        tool->setProjectName(projectname);
    }

    QVariant checkTool() const
    {
        return m_checkTool;
    }

    QVariant currentToolId() const
    {
        return m_currentToolId;
    }

    QVariant currentProjectName() const
    {
        return m_currentProjectName;
    }

    QVariant toolOK() const
    {
        return m_toolOK;
    }

    QVariant toolNOK() const
    {
        return m_toolNOK;
    }

    ToolInfo* currentTool() const
    {
        return m_currentTool;
    }

public slots:
    void setTools(ToolInfoList* tools)
    {
        if (m_tools == tools)
            return;

        m_tools = tools;
        emit toolsChanged(m_tools);
    }

    void setCheckTool(QVariant checkTool)
    {
        m_checkTool = checkTool;
        if(m_checkTool.value<bool>()){

            doCheckTool();
        }
        emit checkToolChanged(m_checkTool);
    }

    void setCurrentToolId(QVariant currentToolId)
    {


        m_currentToolId = currentToolId;
        emit currentToolIdChanged(m_currentToolId);

        if(checkTool().value<bool>()){
            doCheckTool();
        }
    }

    void setCurrentProjectName(QVariant currentProjectName)
    {


        m_currentProjectName = currentProjectName;
        emit currentProjectNameChanged(m_currentProjectName);
        if(checkTool().value<bool>()){
            doCheckTool();
        }
    }

    void setToolOK(QVariant toolOK)
    {

        m_toolOK = toolOK;

        emit toolOKChanged(m_toolOK);

        setToolNOK(!toolOK.value<bool>());
    }

    void setToolNOK(QVariant toolNOK)
    {

        m_toolNOK = toolNOK;
        emit toolNOKChanged(m_toolNOK);
    }



signals:
    void toolsChanged(ToolInfoList* tools);

    void checkToolChanged(QVariant checkTool);

    void currentToolIdChanged(QVariant currentToolId);

    void currentProjectNameChanged(QVariant currentProjectName);

    void toolOKChanged(QVariant toolOK);

    void toolNOKChanged(QVariant toolNOK);

    void currentToolChanged(ToolInfo* currentTool);

private:

    void doCheckTool(){
        ToolInfo* tool=m_tools->getByToolId(m_currentToolId.value<QString>());

        if(tool){
            setToolOK(tool->projectName()==m_currentProjectName);
        }
        else{
            setToolOK(false);
        }

    }
    void setCurrentTool(ToolInfo* currentTool)
    {
        if (m_currentTool == currentTool)
            return;

        m_currentTool = currentTool;
        emit currentToolChanged(m_currentTool);
    }

    ToolInfoList *m_tools= new ToolInfoList();
    QVariant m_checkTool=false;
    QVariant m_currentToolId=QString("");
    QVariant m_currentProjectName=QString("");
    QVariant m_toolOK=false;
    QVariant m_toolNOK=false;
    ToolInfo* m_currentTool;
};

#endif // TOOLNODE_H
