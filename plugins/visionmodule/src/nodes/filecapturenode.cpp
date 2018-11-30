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
    if(m_useSequence==true){
        int replacepos=m_filePath.indexOf('%');
        QString currentfilesequence=m_filePath;
        currentfilesequence.replace(replacepos,1,QString::number(m_fileIndex));
        emit processFileChanged(currentfilesequence);
        setFileIndex(m_fileIndex+1);
    }
    else{
        emit processFileChanged(m_filePath);
    }
}

void FileCaptureNode::DeSerialize(QJsonObject &json)
{


    CaptureNode::DeSerialize(json);

    FlowNodePort* port=getPortFromKey("frameCaptured");
    if(port){
        port->setHidden(true);
    }
}

