#include "processingnode.h"
#include <QtConcurrent>

using namespace cv;

ProcessingNode::ProcessingNode()
{
    m_type=Type::ProcessingNode;


    setName("Processing node");
}

ProcessingNode::~ProcessingNode()
{

}



void ProcessingNode::setProcess(bool process)
{

    emit processChanged(process);

    //    if(!m_input || m_input->cvMat()->empty())
    //        return;

    if(process){


        if(configsLoaded()==false){
            return;
        }

        QtConcurrent::run([this](){
            QMutexLocker ml(&mMutex);

            this->doProcess();


        });
    }
}

void ProcessingNode::reProcess(QMat *out)
{
    this->doProcess();
}

void ProcessingNode::setProcessedMat(QMat *processedMat)
{
    m_processedMat = processedMat;
}


void ProcessingNode::doProcess()
{


    emit outputChanged(m_output);



    setProcessingDone(true);


}

void ProcessingNode::setInput(QMat *input)
{

    m_input = input;


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

    if(m_inputPort->portLabel()==""){
        m_inputPort->setPortLabel("Input");
    }

    if(m_processPort->portLabel()==""){
        m_processPort->setPortLabel("Process");
    }

    if(m_outputPort->portLabel()==""){
        m_outputPort->setPortLabel("Output");
    }


    if(m_processingDonePort->portLabel()==""){
        m_processingDonePort->setPortLabel("Processing Done");
    }

    setConfigsLoaded(true);



}



