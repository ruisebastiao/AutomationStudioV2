#ifndef VISUALNODE_H
#define VISUALNODE_H

#include "flownode.h"

#include <QObject>

class AUTOMATIONMODULE_EXPORT VisualNode : public FlowNode
{
    Q_OBJECT
public:
    VisualNode();



    // JsonSerializable interface
public:
    void DeSerialize(QJsonObject &json) override;

    // JsonSerializable interface
public:
    void Serialize(QJsonObject &json) override;
};

#endif // VISUALNODE_H
