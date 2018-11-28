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
//    m_input->cvMat()->copyTo(*m_output->cvMat());


    QMat* in=m_input.value<QMat*>();

    in->cvMat()->copyTo(*m_output.value<QMat*>()->cvMat());

    ProcessingNode::doProcess();
}

void ProcessingBaseNode::DeSerialize(QJsonObject &json)
{
    ProcessingNode::DeSerialize(json);

    FlowNodePort* port=getPortFromKey("input");
    if(port){
        port->setHidden(true);
    }

    port=getPortFromKey("input");
    if(port){
        if(port->portLabel()==""){
            port->setPortLabel("Process");
        }
    }


}

void ProcessingBaseNode::setInput(QVariant input)
{
    if(input.canConvert<QMat*>()==false){
        return;
    }

    ProcessingNode::setInput(input);

    QMat* mat=input.value<QMat*>();
    if(mat && mat->cvMat()->empty()==false){
        setProcess(true);
    }


}
