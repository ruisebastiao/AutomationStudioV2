#ifndef QAUTOMATIONMODULE_H
#define QAUTOMATIONMODULE_H

#include <QQuickItem>
#include <automationstudiocore/jsonserializable.h>
#include <flownode.h>
#include <flownodemanager.h>
#include "automationmoduleglobal.h"
#include "qanGraphview.h"
#include <scenegraph.h>


class AUTOMATIONMODULE_EXPORT QAutomationModule : public QQuickItem,public JsonSerializable
{
    Q_OBJECT

    Q_PROPERTY(QString moduleID READ moduleID WRITE setModuleID NOTIFY moduleIDChanged USER("serialize"))

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged USER("serialize"))
    Q_PROPERTY(bool editMode READ editMode WRITE setEditMode NOTIFY editModeChanged)
    Q_PROPERTY(bool moduleLoaded READ moduleLoaded WRITE setModuleLoaded NOTIFY moduleLoadedChanged)
    Q_PROPERTY(ModuleType type READ type WRITE setType NOTIFY typeChanged USER("serialize"))
    Q_PROPERTY(qan::GraphView* graphView READ graphView WRITE setGraphView NOTIFY graphViewChanged)
    Q_PROPERTY(QString configSource READ configSource WRITE setConfigSource NOTIFY configSourceChanged)


public:
    enum ModuleType {
        AutomationModule,
        EpsonRobotModule,
        VisionSystemModule,
        BSValidationModule,
        ClockModule
    };

    Q_ENUM(ModuleType)


    QAutomationModule(QQuickItem *parent=nullptr);
    QAutomationModule(const QAutomationModule& other){ }


    static FlowNodeManager* flownodemanager;

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

    virtual ModuleType type() const;


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


    FlowNode* getFlowNodeById(int id);

private:

    QString m_name;


    QJsonObject m_configurationsObject;

    bool m_moduleLoaded=false;

    QString m_moduleConfigPath="";

    bool m_editMode=false;



    qan::GraphView* m_graphView;

    ModuleType m_type;
    QString m_moduleID="";

    QString m_configSource="";

protected:
      QList<FlowNode *> m_FlowNodes;


signals:
    void nameChanged(QString name);

    void moduleconfigChanged(QString moduleconfig);

    void moduleLoadedChanged(bool moduleLoaded);

    void editModeChanged(bool editMode);
    void sceneChanged(SceneGraph* scene);

    void graphViewChanged(qan::GraphView* graphView);

    void typeChanged(ModuleType type);

    void moduleIDChanged(QString moduleID);
    void configSourceChanged(QString configSource);

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
    void setType(ModuleType type)
    {
        if (m_type == type)
            return;

        m_type = type;
        emit typeChanged(m_type);
    }

    // JsonSerializable interface
    void setModuleID(QString moduleID)
    {
        if (m_moduleID == moduleID)
            return;

        m_moduleID = moduleID;
        emit moduleIDChanged(m_moduleID);
    }

    void setConfigSource(QString configSource)
    {
        if (m_configSource == configSource)
            return;

        m_configSource = configSource;
        emit configSourceChanged(m_configSource);

    }

public:
    void Serialize(QJsonObject &json, QObject *target) override;
    void DeSerialize(QJsonObject &json, QObject *target) override;
    QString moduleID() const
    {
        return m_moduleID;
    }

    // JsonSerializable interface
public:
    void Serialize(QJsonObject &json) override;
    void DeSerialize(QJsonObject &json) override;
    QString configSource() const
    {
        return m_configSource;
    }
protected:
   Q_INVOKABLE virtual void load(QString path);
   Q_INVOKABLE virtual void save();

    virtual FlowNode* readNode(qan::GraphView* graphView ,QJsonObject nodeobject);
};

#endif // QAUTOMATIONMODULE_H
