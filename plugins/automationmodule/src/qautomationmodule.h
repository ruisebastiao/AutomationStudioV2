#ifndef QAUTOMATIONMODULE_H
#define QAUTOMATIONMODULE_H

#include <QQuickItem>
#include <jsonserializable.h>
#include "flownode.h"
#include "automationmoduleglobal.h"
#include "qanGraphView.h"
#include "scenegraph.h"
#include "flownodemanager.h"
//#include "project.h"

class Project;

class AUTOMATIONMODULE_EXPORT QAutomationModule : public QQuickItem,public JsonSerializable
{
    Q_OBJECT


    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged USER("serialize"))

    //Q_PROPERTY(User loggedUser READ loggedUser WRITE setLoggedUser NOTIFY loggedUserChanged)


    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged USER("serialize"))
    Q_PROPERTY(bool editMode READ editMode WRITE setEditMode NOTIFY editModeChanged)
    Q_PROPERTY(bool moduleLoaded READ moduleLoaded WRITE setModuleLoaded NOTIFY moduleLoadedChanged)
    Q_PROPERTY(ModuleType type READ type NOTIFY typeChanged USER("serialize"))
    Q_PROPERTY(qan::GraphView* graphView READ graphView WRITE setGraphView NOTIFY graphViewChanged)

    Q_PROPERTY(Project* parentProject READ parentProject WRITE setParentProject NOTIFY parentProjectChanged)


    Q_PROPERTY(QString moduleName READ moduleName NOTIFY moduleNameChanged)

    Q_PROPERTY(FlowNodeManager* flowNodes READ flowNodes WRITE setFlowNodes NOTIFY flowNodesChanged USER("serialize"))

    Q_PROPERTY(QVariant locked READ locked WRITE setLocked NOTIFY lockedChanged REVISION 2)



public:
    enum ModuleType {
        AutomationModule,
        EpsonModule,
        VisionModule,
        BSValidationModule,
        ClockModule
    };

    Q_ENUM(ModuleType)


    QAutomationModule(QQuickItem *parent=nullptr);
    QAutomationModule(const QAutomationModule& other){ }

    ~QAutomationModule() override;


    template<typename QEnum>
    static std::string QtEnumToString (const QEnum value)
    {

        return std::string(QMetaEnum::fromType<QEnum>().valueToKey(value));
    }
    static QList<QString> QtEnumsToStrings (bool lowercase=false)
    {

        QList<QString> enums;

        int enumscount=QMetaEnum::fromType<ModuleType>().keyCount();

        for (int i = 0; i < enumscount; ++i) {
            std::string enum_str=std::string(QMetaEnum::fromType<ModuleType>().valueToKey(i));
            QString moduletypename=QString::fromUtf8(enum_str.c_str());
            if(lowercase){
                moduletypename=moduletypename.toLower();
            }

            enums.append(moduletypename);
        }

        return enums;
    }

    ModuleType type() const;


    QString name() const
    {
        return m_name;
    }

    bool moduleLoaded() const
    {
        return m_moduleLoaded;
    }

    bool editMode() const
    {
        return m_editMode;
    }


    qan::GraphView* graphView() const
    {
        return m_graphView;
    }




    //    FlowNode* readNode(QJsonObject nodeobject);

private:



    QString m_name;


    QJsonObject m_configurationsObject;

    bool m_moduleLoaded=false;

    QString m_moduleConfigPath="";

    bool m_editMode=false;







    int m_id=-1;

    FlowNodeManager* m_flowNodes= new FlowNodeManager(this);

protected:
    qan::GraphView* m_graphView=nullptr;
    QString m_moduleName="";


signals:
    void nameChanged(QString name);

    void moduleconfigChanged(QString moduleconfig);

    void moduleLoadedChanged(bool moduleLoaded);

    void editModeChanged(bool editMode);
    void sceneChanged(SceneGraph* scene);

    void graphViewChanged(qan::GraphView* graphView);

    void typeChanged(ModuleType type);


    void configSourceChanged(QString configSource);



    void moduleNameChanged(QString moduleName);

    void idChanged(int id);

    void flowNodesChanged(FlowNodeManager* flowNodes);

    void componentCompleted();

    void parentProjectChanged(Project* parentProject);



    void lockedChanged(QVariant locked);

    void waitUserMessageChanged(QVariant waitUserMessage);

    void waitUserChanged(QVariant waitUser);

public slots:
    void setName(QString name)
    {
        if (m_name == name)
            return;

        m_name = name;
        emit nameChanged(m_name);
    }

    void setModuleLoaded(bool moduleLoaded);

    void setEditMode(bool editMode)
    {
        if (m_editMode == editMode)
            return;

        m_editMode = editMode;
        emit editModeChanged(m_editMode);
    }


    virtual void setGraphView(qan::GraphView* graphView);


    // JsonSerializable interface


    void setId(int id)
    {
        if (m_id == id)
            return;

        m_id = id;
        emit idChanged(m_id);
    }



    // JsonSerializable interface
    void setParentProject(Project* parentProject)
    {
        if (m_parentProject == parentProject)
            return;

        m_parentProject = parentProject;
        emit parentProjectChanged(m_parentProject);
    }


    void setLocked(QVariant locked)
    {
        if (m_locked == locked)
            return;

        m_locked = locked;
        emit lockedChanged(m_locked);
    }


public:
    void Serialize(QJsonObject &json) override;
    void DeSerialize(QJsonObject &json) override;




    //    Q_INVOKABLE void loadConnections();



    QString moduleName() const
    {
        return m_moduleName;
    }


    //    static FlowNode* getFlowNodeById(int id,QList<FlowNode *> nodeList);



    int id() const
    {
        return m_id;
    }

    FlowNodeManager* flowNodes() const
    {
        return m_flowNodes;
    }


    Project* parentProject() const
    {
        return m_parentProject;
    }


    void initializeModuleProxyNodes();
    void initializeProjectNodes();
    QVariant locked() const
    {
        return m_locked;
    }


protected:
    //   Q_INVOKABLE virtual void loadModuleSettings(QString path);
    //   Q_INVOKABLE virtual void save();

    ModuleType m_type=ModuleType::AutomationModule;


private:
    void setFlowNodes(FlowNodeManager* flowNodes)
    {
        if (m_flowNodes == flowNodes)
            return;

        m_flowNodes = flowNodes;
        emit flowNodesChanged(m_flowNodes);
    }

    Project* m_parentProject=nullptr;


    QVariant m_locked=false;

};

#endif // QAUTOMATIONMODULE_H
