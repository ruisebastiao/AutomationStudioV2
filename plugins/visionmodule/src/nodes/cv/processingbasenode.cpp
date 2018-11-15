#include "processingbasenode.h"

ProcessingBaseNode::ProcessingBaseNode()
{
    m_processingType=ProcessingType::ProcessingBaseNode;
}

QQmlComponent *ProcessingBaseNode::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/Cv/ProcessingBaseNodeItem.qml"));
    return delegate.get();

}

void ProcessingBaseNode::doProcess()
{
    m_input->cvMat()->copyTo(*m_output->cvMat());

    ProcessingNode::doProcess();
}

void ProcessingBaseNode::DeSerialize(QJsonObject &json)
{
    ProcessingNode::DeSerialize(json);

    m_inputPort->setHidden(true);

    if(m_processPort->portLabel()==""){
        m_processPort->setPortLabel("Process");
    }
}

void ProcessingBaseNode::setInput(QMat *input)
{
    if(!input){
        return;
    }

    ProcessingNode::setInput(input);

    if(input->cvMat()->empty()==false){
        setProcess(true);
    }


}
