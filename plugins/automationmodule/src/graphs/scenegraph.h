#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

// QuickQanava headers
//#include <QuickQanava>

// Qt headers
#include <QQuickPaintedItem>
#include <qanGraph.h>

#include "automationmoduleglobal.h"

#include "selectableedge.h"


class AUTOMATIONMODULE_EXPORT SceneGraph : public qan::Graph
{
    Q_OBJECT
public:
    explicit SceneGraph( QQuickItem* parent = nullptr ) noexcept : qan::Graph(parent) {


        QObject::connect(this, &qan::Graph::connectorRequestPortEdgeCreation, this, [this](qan::PortItem* src,qan::PortItem* dst){

            if(isEdgeDestinationBindable(*dst)){
                qan::Edge* newedge= this->insertNewEdge(false,src->getNode(),dst->getNode());

                this->bindEdge(newedge,src,dst);
            }
        });

    }

public:
    //    Q_INVOKABLE  void insertBarcodeReaderNode(BarcodeReaderNode *node);


    Q_INVOKABLE void deleteEdge(qan::Edge *edge);

    QPointer<QQuickItem> createDock(qan::NodeItem::Dock dock, qan::Node& node) noexcept;

    //    Q_INVOKABLE qan::Node*  insertFlowNode(int type) { return insertFlowNode(static_cast<FlowNode::Type>(type)); }       // FlowNode::Type could not be used from QML, Qt 5.10 bug???
    //    qan::Node*              insertFlowNode(FlowNode::Type type);

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
};


QML_DECLARE_TYPE(SceneGraph)



#endif // SCENEGRAPH_H
