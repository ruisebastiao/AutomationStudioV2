#ifndef FLOWNODE_H
#define FLOWNODE_H

#include <qanNode.h>
#include "automationmoduleglobal.h"
#include "scenegraph.h"
#include <jsonserializable.h>

#include <flownodeport.h>
#include <random>


class FlowNodePort;

class QAutomationModule;


using namespace std;

class AUTOMATIONMODULE_EXPORT FlowNode : public qan::Node, public JsonSerializable
{

    // PROPERTIES WITH REVISION 30 WILL BE ATTACHED TO IN PORTS PORTS
    // PROPERTIES WITH REVISION 31 WILL BE ATTACHED TO OUT PORTS PORTS

    Q_OBJECT

    Q_INTERFACES(JsonSerializable)

    Q_PROPERTY(Type type READ getType CONSTANT FINAL USER("serialize"))

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged USER("serialize"))

    Q_PROPERTY(bool configsLoaded READ configsLoaded WRITE setConfigsLoaded NOTIFY configsLoadedChanged)

    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged USER("serialize"))

    Q_PROPERTY(int normalWidth READ normalWidth WRITE setNormalWidth NOTIFY normalWidthChanged  USER("serialize"))
    Q_PROPERTY(int normalHeight READ normalHeight WRITE setNormalHeight NOTIFY normalHeightChanged  USER("serialize"))


    Q_PROPERTY(int editWidth READ editWidth WRITE setEditWidth NOTIFY editWidthChanged)
    Q_PROPERTY(int editHeight READ editHeight WRITE setEditHeight NOTIFY editHeightChanged)

    Q_PROPERTY(qreal nodeX READ nodeX WRITE setNodeX NOTIFY nodeXChanged)
    Q_PROPERTY(qreal nodeY READ nodeY WRITE setNodeY NOTIFY nodeYChanged)

    Q_PROPERTY(bool connectionsLoaded READ connectionsLoaded WRITE setConnectionsLoaded NOTIFY connectionsLoadedChanged)

    Q_PROPERTY(bool portsInitialized READ portsInitialized WRITE setPortsInitialized NOTIFY portsInitializedChanged)


//    Q_PROPERTY(bool connectionsLoaded READ connectionsLoaded WRITE setConnectionsLoaded NOTIFY connectionsLoadedChanged)


    Q_PROPERTY(bool editMode READ editMode WRITE setEditMode NOTIFY editModeChanged)

    Q_PROPERTY(bool locked READ locked WRITE setLocked NOTIFY lockedChanged  USER("serialize"))

    Q_PROPERTY(bool centerOnEdit READ centerOnEdit WRITE setCenterOnEdit NOTIFY centerOnEditChanged)


    Q_PROPERTY(QAutomationModule* parentModule READ parentModule WRITE setParentModule NOTIFY parentModuleChanged)

    Q_PROPERTY(QString typeInfo READ typeInfo NOTIFY typeInfoChanged)

    Q_PROPERTY(bool projectLoaded READ projectLoaded WRITE setProjectLoaded NOTIFY projectLoadedChanged)

    Q_PROPERTY(QVariant disabled READ disabled WRITE setDisabled NOTIFY disabledChanged REVISION 30)


public:
    enum class Type {
        NodeNone,
        BarcodeReaderNode,
        StringNode,
        WebServiceNode,
        BSValidationNode,
        IDSCaptureNode,
        FrameViewerNode,
        SetResetNode,
        ProxyNode,
        VisionSystemNode,
        FileCaptureNode,
        ROINode,
        ProcessingNode,
        ObjectPropertyNode,
        WebCamCaptureNode,
        FrameBufferNode,
        ModulePropertyBind,
        UIComponentNode,
        EpsonNode,
        MultiplexedInputNode,
        NumericNode,
        ModuleProxyNode,
        CommandSenderNode,
        StringBuilderNode,
        CommandParserNode,
        LogicNode,
        ProjectNode,
        SerialIONode,
        EpsonRemote,
        PropertiesNode,
        ArrayNode,
        ProcessNode

    };
    Q_ENUM(Type)

    FlowNode( QObject* parent = nullptr );





    operator QString() const {
        QString  ret(metaObject()->className());
        ret.append(":Name:"+name());
        ret.append(":ID:"+QString::number(id()));
        return ret;
    }


    //static void registerContainer()

    bool operator==(const FlowNode &a)
    {
        return a.id()==id();
    }

    bool operator==(const FlowNode* a)
    {
        return a->id()==id();
    }

    friend ostream& operator<<(ostream &os, const  FlowNode& c);
    friend QDataStream& operator <<(QDataStream &stream, FlowNode &c);



    virtual ~FlowNode() override;


    static  QQmlComponent*      delegate(QQmlEngine& engine) noexcept;
    //    virtual void write(QJsonObject &json) const;
    //    virtual void read(QJsonObject &json);

    virtual QString name() const
    {
        return m_name;
    }
    inline  Type    getType() const noexcept { return m_type; }
    bool configsLoaded() const
    {
        return m_configsLoaded;
    }

    int id() const
    {
        return m_id;
    }


    virtual void initializeNode(int id);

    void initializePorts();

    Q_INVOKABLE void remove();

    Q_INVOKABLE FlowNodePort* getPortFromKey(QString key) const;

