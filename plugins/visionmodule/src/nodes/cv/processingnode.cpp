#include "processingnode.h"
#include <QtConcurrent>

using namespace cv;

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


void ProcessingNode::setProcess(bool process)
{

    m_process = process;
    emit processChanged(m_process);

    if(!m_input || m_input->cvMat()->empty())
        return;

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




    Mat processedOutput;
    (*m_input->cvMat()).copyTo(processedOutput);

    int processorscount=m_preProcessors->count();
    for (int i = 0;i<processorscount ;i++) {
        PreProcessing* preprocessing=m_preProcessors->getItemAt(i);
        if(preprocessing){
            preprocessing->apply(processedOutput,processedOutput,*m_input->cvMat());
        }
    }

    processedOutput.copyTo(*m_output->cvMat());

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

    if(m_input->cvMat()->empty()){
        return;
    }
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


    for (int i = 0; i < m_preProcessors->count(); ++i) {

        connect(m_preProcessors->getItemAt(i),&PreProcessing::preProcessorConditionChanged,this,[&]{
            if(configsLoaded()){
                this->setProcess(true);
            }
        });
    }


    setConfigsLoaded(true);



}



