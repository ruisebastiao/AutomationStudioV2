#ifndef SUBPROJECTINFONODE_H
#define SUBPROJECTINFONODE_H

#include <flownode.h>
#include <serializedlistmodel.h>


class SubProjectInfo:public QObject, public JsonSerializable
{
    Q_OBJECT
    Q_INTERFACES(JsonSerializable)


    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged USER("serialize"))
    Q_PROPERTY(QString projectName READ projectName WRITE setProjectName NOTIFY projectNameChanged USER("serialize"))

public:
    SubProjectInfo();
    SubProjectInfo(QString id,QString projectname);

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

class SubProjectInfoList:public SerializedListModel<SubProjectInfo>
{
    Q_OBJECT
    Q_INTERFACES(JsonSerializable)

public:
    enum InfoRoles {
        ProjectNameRole = Qt::UserRole + 1,
        IDRole,
        InfoRole,
        TextRole
    };
    SubProjectInfoList();
    SubProjectInfoList(const SubProjectInfoList& other){ }



    Q_INVOKABLE SubProjectInfo* getById(QString id){

        for (int var = 0; var < m_internalList.length(); ++var) {
            SubProjectInfo* info=m_internalList.at(var);
            if(info->id()==id){
                return info;
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
    Q_INVOKABLE void removeItem(SubProjectInfo *item) override;
};


class SubProjectInfoNode:public FlowNode
{
    Q_OBJECT


    Q_PROPERTY(SubProjectInfoList* infos READ infos WRITE setInfos NOTIFY infosChanged USER("serialize"))
    Q_PROPERTY(QString infoTitle READ infoTitle WRITE setInfoTitle NOTIFY infoTitleChanged USER("serialize"))


    Q_PROPERTY(SubProjectInfo* currentInfo READ currentInfo WRITE setCurrentInfo NOTIFY currentInfoChanged)


    Q_PROPERTY(QVariant checkInfo READ checkInfo WRITE setCheckInfo NOTIFY checkInfoChanged REVISION 30)
    Q_PROPERTY(QVariant currentInfoId READ currentInfoId WRITE setCurrentInfoId NOTIFY currentInfoIdChanged REVISION 30)
    Q_PROPERTY(QVariant currentProjectName READ currentProjectName WRITE setCurrentProjectName NOTIFY currentProjectNameChanged REVISION 30)

    Q_PROPERTY(QVariant infoOK READ infoOK WRITE setInfoOK NOTIFY infoOKChanged REVISION 31)
    Q_PROPERTY(QVariant infoNOK READ infoNOK WRITE setInfoNOK NOTIFY infoNOKChanged REVISION 31)




public:


    SubProjectInfoNode();

    static  QQmlComponent*  delegate(QQmlEngine& engine) noexcept;

    SubProjectInfoList* infos()
    {
        return m_infos;
    }

    Q_INVOKABLE void addInfo(QString id,QString projectname){
        SubProjectInfo* newinfo=new SubProjectInfo(id,projectname);
        m_infos->addItem(newinfo);
    }
    Q_INVOKABLE void updateInfo(SubProjectInfo* info, QString infoid,QString projectname){
        info->setId(infoid);
        info->setProjectName(projectname);
    }

    QVariant checkInfo() const
    {
        return m_checkInfo;
    }

    QVariant currentInfoId() const
    {
        return m_currentInfoId;
    }

    QVariant currentProjectName() const
    {
        return m_currentProjectName;
    }

    QVariant infoOK() const
    {
        return m_infoOK;
    }

    QVariant infoNOK() const
    {
        return m_infoNOK;
    }

    SubProjectInfo* currentInfo() const
    {
        return m_currentInfo;
    }

    QString infoTitle() const
    {
        return m_infoTitle;
    }

public slots:
    void setInfos(SubProjectInfoList* infos)
    {
        if (m_infos == infos)
            return;

        m_infos = infos;
        emit infosChanged(m_infos);
    }

    void setCheckInfo(QVariant checkInfo)
    {
        m_checkInfo = checkInfo;
        if(m_checkInfo.value<bool>()){

            doCheckInfo();
        }
        emit checkInfoChanged(m_checkInfo);
    }

    void setCurrentInfoId(QVariant currentInfoId)
    {


        m_currentInfoId = currentInfoId;
        emit currentInfoIdChanged(m_currentInfoId);

        if(checkInfo().value<bool>()){
            doCheckInfo();
        }
    }

    void setCurrentProjectName(QVariant currentProjectName)
    {


        m_currentProjectName = currentProjectName;
        emit currentProjectNameChanged(m_currentProjectName);
        if(checkInfo().value<bool>()){
            doCheckInfo();
        }
    }

    void setInfoOK(QVariant infoOK)
    {

        m_infoOK = infoOK;

        emit infoOKChanged(m_infoOK);

        setInfoNOK(!infoOK.value<bool>());
    }

    void setInfoNOK(QVariant infoNOK)
    {

        m_infoNOK = infoNOK;
        emit infoNOKChanged(m_infoNOK);
    }



    void setInfoTitle(QString infoTitle)
    {
        if (m_infoTitle == infoTitle)
            return;

        m_infoTitle = infoTitle;
        emit infoTitleChanged(m_infoTitle);
    }

signals:
    void infosChanged(SubProjectInfoList* infos);

    void checkInfoChanged(QVariant checkInfo);

    void currentInfoIdChanged(QVariant currentInfoId);

    void currentProjectNameChanged(QVariant currentProjectName);

    void infoOKChanged(QVariant infoOK);

    void infoNOKChanged(QVariant infoNOK);

    void currentInfoChanged(SubProjectInfo* currentInfo);

    void infoTitleChanged(QString infoTitle);

private:

    void doCheckInfo(){
        SubProjectInfo* info=m_infos->getById(m_currentInfoId.value<QString>());

        if(info){
            setInfoOK(info->projectName()==m_currentProjectName);
        }
        else{
            setInfoOK(false);
        }

    }
    void setCurrentInfo(SubProjectInfo* currentInfo)
    {
        if (m_currentInfo == currentInfo)
            return;

        m_currentInfo = currentInfo;
        emit currentInfoChanged(m_currentInfo);
    }

    SubProjectInfoList *m_infos= new SubProjectInfoList();
    QVariant m_checkInfo=false;
    QVariant m_currentInfoId=QString("");
    QVariant m_currentProjectName=QString("");
    QVariant m_infoOK=false;
    QVariant m_infoNOK=false;
    SubProjectInfo* m_currentInfo;
    QString m_infoTitle="Info Title";
};

#endif // SUBPROJECTINFONODE_H