private:

    bool m_portsInitialized=false;
protected:
    Type            m_type{Type::NodeNone};




private:

    //void setPortConnection(int createdNodeId);

    SceneGraph* m_scenegraph=nullptr;

    bool m_configsLoaded=false;

    int m_id=-1;


    int m_editWidth=250;

    int m_editHeight=250;

    bool m_editMode=false;
    qreal m_lastcenterX=0;
    qreal m_lastcenterY=0;
    qreal m_lastZoom=1;



    int m_normalWidth=250;

    int m_normalHeight=250;

    bool m_locked=false;

    qreal m_nodeX=0;

    qreal m_nodeY=0;

    bool m_centerOnEdit=false;


    QAutomationModule* m_parentModule=nullptr;

    QString m_typeInfo;

    bool m_connectionsLoaded=false;

    bool m_projectLoaded=false;

    void setPortsInitialized(bool portsInitialized)
    {
        if (m_portsInitialized == portsInitialized)
            return;

        m_portsInitialized = portsInitialized;
        emit portsInitializedChanged(m_portsInitialized);
    }

    QVariant m_disabled=false;

public slots:
    virtual void    inNodeOutputChanged();

    virtual void setParentModule(QAutomationModule* parentModule);


    void setName(QString name)
    {
        if (m_name == name)
            return;

        m_name = name;
        emit nameChanged(m_name);
    }
    void setConfigsLoaded(bool configsLoaded)
    {
        if (m_configsLoaded == configsLoaded)
            return;

        m_configsLoaded = configsLoaded;
        emit configsLoadedChanged(m_configsLoaded);
    }


    void setEditWidth(int editWidth)
    {
        if (m_editWidth == editWidth)
            return;

//        if(editWidth<250)
//            editWidth=250;

        m_editWidth = editWidth;
        emit editWidthChanged(m_editWidth);
    }

    void setEditHeight(int editHeight)
    {
        if (m_editHeight == editHeight)
            return;

//        if(editHeight<250)
//            editHeight=250;


        m_editHeight = editHeight;
        emit editHeightChanged(m_editHeight);
    }

    void setEditMode(bool editMode)
    {
        if (m_editMode == editMode)
            return;

        m_editMode = editMode;
        emit editModeChanged(m_editMode);
    }


    void setNormalWidth(int normalWidth)
    {
        if (m_normalWidth == normalWidth || normalWidth==0)
            return;

        m_normalWidth = normalWidth;
        //    getItem()->setProperty("width",QVariant::fromValue(m_normalWidth));

        emit normalWidthChanged(m_normalWidth);
    }

    void setNormalHeight(int normalHeight)
    {
        if (m_normalHeight == normalHeight || normalHeight ==0)
            return;

        m_normalHeight = normalHeight;
        // getItem()->setProperty("height",QVariant::fromValue(m_normalHeight));


        emit normalHeightChanged(m_normalHeight);
    }

    void setLocked(bool locked)
    {
        if (m_locked == locked)
            return;

        m_locked = locked;
        emit lockedChanged(m_locked);
    }

    void setNodeX(qreal nodeX)
    {

        if (qFuzzyCompare(m_nodeX, nodeX))
            return;

        m_nodeX = nodeX;
        emit nodeXChanged(m_nodeX);
    }

    void setNodeY(qreal nodeY)
    {

        if (qFuzzyCompare(m_nodeY, nodeY))
            return;

        m_nodeY = nodeY;
        emit nodeYChanged(m_nodeY);
    }

    void setCenterOnEdit(bool centerOnEdit)
    {
        if (m_centerOnEdit == centerOnEdit)
            return;

        m_centerOnEdit = centerOnEdit;
        emit centerOnEditChanged(m_centerOnEdit);
    }

