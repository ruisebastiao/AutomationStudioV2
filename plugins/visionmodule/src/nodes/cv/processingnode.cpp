#include "processingnode.h"
#include <QtConcurrent>

ProcessingNode::ProcessingNode()
{
    m_type=Type::ProcessingNode;
    setName("Processing node");
}

ProcessingNode::~ProcessingNode()
{

}

//void ProcessingNode::process()
//{
//    if(configsLoaded()==false){
//        return;
//    }

//    QtConcurrent::run([this](){
//        QMutexLocker ml(&mMutex);

//        setProcessing(true);
//        this->doProcess();
//        setProcessing(false);


//    });

//}

QQmlComponent*  ProcessingNode ::delegate(QQmlEngine& engine) noexcept
{
    static UniqueQQmlComponentPtr   qan_FlowNode_delegate;
    if ( !qan_FlowNode_delegate )
        qan_FlowNode_delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:/components/nodes/cv/ProcessingNode.qml"));
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


    setProcessingDone(true);


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



