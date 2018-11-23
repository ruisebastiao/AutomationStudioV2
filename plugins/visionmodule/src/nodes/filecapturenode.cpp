#include "filecapturenode.h"



FileCaptureNode::FileCaptureNode()
{

    m_type=Type::FileCaptureNode;

}




QQmlComponent *FileCaptureNode::delegate(QQmlEngine &engine)noexcept
{


    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/FileCaptureNodeItem.qml"));
    return delegate.get();

}

void FileCaptureNode::processFile()
{

}

void FileCaptureNode::DeSerialize(QJsonObject &json)
{


    CaptureNode::DeSerialize(json);

    FlowNodePort* port=getPortFromKey("frameCaptured");
    if(port){
        port->setHidden(true);
    }
}