//    void setConnectionsLoaded(bool connectionsLoaded)
//    {
//        if (m_connectionsLoaded == connectionsLoaded)
//            return;

//        m_connectionsLoaded = connectionsLoaded;

//        if(m_connectionsLoaded){
//            this->blockSignals(false);
//        }
//        emit connectionsLoadedChanged(m_connectionsLoaded);
//    }






    void setConnectionsLoaded(bool connectionsLoaded)
    {
        if (m_connectionsLoaded == connectionsLoaded)
            return;

        m_connectionsLoaded = connectionsLoaded;
        emit connectionsLoadedChanged(m_connectionsLoaded);
    }

    virtual void setProjectLoaded(bool projectLoaded)
    {
        if (m_projectLoaded == projectLoaded)
            return;

        m_projectLoaded = projectLoaded;
        emit projectLoadedChanged(m_projectLoaded);
    }



    void setDisabled(QVariant disabled)
    {
        if (m_disabled == disabled)
            return;

        m_disabled = disabled;
        emit disabledChanged(m_disabled);
    }

signals:
    void nameChanged(QString name);

    void removeNode(FlowNode*);

//    void bindPortLabelToProperty(qan::PortItem* portItem,QString nodeProperty);

//    void bindSourceProperty(qan::Node* sourceNode,QString sourceProperty,QString targetProperty);

//    void unbindSourceProperty(QString targetProperty);

//    void bindPropertyToTarget(QString sourceproperty,QObject* target,QString targetproperty);
    //    void bindToOutput( qan::Node* outputNode);

    void configsLoadedChanged(bool configsLoaded);

    void idChanged(int id);

    void editWidthChanged(int editWidth);

    void editHeightChanged(int editHeight);

    void editModeChanged(bool editMode);

    void normalWidthChanged(int normalWidth);

    void normalHeightChanged(int normalHeight);

    void lockedChanged(bool locked);

    void nodeXChanged(qreal nodeX);

    void nodeYChanged(qreal nodeY);

    void centerOnEditChanged(bool centerOnEdit);

    void connectionsLoadedChanged(bool connectionsLoaded);

    void parentModuleChanged(QAutomationModule* parentModule);

    void typeInfoChanged(QString typeInfo);

    void projectLoadedChanged(bool projectLoaded);

    void portsInitializedChanged(bool portsInitialized);

    void disabledChanged(QVariant disabled);

protected:

    QString m_name="";

    QMap<string,FlowNodePort*> m_inPorts;
    QMap<string,FlowNodePort*> m_outPorts;

    // JsonSerializable interface
public:
    void Serialize(QJsonObject &json) override;
    void DeSerialize(QJsonObject &json) override;

    // JsonSerializable interface
public:


    void setId(int id)
    {
        if (m_id == id)
            return;

        m_id = id;
        emit idChanged(m_id);
    }

    int editWidth() const
    {
        return m_editWidth;
    }
    int editHeight() const
    {
        return m_editHeight;
    }

    bool editMode() const
    {
        return m_editMode;
    }



    int normalWidth() const
    {
        return m_normalWidth;
    }
    int normalHeight() const
    {
        return m_normalHeight;
    }
    bool locked() const
    {
        return m_locked;
    }
    qreal nodeX() const
    {
        return m_nodeX;
    }
    qreal nodeY() const
    {
        return m_nodeY;
    }


    bool centerOnEdit() const
    {
        return m_centerOnEdit;
    }

    // Node interface
public:
    void installBehaviour(std::unique_ptr<qan::NodeBehaviour> behaviour) override;

    //void updateConnections(FlowNodePort* sourceNode,);
    QMap<string,FlowNodePort *> getInPorts() const;
    QMap<string,FlowNodePort *> getOutPorts() const;
    SceneGraph *getScenegraph() const;
    FlowNodePort *getPortByID(QString id) const;
//    bool connectionsLoaded() const
//    {
//        return m_connectionsLoaded;
//    }

    FlowNodePort* createPort(QString portID,qan::PortItem::Type port_type);


    QAutomationModule* parentModule() const
    {
        return m_parentModule;
    }
    QString typeInfo() const;
    bool connectionsLoaded() const
    {
        return m_connectionsLoaded;
    }
    bool projectLoaded() const
    {
        return m_projectLoaded;
    }
    bool portsInitialized() const
    {
        return m_portsInitialized;
    }
    QVariant disabled() const
    {
        return m_disabled;
    }
};
#endif // FLOWNODE_H
