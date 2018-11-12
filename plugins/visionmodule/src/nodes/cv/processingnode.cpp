#include "processingnode.h"
#include <QtConcurrent>

ProcessingNode::ProcessingNode()
{
    m_type=Type::ProcessingNode;

    m_preProcessors=new PreProcessingListModel(this);

    setName("Processing node");
}

ProcessingNode::~ProcessingNode()
{

}

QQmlComponent*  ProcessingNode ::delegate(QQmlEngine& engine) noexcept
{
    static UniqueQQmlComponentPtr   qan_FlowNode_delegate;
    if ( !qan_FlowNode_delegate )
        qan_FlowNode_delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/Cv/ProcessingNodeItem.qml"));
    return qan_FlowNode_delegate.get();
}

void ProcessingNode::reProcess()
{
    setProcess(true);
}

void ProcessingNode::setProcess(bool process)
{

    m_process = process;
    emit processChanged(m_process);

    if(m_process){
        setProcess(false);

        if(configsLoaded()==false){
            return;
        }

        QtConcurrent::run([this](){
            QMutexLocker ml(&mMutex);

            this->doProcess();


        });
    }
}


void ProcessingNode::doProcess()
{

    (*m_input->cvMat()).copyTo((*m_output->cvMat()));




    emit outputChanged(m_output);
    setProcessingDone(true);



    if(isEndNode()){
        emit processingCompleted(this);
    }


}

void ProcessingNode::setInput(QMat *input)
{

    if(!input){
        return;
    }

    m_input = input;

    if(m_input){

        setOutput(m_input);
    }

    emit inputChanged(m_input);

    if(isBaseNode()){
        setProcess(true);
    }


}

void ProcessingNode::DeSerialize(QJsonObject &json)
{
    m_inputPort= new FlowNodePort(this,qan::PortItem::Type::In,"input");
    m_outputPort= new FlowNodePort(this,qan::PortItem::Type::Out,"output");


    m_processPort= new FlowNodePort(this,qan::PortItem::Type::In,"process");
    m_processingDonePort=new FlowNodePort(this,qan::PortItem::Type::Out,"processingDone");


    m_inPorts.append(m_inputPort);
    m_inPorts.append(m_processPort);

    m_outPorts.append(m_outputPort);
    m_outPorts.append(m_processingDonePort);

    FlowNode::DeSerialize(json);

    setConfigsLoaded(true);

}



