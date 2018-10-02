#include "filecapturenode.h"



FileCaptureNode::FileCaptureNode()
{

    m_type=Type::FileCaptureNode;

}




QQmlComponent *FileCaptureNode::delegate(QQmlEngine &engine)noexcept
{


    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:/components/nodes/FileCaptureNode.qml"));
    return delegate.get();

}

void FileCaptureNode::processFile()
{

}

void FileCaptureNode::DeSerialize(QJsonObject &json)
{

    m_filePathPort= new FlowNodePort(this,qan::PortItem::Type::In,"filePath");

    CaptureNode::DeSerialize(json);
}
