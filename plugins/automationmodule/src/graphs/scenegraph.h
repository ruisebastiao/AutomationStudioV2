#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

// QuickQanava headers
//#include <QuickQanava>

// Qt headers
#include <QQuickPaintedItem>
#include <flownode.h>
#include <qanGraph.h>

#include "automationmoduleglobal.h"

#include "selectableedge.h"



class FlowNode;
class QAutomationModule;

class AUTOMATIONMODULE_EXPORT SceneGraph : public qan::Graph
{
    Q_OBJECT

    Q_PROPERTY(QVariantList commonNodeTypes READ commonNodeTypes NOTIFY commonNodeTypesChanged)
    Q_PROPERTY(QVariantList moduleNodeTypes READ moduleNodeTypes NOTIFY moduleNodeTypesChanged)


public:
    explicit SceneGraph( QQuickItem* parent = nullptr ) noexcept;

    virtual FlowNode* createNode(QString nodetype);

    Q_INVOKABLE virtual void addNode(QPoint loc, QVariantMap nodeinfo);

public:
    //    Q_INVOKABLE  void insertBarcodeReaderNode(BarcodeReaderNode *node);


    Q_INVOKABLE void deleteEdge(qan::Edge *edge);

    QPointer<QQuickItem> createDock(qan::NodeItem::Dock dock, qan::Node& node) noexcept;


public slots:

    void  onConnectorRequestEdgeCreation(qan::Node* src, QObject* dst);

    // Graph interface
public:
    virtual qan::Edge *insertNewEdge(bool hidden, qan::Node *source, qan::Node *destination);
    //    qan::Edge *insertEdge(qan::Node *source, qan::Edge *destination, QQmlComponent *edgeComponent= nullptr) override;

    // Graph interface
public:
    void bindEdgeDestination(qan::Edge &edge, qan::PortItem &inPort) noexcept override;

    // Graph interface
public:
    void bindEdge(qan::Edge *edge, qan::PortItem *outPort, qan::PortItem *inPort) noexcept override;
    virtual FlowNode *readNode(QJsonObject nodeobject);

    QVariantList commonNodeTypes() const
    {
        return m_commonNodeTypes;
    }

    QVariantList moduleNodeTypes() const
    {
        return m_moduleNodeTypes;
    }

signals:
    void flowNodeAdded(FlowNode* flownode);

    void commonNodeTypesChanged(QVariantList commonNodeTypes);

    void moduleNodeTypesChanged(QVariantList moduleNodeTypes);

private:
    void getCommonTypes();

    QVariantList m_commonNodeTypes;

protected:
    QVariantList m_moduleNodeTypes;

};



QML_DECLARE_TYPE(SceneGraph)



#endif // SCENEGRAPH_H
