#ifndef QAUTOMATIONMODULE_H
#define QAUTOMATIONMODULE_H

#include <QQuickItem>
#include <automationstudiocore/jsonserializable.h>
#include "flownode.h"
#include "automationmoduleglobal.h"
#include "qanGraphView.h"
#include "scenegraph.h"
#include "flownodemanager.h"


class AUTOMATIONMODULE_EXPORT QAutomationModule : public QQuickItem,public JsonSerializable
{
    Q_OBJECT

    Q_PROPERTY(int moduleID READ moduleID WRITE setModuleID NOTIFY moduleIDChanged)

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged USER("serialize"))
    Q_PROPERTY(bool editMode READ editMode WRITE setEditMode NOTIFY editModeChanged)
    Q_PROPERTY(bool moduleLoaded READ moduleLoaded WRITE setModuleLoaded NOTIFY moduleLoadedChanged)
    Q_PROPERTY(ModuleType type READ type NOTIFY typeChanged USER("serialize"))
    Q_PROPERTY(qan::GraphView* graphView READ graphView WRITE setGraphView NOTIFY graphViewChanged)

    Q_PROPERTY(QVariantList commonNodeTypes READ commonNodeTypes NOTIFY commonNodeTypesChanged)

    Q_PROPERTY(QVariantList moduleNodeTypes READ moduleNodeTypes NOTIFY moduleNodeTypesChanged)

    Q_PROPERTY(QString moduleName READ moduleName NOTIFY moduleNameChanged)

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


    Q_INVOKABLE FlowNode *addCommonNode(QPoint loc, QVariantMap nodeinfo, qan::GraphView *graphview);
    Q_INVOKABLE virtual void addModuleNode(QPoint loc, QVariantMap nodeinfo, qan::GraphView *graphview);


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





private:

    FlowNode* readNode(qan::GraphView* graphView ,QJsonObject nodeobject);

    QString m_name;


    QJsonObject m_configurationsObject;

    bool m_moduleLoaded=false;

    QString m_moduleConfigPath="";

    bool m_editMode=false;



    qan::GraphView* m_graphView;


    int m_moduleID=-1;


    QVariantList m_commonNodeTypes;


    FlowNodeManager* m_flownodemanager= new FlowNodeManager(this);



protected:
//      QList<FlowNode *> m_FlowNodes;
      QString m_moduleName="";
      QVariantList m_moduleNodeTypes;

signals:
    void nameChanged(QString name);

    void moduleconfigChanged(QString moduleconfig);

    void moduleLoadedChanged(bool moduleLoaded);

    void editModeChanged(bool editMode);
    void sceneChanged(SceneGraph* scene);

    void graphViewChanged(qan::GraphView* graphView);

    void typeChanged(ModuleType type);

    void moduleIDChanged(int moduleID);
    void configSourceChanged(QString configSource);

    void commonNodeTypesChanged(QVariantList commonNodeTypes);

    void moduleNodeTypesChanged(QVariantList moduleNodeTypes);

    void moduleNameChanged(QString moduleName);

public slots:
    void setName(QString name)
    {
        if (m_name == name)
            return;

        m_name = name;
        emit nameChanged(m_name);
    }

    void setModuleLoaded(bool moduleLoaded)
    {
        if (m_moduleLoaded == moduleLoaded)
            return;

        m_moduleLoaded = moduleLoaded;
        emit moduleLoadedChanged(m_moduleLoaded);
    }
    void setEditMode(bool editMode)
    {
        if (m_editMode == editMode)
            return;

        m_editMode = editMode;
        emit editModeChanged(m_editMode);
    }


    virtual void setGraphView(qan::GraphView* graphView);


    // JsonSerializable interface
    void setModuleID(int moduleID)
    {
        if (m_moduleID == moduleID)
            return;

        m_moduleID = moduleID;
        emit moduleIDChanged(m_moduleID);
    }

public:
//    void Serialize(QJsonObject &json, QObject *target) override;
//    void DeSerialize(QJsonObject &json, QObject *target) override;
    int moduleID() const
    {
        return m_moduleID;
    }

    // JsonSerializable interface
public:
    void Serialize(QJsonObject &json) override;
    void DeSerialize(QJsonObject &json) override;


    FlowNode* createCommonNode(qan::GraphView* graphView , QString nodetype);

    virtual FlowNode *createModuleNode(qan::GraphView* graphView , QString nodetype)=0;

    static QList<FlowNode*> proxyFlowNodes;


    Q_INVOKABLE void loadConnections();
    QVariantList commonNodeTypes() const
    {
        return m_commonNodeTypes;
    }

    QVariantList moduleNodeTypes() const
    {
        return m_moduleNodeTypes;
    }

    QString moduleName() const
    {
        return m_moduleName;
    }


    //    static FlowNode* getFlowNodeById(int id,QList<FlowNode *> nodeList);



protected:
   Q_INVOKABLE virtual void loadModuleSettings(QString path);
   Q_INVOKABLE virtual void save();

    ModuleType m_type=ModuleType::AutomationModule;





};

#endif // QAUTOMATIONMODULE_H
