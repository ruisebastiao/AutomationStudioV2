#ifndef EPSONNODE_H
#define EPSONNODE_H

#include <flownode.h>



class EpsonNode : public FlowNode
{
public:
    EpsonNode();
    static  QQmlComponent*      delegate(QQmlEngine& engine) noexcept;
};

#endif // EPSONNODE_H
